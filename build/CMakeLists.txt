# g++のオプション指定
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDX_GCC_COMPILE -mwindows")

# CMakeのバージョン指定とプロジェクト設定
cmake_minimum_required(VERSION 3.23.0)
project(${CMAKE_PROJECT_NAME} CXX)

# インクルードファイル指定
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../program/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/include/DxLib)

# ソースファイルを全部さらってきて追加
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../program SOURCES)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# ライブラリをリンク
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    DxLib
    DxLibW
    DxUseCLib
    DxUseCLibW
    DxDrawFunc
    jpeg
    png
    zlib
    tiff
    theora_static
    vorbis_static
    vorbisfile_static
    ogg_static
    bulletdynamics
    bulletcollision
    bulletmath
    opusfile
    opus
    silk_common
    celt
)
