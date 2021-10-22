#ifndef _VECTOR3_HPP_INCLUDED
#define _VECTOR3_HPP_INCLUDED

#include <assert.h>

template <typename T>
struct Vec3
{
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    ~Vec3() {}
    
    Vec3& operator+=(const Vec3& vec);
    Vec3& operator-=(const Vec3& vec);
    Vec3& operator*=(float k);
    Vec3& operator/=(float k);

    Vec3 MulByCoords(const Vec3& lhs, const Vec3& rhs);

    float GetLength();
    void Normalize();

    T x;
    T y;
    T z;
};

template <typename T>
Vec3<T> operator+(Vec3<T> lhs, const Vec3<T>& rhs)
{
    return lhs += rhs;
}

template <typename T>
Vec3<T> operator-(Vec3<T> lhs, const Vec3<T>& rhs)
{
    return lhs -= rhs;
}

template <typename T>
float operator*(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T>
Vec3<T> operator*(float lhs, Vec3<T> rhs)
{
    return rhs *= lhs;
}

template <typename T>
Vec3<T> operator/(Vec3<T> lhs, float rhs)
{
    return lhs /= rhs;
}

template <typename T>
Vec3<T>& Vec3<T>::operator+=(const Vec3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator-=(const Vec3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator*=(float k)
{
    x *= k;
    y *= k;
    z *= k;

    return *this;
}

template <typename T>
Vec3<T>& Vec3<T>::operator/=(float k)
{
    assert(k);

    x /= k;
    y /= k;
    z /= k;

    return *this;
}

template <typename T>
Vec3<T> Vec3<T>::MulByCoords(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

template <typename T>
float Vec3<T>::GetLength()
{
    return sqrt(x * x + y * y + z * z);
}

template <typename T>
void Vec3<T>::Normalize()
{
    float length = GetLength();

    if (length != 0)
    {
        *this /= length;
    }
}

#endif /* _VECTOR3_HPP_INCLUDED */