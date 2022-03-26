@echo off

rem �v���W�F�N�g����`
set PROJECT_NAME=basic

rem �r���h�I�v�V����
set IS_DEBUG_BUILD=%1

rem ��ƃf�B���N�g��
cd /d %~dp0
set MAKE_DIR=%~dp0\make
set ROM_DIR=%~dp0\..\rom
set EXE_FILE=%MAKE_DIR%\%PROJECT_NAME%.exe

rem make�t�H���_���쐬
if not exist %MAKE_DIR% (
    mkdir %MAKE_DIR%
)

cd %MAKE_DIR%

rem cmake�łȂ񂩃t�@�C�������ς����
cmake .. -G "MinGW Makefiles" ^
         -D CMAKE_PROJECT_NAME="%PROJECT_NAME%" ^
         -D IS_DEBUG_BUILD=%IS_DEBUG_BUILD%
if %errorlevel% neq 0 (
    exit /b 1
)

rem �r���h
cmake --build .
if %errorlevel% neq 0 (
    exit /b 1
)

rem ���s�t�@�C�����ړ�������
echo %EXE_FILE%
if not exist %EXE_FILE% (
    echo ���s�t�@�C��������܂���
    exit /b 1
)

move %EXE_FILE% %ROM_DIR%

exit /b 0
