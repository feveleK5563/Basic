//------------------------------------------------------------------------------
// various.hpp
// 色々群（デバッグ時は無効になったりする）
//------------------------------------------------------------------------------

#ifdef _DEBUG
#include <assert.h>
#include <stdio.h>
#endif

// アサート
#ifdef _DEBUG
    // デバッグ時（有効）
    #define ASSERT(expr)\
        assert(expr)
#else
    // リリース時（何もしない）
    #define ASSERT(expr)
#endif

// ログ出力
#ifdef _DEBUG
    // デバッグ時（有効）
    #define PRINTF(format, ...)\
        printf(format, __VA_ARGS__)
#else
    // リリース時（何もしない）
    #define PRINTF(format, ...)
#endif