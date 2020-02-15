echo off
setlocal enabledelayedexpansion
for /f %%f in ('dir /b .\*.c') do (
	set input=%%f
	set output=!input:.c=.exe!
	gcc !input! -o !output!
)
