@echo off

set WORKING_PATH=%1

cd /d %~dp0

rem コンパイル
echo compile
g++ -g ^
    -I"%WORKING_PATH%\library\include" ^
    -DDX_GCC_COMPILE ^
    -c %WORKING_PATH%\program\main.cpp ^
    -o .\main.o

rem リンク
echo link
g++ .\main.o ^
    -o %WORKING_PATH%\rom\test.exe ^
    -L"%WORKING_PATH%\library\include\DxLib" ^
    -mwindows ^
    -lDxLib ^
    -lDxUseCLib ^
    -lDxDrawFunc ^
    -ljpeg ^
    -lpng ^
    -lzlib ^
    -ltiff ^
    -ltheora_static ^
    -lvorbis_static ^
    -lvorbisfile_static ^
    -logg_static ^
    -lbulletdynamics ^
    -lbulletcollision ^
    -lbulletmath ^
    -lopusfile ^
    -lopus ^
    -lsilk_common ^
    -lcelt

del .\main.o

