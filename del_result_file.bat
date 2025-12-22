@echo off
setlocal enabledelayedexpansion

:: 设置当前目录为根目录
set "root_folder=%CD%"

:: 要删除的文件扩展名列表
set "extensions=o d elf bak dep map lst i srec bin hex verilog dump dasm icf dbgconf crf htm lnp sct axf"

:: 循环删除每种扩展名的文件
echo Deleting generated files...
for %%e in (%extensions%) do (
    echo.
    echo Deleting *.%%e files...
    for /r "%root_folder%" %%f in (*.%%e) do (
        del /q "%%f" >nul 2>&1
        if !errorlevel! equ 0 (
            echo Deleted: %%f
        ) else (
            echo Failed: %%f (file not found or in use)
        )
    )
)

echo.
echo Cleanup operation completed.
pause