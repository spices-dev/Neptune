::@file compile.bat
::@brief This file is used for compile shader source with slang.
::@author Spices.
@echo off

setlocal enabledelayedexpansion

::------------------------------------------------------------------------------
:: Config
::------------------------------------------------------------------------------

:: @brief 1: Debug, 0: Release.
set DEBUG=1

:: @brief Target SPIR-V profile.
set SPIRV_PROFILE=spirv_1_4

:: @brief Include search paths (shaders use #include "Header/xxx").
set INCLUDE_FLAGS=-I. -I./Header

:: @brief Slang compiler.
::  -matrix-layout-column-major : column-major matrices, keep mul(M, v) same as GLSL (M * v).
::  -fvk-use-scalar-layout      : GL_EXT_scalar_block_layout.
::  -emit-spirv-directly        : emit SPIR-V directly.
::  -entry main                 : entry name.
::  -capability ...             : declare subgroup (Wave*) capabilities.
set COMMON_FLAGS=-target spirv -profile %SPIRV_PROFILE% -entry main -matrix-layout-column-major -fvk-use-scalar-layout -emit-spirv-directly -capability spvGroupNonUniform+spvGroupNonUniformVote+spvGroupNonUniformBallot+spvGroupNonUniformArithmetic

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

set SLANGC="%VULKAN_SDK%\Bin\slangc.exe"

if not exist %SLANGC% (
    echo [ERROR] slangc.exe not found: %SLANGC%
    pause
    exit /b 1
)

::------------------------------------------------------------------------------
:: Compile
::------------------------------------------------------------------------------

echo ========================================
echo Compiling all shader files with  Slang...
echo ========================================
%SLANGC% -version
echo.

set /a TOTAL=0
set /a FAILED=0

for %%f in (*.slang) do (
    set /a TOTAL+=1
    echo Compiling %%f ...
    %SLANGC% %%f %COMMON_FLAGS% %BUILD_FLAGS% %INCLUDE_FLAGS% -o ../spv/%%~nf%%~xf.spv
    if !errorlevel! equ 0 (
        echo   [OK] %%f -^> ../spv/%%~nf%%~xf.spv
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