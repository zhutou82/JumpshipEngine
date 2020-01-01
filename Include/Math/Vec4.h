#pragma once
#include "Common/CommonMath.h"

class Vec4f
{
  public:
  Vec4f(float x, float y, float z, float w) :
  m_XYZW {x, y, z, w} {}
  Vec4f(float xyzw = 0.f)
  :
  m_XYZW {xyzw, xyzw, xyzw, xyzw } {}
  Vec4f(const Vec4f& rhs) { *this = rhs;}
  const Vec4f& operator=(const Vec4f& rhs);
  const Vec4f& operator+=(const Vec4f& rhs);
  const Vec4f& operator-=(const Vec4f& rhs);
  const Vec4f& operator*=(const Vec4f& rhs);
  const Vec4f& operator*=(float rhs);
  const Vec4f& operator/=(const Vec4f& rhs);
  const Vec4f& operator/=(float rhs);
  const Vec4f& NormalizeThis();
  float Dot(const Vec4f& rhs) const;
  float Magnitude() const { return std::sqrt(Dot(*this)); }
  
  friend bool operator==(const Vec4f& lhs, const Vec4f& rhs) { return _mm_movemask_ps(_mm_cmpeq_ps(lhs.m_XYZWMM, rhs.m_XYZWMM)) == 0x0F; }

  friend std::ostream& operator<<(std::ostream& os, const Vec4f& rhs)
  {
    os << GLOBAL::BRACKET_O << rhs.m_XYZW[0] << GLOBAL::COMMA << rhs.m_XYZW[1] << GLOBAL::COMMA << rhs.m_XYZW[2] << GLOBAL::COMMA << rhs.m_XYZW[3] << GLOBAL::BRACKET_C;
    return os;
  }

  private:

  union { __m128 m_XYZWMM; float m_XYZW[4]; };

};

static Vec4f operator+(Vec4f lhs, const Vec4f& rhs) {return lhs += rhs; }
static Vec4f operator-(Vec4f lhs, const Vec4f& rhs) { return lhs -= rhs; }
static Vec4f operator*(Vec4f lhs, const Vec4f& rhs) { return lhs *= rhs; }
static Vec4f operator*(Vec4f lhs, float rhs) { return lhs *= rhs; }
static Vec4f operator/(Vec4f lhs, const Vec4f& rhs) { return lhs /= rhs; }
static Vec4f operator/(Vec4f lhs, float rhs) { return lhs /= rhs; }

namespace Vec4
{
  static float Dot (const Vec4f& lhs, const Vec4f& rhs) { return lhs.Dot(rhs); }
  static Vec4f Normalize (Vec4f lhs) {return lhs.NormalizeThis(); }
}