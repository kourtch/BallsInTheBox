#pragma once

#include "stdafx.h"

template <typename T>
class Vector2
{
public:
  // x, y the two elements of the 2 dimensional vector
  T x, y;

  // defalut constructor
  Vector2(void) : x(0), y(0) {}

  // constructor. 
  Vector2(T i_x, T i_y)
    : x(i_x), y(i_y) {}

  // Assigns the product of the receiver and the scalar i_scale to the receiver. 
  Vector2 &operator*=(T i_scale) { x *= i_scale; y *= i_scale; return *this; }
  Vector2 &operator/=(T i_div) { x /= i_div; y /= i_div; return *this; }

  Vector2 &operator+=(const Vector2 &i_v) {x += i_v.x; y += i_v.y; return *this; }
  Vector2 &operator-=(const Vector2 &i_v) {x -= i_v.x; y -= i_v.y; return *this; }

  T lengthSqr(void) const { return x*x + y*y; }

};

// =======================
// 2D VECTORS AND SCALARS. 
// =======================

// Return the product of the 2D vector i_v and the scalar i_c. 
template <class T>
inline Vector2<T> operator*(const Vector2<T> &i_v, T i_c)
{
  return Vector2<T>(i_v.x*i_c, i_v.y*i_c);
}

template <class T>
inline Vector2<T> operator*(T i_c, const Vector2<T> &i_v)
{
  return i_v*i_c;
}

// Returns the product of the 2D vector V and the scalar 1/C, where C
// is presumed nonzero. 
template <class T>
inline Vector2<T> operator/(const Vector2<T> &i_v, T i_c)
{
  return Vector2<T>(i_v.x / i_c, i_v.y / i_c);
}


// =======================
// 2D VECTOR PAIRS. 
// =======================

// Returns the sum of the 2D vectors V1 and V2. 
template <class T>
inline Vector2<T> operator+(const Vector2<T> &i_v1, const Vector2<T> &i_v2)
{
  return Vector2<T>(i_v1.x + i_v2.x, i_v1.y + i_v2.y);
}

// Returns the difference of the 2D vectors V1 and V2. 
template <class T>
inline Vector2<T> operator-(const Vector2<T> &i_v1, const Vector2<T> &i_v2)
{
  return Vector2<T>(i_v1.x - i_v2.x, i_v1.y - i_v2.y);
}

// Returns the dot product of the 2D vectors V1 and V2. 
template <class T>
inline T operator*(const Vector2<T> &i_v1, const Vector2<T> &i_v2)
{
  return i_v1.x*i_v2.x + i_v1.y*i_v2.y;
}

typedef Vector2<float> V;

class Ball
{
public:
  Ball() : radius(50), color(RGB(0, 0, 255)) {};

  COLORREF color;
  float radius;
  Vector2<float> p;
  Vector2<float> v;

  void init(CRect walls);
  void reflect(Vector2<float> a);
  bool collide(Ball& otherBall);

};

