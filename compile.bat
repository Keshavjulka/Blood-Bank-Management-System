@echo off
echo Compiling Blood Bank Management System...
echo.

REM Check if g++ is available
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found. Please install MinGW or a C++ compiler.
    pause
    exit /b 1
)

REM Compile the program
echo Compiling final.c++...
g++ -std=c++17 -Wall -o BloodBankSystem.exe final.c++

if %errorlevel% equ 0 (
    echo.
    echo ✓ Compilation successful!
    echo ✓ Executable created: BloodBankSystem.exe
    echo.
    echo To run the program, type: BloodBankSystem.exe
    echo.
) else (
    echo.
    echo ✗ Compilation failed. Please check your code for errors.
    echo.
)

pause
