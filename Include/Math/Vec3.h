#pragma once
#include "Common/CommonMath.h"

class Vec3f
{
  public:
  Vec3f(float x = 0.f, float y = 0.f, float z = 0.f)
  :
  m_XYZ{ x, y, z, 0.f } {}
  Vec3f(const Vec3f& rhs) {*this = rhs;}
  const Vec3f& operator=(const Vec3f& rhs);
  bool         operator==(const Vec3f& rhs) { return _mm_movemask_ps(_mm_cmpeq_ps(m_XYZMM, rhs.m_XYZMM)) == 0x0F; }
  const Vec3f& operator+=(const Vec3f& rhs);
  const Vec3f& operator-=(const Vec3f& rhs);
  const Vec3f& operator*=(const Vec3f& rhs);
  const Vec3f& operator*=(float rhs);
  const Vec3f& operator/=(const Vec3f& rhs);
  const Vec3f& operator/=(float rhs);
  float        Magnitude() const { return sqrt(Dot(*this)); }
  float        Dot(const Vec3f& rhs) const;
  Vec3f        Normalize() const;
  const Vec3f& NormalizeThis();
  const __m128& GetXMM() const {return m_XYZMM;}
  
  friend std::ostream& operator<<(std::ostream& os, const Vec3f& rhs)
  {
    os << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZ[0] << GLOBAL::COMMA << rhs.m_XYZ[1] << GLOBAL::COMMA << rhs.m_XYZ[2] << GLOBAL::SQUARE_BRACKET_C;
    return os;
  }

  private:
  union { __m128 m_XYZMM; float m_XYZ[4]; };
};

static const Vec3f operator+(Vec3f lhs, const Vec3f& rhs) { return lhs += rhs; }
static const Vec3f operator-(Vec3f lhs, const Vec3f& rhs) { return lhs -= rhs; }
static const Vec3f operator*(Vec3f lhs, const Vec3f& rhs) { return lhs *= rhs; }
//static bool operator == (const Vec3f& lhs, const Vec3f& rhs) {return lhs.operator==(rhs); }

namespace Vec3
{
  static float Dot(const Vec3f& lhs, const Vec3f& rhs) { return lhs.Dot(rhs); }
  static Vec3f Normalize(const Vec3f& rhs) { return rhs.Normalize(); }
}