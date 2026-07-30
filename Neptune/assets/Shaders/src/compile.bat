::@file compile.bat
::@brief This file is used for compile shader source to spv.
::Though we use internal shader compile, this file might be useless. 
::@author Spices.
@echo off

setlocal enabledelayedexpansion

echo ========================================
echo Compiling all shader files...
echo ========================================
echo.

for %%f in (*.vert *.frag *.comp *.geom *.tesc *.tese) do (
    echo Compiling %%f ...
    %VULKAN_SDK%/Bin/glslc.exe %%f -o %%~nf%%~xf.spv -g --target-env=vulkan1.4 -I.
    if !errorlevel! equ 0 (
        echo   [OK] %%f -^> %%~nf%%~xf.spv
    ) else (
        echo   [FAILED] %%f
    )
    echo.
)

echo ========================================
echo Compilation complete!
echo ========================================
pause