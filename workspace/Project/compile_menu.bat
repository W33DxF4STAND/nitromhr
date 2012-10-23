@echo off
setLocal EnableDelayedExpansion
set compiler=main.cpp
COLOR 0b
Title Emmanuel Utomi's SCO Compiler

if not exist *.c (
if not exist *.cpp goto nofile
)
if not exist ../../out_sco (
cd ../../
mkdir out_sco
cd workspace/Project/
)
if exist ../../out_sco/*.sco (
echo Cleaning prior scripts ...
echo.
cd ../../out_sco/
del -f *.sco
cd ../workspace/Project/
)
if exist ../../out_sco/*.s (
echo Cleaning prior failed scripts ...
echo.
cd ../../out_sco/
del -f *.s
cd ../workspace/Project/
)
if not defined %%1 goto compile_menu
goto compile_custom

:compile_menu
echo Compiling %compiler%
echo.
..\..\bin\scocl_old.exe TBOGT "%compiler%" "..\..\out_sco/" > build.txt
for /f "tokens=* delims= skip=1" %%a in (build.txt) do (
cls
echo %%a
)
if not exist ../../out_sco/*.sco goto err_build
set "outsco=*.sco"
cd ../../out_sco/
ren "main.sco" "xmc_modmenu.sco"
echo.
for %%A in (%outsco%) do echo.Size of "xmc_modmenu.sco" is %%~zA bytes
cd ../workspace/Project/
del -f build.txt
pause
exit 1

:compile_custom
echo.
if %%1 NEQ *.c goto err_custom
echo Compiling %%1 ...
..\..\bin\scocl_old.exe TBOGT "%%1" "..\..\out_sco/"
if not exist *.sco goto err_build
pause
exit 1

:err_custom
cls
echo Your custom script is not a .c file, please try again
pause
exit 1

:err_build
echo.
echo.
echo ERROR ABOVE
echo Your custom script did not build
echo make your changes, then press any key to try again
pause >nul 
cls
goto compile_menu

:nofile
cls
echo No .c Files found in local directory
pause 
exit 1