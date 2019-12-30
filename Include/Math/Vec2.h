#pragma once
#include "Common/CommonMath.h"
class Vec2f
{ 
public:
  //constructor
  Vec2f(float x = 0.f, float y = 0.f);
  Vec2f(const Vec2f& rhs) { *this = rhs; }
  //operator overloading
  const Vec2f& operator+=(const Vec2f& rhs);
  const Vec2f  operator-=(const Vec2f& rhs);
  const Vec2f& operator*=(const Vec2f& rhs);
  const Vec2f& operator*=(float rhs);
  const Vec2f& operator=(const Vec2f& rhs);
  const Vec2f& operator/=(const Vec2f& rhs);
  const Vec2f& operator/=(float rhs);
  /*
  An ordered comparison checks if neither operand is NaN.
  Conversely, an unordered comparison checks if either operand is a NaN.

  Signaling (S) vs non-signaling (Q for quiet) will
  determine whether an exception is raised if an operand contains a NaN.
  */
  //bool         operator==(const Vec2f& rhs) const { return  _mm_movemask_ps(_mm_cmp_ps(m_XYMM, rhs.m_XYMM, _CMP_EQ_OQ)) == 0x0F; }
  float        Dot(const Vec2f& rhs) const;
  const float* GetValueInPtr() const {return m_XY; }
  void         SetValue(int index, float v) { m_XY[index] = v; }
  float        Magnitude();
  const Vec2f& NormalizeThis();
  Vec2f        Normalize() const;
  
  friend bool operator==(const Vec2f& lhs, const Vec2f& rhs) { return _mm_movemask_ps(_mm_cmp_ps(lhs.m_XYMM, rhs.m_XYMM, _CMP_EQ_OQ)) == 0x0F; }
  friend std::ostream& operator<<(std::ostream& os, const Vec2f& rhs) { os << "(" << rhs.m_XY[0] << ", " << rhs.m_XY[1] << ")"; return os;}
private:
  union { __m128 m_XYMM; float m_XY[4]; };
};
class Vec2i
{
  public:
  //operator overloading
  const Vec2i& operator+=(const Vec2i& rhs) { m_XY[0] += rhs.m_XY[0]; m_XY[1] += rhs.m_XY[1]; }
  const Vec2i& operator-=(const Vec2i& rhs) { m_XY[0] -= rhs.m_XY[0]; m_XY[1] -= rhs.m_XY[1]; }
  const Vec2i& operator*=(const Vec2i& rhs) { m_XY[0] *= rhs.m_XY[0]; m_XY[1] *= rhs.m_XY[1]; }
  const Vec2i& operator=(const Vec2i& rhs)  { m_XY[0] = rhs.m_XY[0]; m_XY[1] = rhs.m_XY[1]; }
  bool operator==(const Vec2i& rhs)         { return m_XY[0] == rhs.m_XY[0] && m_XY[1] == rhs.m_XY[1]; }
  int Dot(const Vec2i& rhs)                 { return m_XY[0] * rhs.m_XY[0] + m_XY[1] * rhs.m_XY[1]; }
  friend std::ostream& operator<<(std::ostream& os, const Vec2i& rhs){ os << "(" << rhs.m_XY[0] << ", " << rhs.m_XY[1] << ")"; return os;}
  private:
  int m_XY[2];
};

static const Vec2f operator+(Vec2f lhs, const Vec2f& rhs) { return lhs += rhs; }
static const Vec2f operator-(Vec2f lhs, const Vec2f& rhs) { return lhs -= rhs; }
static const Vec2f operator*(Vec2f lhs, const Vec2f& rhs) { return lhs *= rhs; }
//static bool operator == (const Vec2f& lhs, const Vec2f& rhs) {return lhs.operator==(rhs); }

namespace Vec2
{
  static float Dot(const Vec2f& lhs, const Vec2f& rhs) { return lhs.Dot(rhs); }
  static Vec2f Normalize(const Vec2f& rhs) { return rhs.Normalize(); }
}