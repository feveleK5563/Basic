# g++のオプション指定
if(${IS_DEBUG_BUILD})
    # デバッグビルド
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 --input-charset=utf-8 --exec-charset=cp932 -g -DDX_GCC_COMPILE -D_DEBUG")
else()
    # リリースビルド
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 --input-charset=utf-8 --exec-charset=cp932 -DDX_GCC_COMPILE -mwindows")
endif()

# CMakeのバージョン指定とプロジェクト設定
cmake_minimum_required(VERSION 3.23.0)
project(${CMAKE_PROJECT_NAME} CXX)

# インクルードファイル指定
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../program/library/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../program/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../program/library/lib/DxLib)

# ソースファイルを全部さらってきて追加
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/../program/source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../program/source/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../program/source/*/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../program/source/*/*/*/*.cpp")
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
