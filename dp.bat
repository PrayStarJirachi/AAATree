@echo off
:again
call generator
call std
call test
fc forest.standard forest.output
if %errorlevel% == 1 pause > nul & exit
goto again