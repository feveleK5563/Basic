//------------------------------------------------------------------------------
// debugUtil.hpp
// デバッグ時のみ有効
//------------------------------------------------------------------------------

#pragma once

#ifdef _DEBUG
#include <assert.h>
#include <stdio.h>
#endif

// アサート
#ifdef _DEBUG
    // デバッグ時（有効）
    #define DEBUG_ASSERT(expr)\
        assert(expr)
#else
    // リリース時（何もしない）
    #define DEBUG_ASSERT(expr)
#endif

// ログ出力
#ifdef _DEBUG
    // デバッグ時（有効）
    #define DEBUG_LOG(...)\
        printf(__VA_ARGS__)
#else
    // リリース時（何もしない）
    #define DEBUG_LOG(...)
#endif
