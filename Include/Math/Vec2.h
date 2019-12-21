#pragma once
#include <math.h>
#include "Common/GlobalVariables.h"

template <typename T>
class Vec2
{
public:
  Vec2(T x = T(), T y = T()) : m_X(x), m_Y(y) {}
  Vec2(const Vec2& rhs) { *this = rhs; }
  ~Vec2(){}
  Vec2& operator+=(const Vec2& rhs);
  Vec2& operator-=(const Vec2& rhs);
  friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
    lhs += rhs;
    return lhs;
  }
  friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) {
    lhs -= rhs;
    return lhs;
  }
  friend std::ostream& operator<<(std::ostream& os, const Vec2& lhs)
  {
    os << lhs.m_X << ", " << lhs.m_Y;
    return os;
  }
  bool operator==(const Vec2& rhs) { return m_X == rhs.m_X && m_Y == rhs.m_Y; }

   
  const Vec2& operator=(const Vec2& rhs);
private:

  T m_X;
  T m_Y;

};

template<typename T>
inline Vec2<T> & Vec2<T>::operator+=(const Vec2<T>& rhs)
{
  // TODO: insert return statement here
  m_X += rhs.m_X;
  m_Y += rhs.m_Y;
  return *this;
}

template <typename T>
inline Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& rhs)
{
  m_X -= rhs.m_X;
  m_Y -= rhs.m_Y;
  return *this;
}

template <typename T>
inline const Vec2<T>& Vec2<T>::operator=(const Vec2<T>& rhs)
{
  m_X = rhs.m_X;
  m_Y = rhs.m_Y;
  return *this;
}