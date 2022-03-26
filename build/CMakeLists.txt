# g++のオプション指定
if(${IS_DEBUG_BUILD})
    # デバッグビルド
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDX_GCC_COMPILE -mwindows")
else()
    # リリースビルド
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDX_GCC_COMPILE -mwindows")
endif()

# CMakeのバージョン指定とプロジェクト設定
cmake_minimum_required(VERSION 3.23.0)
project(${CMAKE_PROJECT_NAME} CXX)

# インクルードファイル指定
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../program/header)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../program/library/DxLib)

# ソースファイルを全部さらってきて追加
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../program/source SOURCE)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})

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
