@echo off
:again
call generator
call test
fc forest.output forest.answer
if %errorlevel% == 1 pause > nul & exit
goto again