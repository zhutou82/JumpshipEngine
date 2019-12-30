#include "Math/Vec2.h"

Vec2f::Vec2f(float x, float y)
:
 m_XY{ x, y, 0.f, 0.f }
{
  m_XYMM = _mm_load_ps(m_XY);
}
const Vec2f & Vec2f::operator=(const Vec2f & rhs)
{
  m_XYMM = rhs.m_XYMM;
  return *this;
}
const Vec2f & Vec2f::operator/=(const Vec2f & rhs)
{
  m_XYMM = _mm_div_ps(m_XYMM, rhs.m_XYMM);
  return *this;
}
const Vec2f & Vec2f::operator/=(float rhs)
{
  m_XYMM = _mm_div_ps(m_XYMM, _mm_load_ps1(&rhs));
  return *this;
}
const Vec2f & Vec2f::operator+=(const Vec2f & rhs)
{
  m_XYMM = _mm_add_ps(m_XYMM, rhs.m_XYMM);
  return *this;   
}
const Vec2f Vec2f::operator-=(const Vec2f & rhs)
{
  m_XYMM = _mm_sub_ps(m_XYMM, rhs.m_XYMM);
  return *this;
}
const Vec2f& Vec2f::operator*=(const Vec2f & rhs)
{
  m_XYMM = _mm_mul_ps(m_XYMM, rhs.m_XYMM);
  return *this;
}
const Vec2f & Vec2f::operator*=(float rhs)
{
  m_XYMM = _mm_mul_ps(m_XYMM, _mm_load_ps1(&rhs));
  return *this;
}



float Vec2f::Dot(const Vec2f & rhs) const
{
  __m128 result = _mm_mul_ps(m_XYMM, rhs.m_XYMM);
  return _mm_hadd_ps(result, result).m128_f32[0];
}

float Vec2f::Magnitude()
{
  return sqrt(Dot(*this));
  //return sqrt(m_XY[0] * m_XY[0] + m_XY[1] * m_XY[1]);
}

const Vec2f& Vec2f::NormalizeThis()
{
  float mag = Magnitude();
  m_XYMM = _mm_div_ps(m_XYMM, _mm_load_ps1(&mag));
  _mm_store_ps(m_XY, m_XYMM);
  return *this;
}

Vec2f Vec2f::Normalize() const
{
  Vec2f result = *this;
  return result.NormalizeThis();
}


