@echo off
cd /d "%~dp0"
g++ -std=c++11 -O2 -Wall -Wextra main.cpp -o mini_search.exe
if errorlevel 1 (
  echo Compilation failed.
  pause
  exit /b 1
)
mini_search.exe
pause
