/**
* @file ImageWriter.cpp.
* @brief The ImageWriter Class Implementation.
* @author Spices.
*/

#include "ImageWriter.h"

#include <array>
#include <fstream>

namespace Neptune {
    
    namespace detail
    {
        inline void PutBE32(std::vector<uint8_t>& v, uint32_t x)
        {
            v.push_back(uint8_t(x >> 24)); v.push_back(uint8_t(x >> 16));
            v.push_back(uint8_t(x >> 8));  v.push_back(uint8_t(x));
        }

        inline uint32_t Crc32(const uint8_t* p, size_t n)
        {
            static const auto table = [] {
                std::array<uint32_t, 256> t{};
                for (uint32_t i = 0; i < 256; ++i)
                {
                    uint32_t c = i;
                    for (int k = 0; k < 8; ++k) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
                    t[i] = c;
                }
                return t;
            }();
            uint32_t crc = 0xFFFFFFFFu;
            for (size_t i = 0; i < n; ++i) crc = table[(crc ^ p[i]) & 0xFF] ^ (crc >> 8);
            return ~crc;
        }

        inline uint32_t Adler32(const uint8_t* p, size_t n)
        {
            uint32_t a = 1, b = 0;
            while (n)
            {
                size_t len = n < 5552 ? n : 5552;
                n -= len;
                while (len--) { a += *p++; b += a; }
                a %= 65521; b %= 65521;
            }
            return (b << 16) | a;
        }
        
        inline std::vector<uint8_t> ZlibStore(const std::vector<uint8_t>& raw)
        {
            std::vector<uint8_t> z;
            z.reserve(raw.size() + raw.size() / 65535 * 5 + 16);
            z.push_back(0x78); z.push_back(0x01);

            size_t pos = 0;
            do
            {
                const size_t len   = std::min<size_t>(65535, raw.size() - pos);
                const bool   final = (pos + len == raw.size());
                z.push_back(final ? 1 : 0);
                z.push_back(uint8_t(len & 0xFF));          z.push_back(uint8_t(len >> 8));
                z.push_back(uint8_t(~len & 0xFF));         z.push_back(uint8_t((~len >> 8) & 0xFF));
                z.insert(z.end(), raw.begin() + pos, raw.begin() + pos + len);
                pos += len;
            } while (pos < raw.size());

            PutBE32(z, Adler32(raw.data(), raw.size()));
            return z;
        }

        inline void WriteChunk(std::vector<uint8_t>& out, const char type[4], const std::vector<uint8_t>& data)
        {
            PutBE32(out, uint32_t(data.size()));
            const size_t start = out.size();
            out.insert(out.end(), type, type + 4);
            out.insert(out.end(), data.begin(), data.end());
            PutBE32(out, Crc32(out.data() + start, out.size() - start));
        }
        
        inline std::vector<uint8_t> BuildScanlines(const uint8_t* src, uint32_t w, uint32_t h, uint32_t pixelBytes)
        {
            const size_t bpp = pixelBytes / 8;
            std::vector<uint8_t> raw(size_t(h) * (1 + w * bpp));
            uint8_t* dst = raw.data();

            for (uint32_t y = 0; y < h; ++y)
            {
                *dst++ = 0;
                const uint8_t* row = src + size_t(y) * w * 4;

                if (pixelBytes == 32)
                {
                    for (uint32_t x = 0; x < w; ++x, row += 4, dst += 4)
                    {
                        dst[0] = row[0];
                        dst[1] = row[1];
                        dst[2] = row[2];
                        dst[3] = row[3];
                    }
                }
                else
                {
                    for (uint32_t x = 0; x < w; ++x, row += 4, dst += 8)
                    {
                        uint32_t v; std::memcpy(&v, row, 4);
                        uint32_t c0 =  v        & 0x3FF;
                        uint32_t g  = (v >> 10) & 0x3FF;
                        uint32_t c2 = (v >> 20) & 0x3FF;
                        uint32_t a  =  v >> 30;
                        const uint32_t r = c0;
                        const uint32_t b = c2;

                        auto e10 = [](uint32_t t) { return uint16_t((t << 6) | (t >> 4)); };
                        const uint16_t px[4] = { e10(r), e10(g), e10(b), uint16_t(a * 0x5555) };
                        for (int i = 0; i < 4; ++i)
                        {
                            dst[i * 2]     = uint8_t(px[i] >> 8);
                            dst[i * 2 + 1] = uint8_t(px[i] & 0xFF);
                        }
                    }
                }
            }
            return raw;
        }
    }
    
    bool SavePng(const std::filesystem::path& path, const void* data, uint32_t w, uint32_t h, uint32_t pixelBytes)
    {
        if (!data || !w || !h || pixelBytes != 32) return false;
        
        std::vector<uint8_t> png = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
        
        std::vector<uint8_t> ihdr;
        detail::PutBE32(ihdr, w);    // width
        detail::PutBE32(ihdr, h);    // height
        ihdr.push_back(8);          // bit depth
        ihdr.push_back(6);          // Color type
        ihdr.push_back(0);          // compression
        ihdr.push_back(0);          // filter
        ihdr.push_back(0);          // interlace
        detail::WriteChunk(png, "IHDR", ihdr);
        
        const auto raw = detail::BuildScanlines(static_cast<const uint8_t*>(data), w, h, pixelBytes);
        detail::WriteChunk(png, "IDAT", detail::ZlibStore(raw));
        detail::WriteChunk(png, "IEND", {});

        std::error_code ec;
        
        std::filesystem::create_directories(path.parent_path(), ec);
        
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        
        if (!file) return false;
        
        file.write(reinterpret_cast<const char*>(png.data()), static_cast<std::streamsize>(png.size()));
        
        return static_cast<bool>(file);
    }
    
}
