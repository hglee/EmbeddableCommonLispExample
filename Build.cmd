@echo off

title Build - %DATE% %TIME%

cls
Tools\FAKE\tools\fake run Build.fsx

pause
pause
