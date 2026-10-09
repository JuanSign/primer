@echo off
setlocal
set d=%1_fail
if not exist %d% md %d%
for /l %%i in (1,1,1000) do (
  gen %%i > %d%\in
  %1 < %d%\in > %d%\out
  brute < %d%\in > %d%\ans
  fc %d%\out %d%\ans > nul || (
    echo test %%i failed, see %d%
    exit /b
  )
)
rd /s /q %d%
echo all passed
