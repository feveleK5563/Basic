@echo off

rem プロジェクト名定義
set PROJECT_NAME=basic

rem ビルドオプション
set IS_DEBUG_BUILD=%1

rem 作業ディレクトリ
cd /d %~dp0
set MAKE_DIR=%~dp0\make
set ROM_DIR=%~dp0\..\rom
set EXE_FILE=%MAKE_DIR%\%PROJECT_NAME%.exe

rem makeフォルダを作成
if not exist %MAKE_DIR% (
    mkdir %MAKE_DIR%
)

cd %MAKE_DIR%

rem cmakeでなんかファイルいっぱい作る
cmake .. -G "MinGW Makefiles" ^
         -D CMAKE_PROJECT_NAME="%PROJECT_NAME%" ^
         -D IS_DEBUG_BUILD=%IS_DEBUG_BUILD%
if %errorlevel% neq 0 (
    exit /b 1
)

rem ビルド
cmake --build .
if %errorlevel% neq 0 (
    exit /b 1
)

rem 実行ファイルを移動させる
echo %EXE_FILE%
if not exist %EXE_FILE% (
    echo 実行ファイルがありません
    exit /b 1
)

move %EXE_FILE% %ROM_DIR%

exit /b 0
