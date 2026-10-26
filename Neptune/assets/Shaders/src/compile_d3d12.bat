::@file compile_d3d12.bat
::@brief This file is used for compile shader source with slang to DXIL.
::@author Spices.
@echo off

setlocal enabledelayedexpansion

::------------------------------------------------------------------------------
:: Config
::------------------------------------------------------------------------------

:: @brief 1: Debug, 0: Release.
set DEBUG=1

:: @brief Target shader model. Wave intrinsics need >= sm_6_0, mesh shader >= sm_6_5.
set DXIL_PROFILE=sm_6_6

:: @brief 1: Dump reflection json.
set DUMP_REFLECTION=1

:: @brief Output directory (relative to this script).
set OUT_DIR=..\dxil

:: @brief Include search paths (shaders use #include "Header/xxx").
set INCLUDE_FLAGS=-I. -I./Header

:: @brief Slang compiler.
::  -matrix-layout-column-major : keep the same matrix layout as the Vulkan build.
::  -entry main                 : entry name.
set COMMON_FLAGS=-target dxil -profile %DXIL_PROFILE% -entry main -matrix-layout-column-major

if "%DEBUG%"=="1" (
    set BUILD_FLAGS=-g -O0
) else (
    set BUILD_FLAGS=-O3
)

::------------------------------------------------------------------------------
:: Check Slang
::------------------------------------------------------------------------------

if not defined VULKAN_SDK (
    echo [ERROR] VULKAN_SDK environment variable is not set.
    pause
    exit /b 1
)

set SLANG_BIN=%VULKAN_SDK%\Bin
set SLANGC="%SLANG_BIN%\slangc.exe"

if not exist %SLANGC% (
    echo [ERROR] slangc.exe not found: %SLANGC%
    pause
    exit /b 1
)

:: DXIL generation relies on DXC. dxil.dll is required to SIGN the shader,
:: an unsigned DXIL will be rejected by D3D12 runtime.
if not exist "%SLANG_BIN%\dxcompiler.dll" (
    echo [WARN] dxcompiler.dll not found in %SLANG_BIN%, DXIL compile will fail.
)
if not exist "%SLANG_BIN%\dxil.dll" (
    echo [WARN] dxil.dll not found in %SLANG_BIN%, DXIL will be unsigned and rejected by D3D12.
)

if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

::------------------------------------------------------------------------------
:: Compile
::------------------------------------------------------------------------------

echo ========================================
echo Compiling all shader files to DXIL with Slang...
echo Profile: %DXIL_PROFILE%
echo ========================================
%SLANGC% -version
echo.

set /a TOTAL=0
set /a FAILED=0

for %%f in (*.slang) do (
    set /a TOTAL+=1
    echo Compiling %%f ...
    if "%DUMP_REFLECTION%"=="1" (
        %SLANGC% %%f %COMMON_FLAGS% %BUILD_FLAGS% %INCLUDE_FLAGS% -reflection-json %OUT_DIR%/%%~nf%%~xf.json -o %OUT_DIR%/%%~nf%%~xf.dxil
    ) else (
        %SLANGC% %%f %COMMON_FLAGS% %BUILD_FLAGS% %INCLUDE_FLAGS% -o %OUT_DIR%/%%~nf%%~xf.dxil
    )
    if !errorlevel! equ 0 (
        echo   [OK] %%f -^> %OUT_DIR%/%%~nf%%~xf.dxil
    ) else (
        set /a FAILED+=1
        echo   [FAILED] %%f
    )
    echo.
)

echo ========================================
echo Compilation complete! Total: !TOTAL!, Failed: !FAILED!
echo ========================================
pause

if !FAILED! gtr 0 exit /b 1
exit /b 0
