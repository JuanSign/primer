@echo off
setlocal
set d=%1_fail
set c=fc %d%\out %d%\ans
if not "%2"=="" set c=%2 %d%\in %d%\out %d%\ans
if not exist %d% md %d%
for /l %%i in (1,1,1000) do (
  gen %%i > %d%\in
  %1 < %d%\in > %d%\out
  brute < %d%\in > %d%\ans
  %c% > nul || (
    echo test %%i failed, see %d%
    exit /b
  )
)
rd /s /q %d%
echo all passed
