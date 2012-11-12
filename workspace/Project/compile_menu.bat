@echo off
setLocal EnableDelayedExpansion
set compiler=main.c
set out=xmc_modmenu.sco
set /A value=0
set /A sum=0
::set /A divide=1024
set "outsco=*.sco"

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
if exist build.txt (
echo Cleaning prior build log ...
echo.
del -f build.txt
)
if exist ../../out_sco/*.newsco (
echo.
cd ../../out_sco/
del -f *.newsco
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
echo Compiling %compiler% ...
echo.
..\..\bin\scocl_old.exe TBOGT "%compiler%" "..\..\out_sco/" > build.txt
for /f "tokens=* delims= skip=1" %%a in (build.txt) do (
cls
echo %%a
)
if not exist ../../out_sco/*.sco goto err_build
cd ../../out_sco/
ren "main.sco" "%out%"
echo.
for %%A in (%outsco%) do (
set /A value=%%~zA
set /A value /=1024
echo Size of "%out%" is !value!kb
)
::for %%A in (%outsco%) do echo.New compressed Size of "%out%" is %%~zI bytes
::for %%A in (%outsco%) do echo.Size of "%out%" is %%~zA bytes
cd ../workspace/Project/
del -f build.txt
echo Press any key to launch sco compressor
pause > nul
cls
..\..\bin\compress.exe ../../out_sco/xmc_modmenu.sco
goto compress

:compress
cls
echo Waiting for compressed sco ...
if not exist ../../out_sco/xmc_modmenu.sco.newsco goto compressloop
echo Cleaning Renaming compressed file ...
echo.
cd ../../out_sco/
del -f xmc_modmenu.sco
ren "xmc_modmenu.sco.newsco" "%out%"
cd ../workspace/Project/
cls
cd ../../out_sco/
for %%A in (%outsco%) do (
set /A value=%%~zA
set /A value /=1024
echo Compressed size of "%out%" is !value!kb
)
cd ../workspace/Project/
echo.
echo Completed compile job, your sco is named %out%
::for %%A in (%outsco%) do echo.New compressed Size of "%out%" is %%~zA bytes
echo.Press any key to exit, or you can sit here like a dumbass :D
pause > nul
exit 1

:compressloop
ping localhost -n 2 >nul
goto compress

:compile_custom
echo.
if %%1 NEQ *.c goto err_custom
echo Compiling %%1 ...
..\..\bin\scocl_old.exe TBOGT "%%1" "..\..\out_sco/"
if not exist *.sco goto err_build
pause
exit 1

:err_custom
del -f build.txt > nul
echo.
echo.
echo Your custom script is not a .c or .cpp file, please try again
pause
exit 1

:err_build
del -f build.txt > nul
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