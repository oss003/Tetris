@echo off
echo Assembling %1
bin\ca65 -l -o %1.o %1.asm 
if not "%errorlevel%" == "0" goto failed
echo Linking %1
bin\ld65 %1.o -C atom.cfg -o %1.atm 
if not "%errorlevel%" == "0" goto failed
copy %1.atm "C:\Users\gebruiker\Documents\Atom\Atomulator Phill\mmc"
echo Finished, created %1.atm
goto end

:failed
echo.
echo Error %errorlevel%
echo.

:end


