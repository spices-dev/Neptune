/**
* @file Compiler.h.
* @brief The Compiler Macro.
* @author Spices.
*/

#pragma once

#ifdef _MSC_VER   // @brief mvsc and LLVM-clang-cl
#define NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#define NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif