//------------------------------------------------------------------------------
// math.hpp
// 数式とか色々
//------------------------------------------------------------------------------

#pragma once

namespace Math
{
    static constexpr float PI = 3.14159265358979323846264338327950288419f;

    //--------------------------------------------------------------------------
    // 弧度法変換
    float ToRadian(float val)
    {
        return val * PI / 180.f;
    }

    //--------------------------------------------------------------------------
    // 度数法変換
    float ToDegree(float val)
    {
        return 180.f * val / PI;
    }

    //--------------------------------------------------------------------------
    // 二次元ベクトルクラス
    class Vec2
    {
    public:
        float x = 0.f;
        float y = 0.f;

    public:
        Vec2(){}
        Vec2(const Vec2& vec)
            : x(vec.x), y(vec.y){}
        Vec2(float x, float y)
            : x(x), y(y){}

        void operator =(const Vec2& vec)
        {
            x = vec.x;
            y = vec.y;
        }
        Vec2 operator +(const Vec2& vec) const
        {
            return Vec2(x + vec.x, y + vec.y);
        }
        Vec2 operator -(const Vec2& vec) const
        {
            return Vec2(x - vec.x, y - vec.y);
        }
        void operator +=(const Vec2& vec)
        {
            x += vec.x;
            y += vec.y;
        }
        void operator -=(const Vec2& vec)
        {
            x -= vec.x;
            y -= vec.y;
        }
    };

    //--------------------------------------------------------------------------
    // 当たり判定つき矩形クラス
    class Box
    {
    public:
        float x = 0.f;
        float y = 0.f;
        float w = 0.f;
        float h = 0.f;

    public:
        Box(){}
        Box(const Box& box)
            : x(box.x), y(box.y), w(box.w), h(box.h){}
        Box(float x, float y, float w, float h)
            : x(x), y(y), w(w), h(h){}

        bool Hit(const Box& box) const
        {
            return x <= (box.x + box.w) && box.x <= (x + w) &&
                   y <= (box.y + box.h) && box.y <= (y + h);
        }
        bool Hit(const Vec2& vec) const
        {
            return x <= vec.x && vec.x <= (x + w) &&
                   y <= vec.y && vec.y <= (y + h);
        }

        bool In(const Box& box) const
        {
            return x <= box.x && (box.x + box.w) <= (x + w) &&
                   y <= box.y && (box.y + box.h) <= (y + h);
        }

        void operator =(const Box& box)
        {
            x = box.x;
            y = box.y;
            w = box.w;
            h = box.h;
        }
        bool operator <=(const Box& box)
        {
            return (w * h) <= (box.w * box.h);
        }
        bool operator <(const Box& box)
        {
            return (w * h) < (box.w * box.h);
        }
        bool operator >=(const Box& box)
        {
            return (w * h) >= (box.w * box.h);
        }
        bool operator >(const Box& box)
        {
            return (w * h) > (box.w * box.h);
        }
    };
}