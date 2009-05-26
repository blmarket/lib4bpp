#include <vector>
#include <cmath>

struct Vector2
{
    float x,y;

    Vector2 & operator+=(const Vector2 &p)
    {
        x+=p.x;
        y+=p.y;
        return (*this);
    }

    Vector2 operator+(const Vector2 &p)
    {
        Vector2 tmp = (*this);
        tmp+=p;
        return tmp;
    }

    Vector2 & operator-=(const Vector2 &p)
    {
        x-=p.x;
        y-=p.y;
        return (*this);
    }

    Vector2 & operator*=(const float v)
    {
        x *= v;
        y *= v;
    }

    float angle()
    {
        return atan2f(y,x);
    }

    void normalize()
    {
        float dist = hypot(x,y);
        x /= dist; y /= dist;
    }
};

template<typename T>
T operator-(const T &a1, const T &a2)
{
    T tmp = a1;
    tmp -= a2;
    return tmp;
}

template<typename T1,typename T2>
T1 operator*(const T1 &a1, const T2 &a2)
{
    T1 tmp = a1;
    tmp *= a2;
    return tmp;
}


struct Line
{
    Vector2 s,e;
};

class TrueSight
{
public:
    

protected:
    void CalcClipArea(const Line &wall);

    std::vector<Line>   m_Walls;
    Vector2             m_Viewer;
    float               m_SightRadius;
};
