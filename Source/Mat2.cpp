#include "Math/Mat2.h"
#include "Math/JSMath.h"

const Mat2f & Mat2f::operator=(const Mat2f & rhs)
{
  m_XYMM = rhs.m_XYMM;
  return *this;
}

const Mat2f & Mat2f::operator+=(const Mat2f & rhs)
{
  m_XYMM = _mm_add_ps(m_XYMM, rhs.m_XYMM);
  return *this;
}

const Mat2f & Mat2f::operator-=(const Mat2f & rhs)
{
  m_XYMM = _mm_sub_ps(m_XYMM, rhs.m_XYMM);
  return *this;
}
const Mat2f& Mat2f::operator*=(const Mat2f & rhs)
{
  //Mat2f m1(7, 10, 15, 22);
  //float x1 = m_XYMat[0][0] * rhs.m_XYMat[0][0] + m_XYMat[0][1] * rhs.m_XYMat[1][0];
  //float x2 = m_XYMat[0][0] * rhs.m_XYMat[0][1] + m_XYMat[0][1] * rhs.m_XYMat[1][1];
  //float y1 = m_XYMat[1][0] * rhs.m_XYMat[0][0] + m_XYMat[1][1] * rhs.m_XYMat[1][0];
  //float y2 = m_XYMat[1][0] * rhs.m_XYMat[0][1] + m_XYMat[1][1] * rhs.m_XYMat[1][1];
  float X1y1[] = { m_XYMat[0][0], m_XYMat[0][1], m_XYMat[0][0], m_XYMat[0][1] };
  float X2y2[] = { m_XYMat[1][0], m_XYMat[1][1], m_XYMat[1][0], m_XYMat[1][1] };
  float rhsX1y1[] = { rhs.m_XYMat[0][0], rhs.m_XYMat[1][0], rhs.m_XYMat[0][1], rhs.m_XYMat[1][1] };
  //float rhsX2y2[] = { rhs.m_XYMat[0][1], rhs.m_XYMat[1][1], rhs.m_XYMat[0][1], rhs.m_XYMat[1][1] };
  _mm_store_ps(m_XY, _mm_hadd_ps(_mm_mul_ps(_mm_load_ps(X1y1), _mm_load_ps(rhsX1y1)),
                                 _mm_mul_ps(_mm_load_ps(X2y2), _mm_load_ps(rhsX1y1))));
  return *this; 
}
const Mat2f & Mat2f::operator*=(const Vec2f & rhs)
{
  m_XYMM = _mm_mul_ps(m_XYMM,_mm_load_ps(rhs.GetValueInPtr()));
  return *this;
}
const Mat2f & Mat2f::operator*=(float rhs)
{
  m_XYMM = _mm_mul_ps(m_XYMM, _mm_load_ps1(&rhs));
  return *this;
}
const Mat2f & Mat2f::operator/=(const Mat2f & rhs)
{
  m_XYMM = _mm_div_ps(m_XYMM, rhs.m_XYMM);
  return *this;
}
const Mat2f & Mat2f::operator/=(float rhs)
{
  m_XYMM = _mm_div_ps(m_XYMM, _mm_load_ps1(&rhs));
  return *this;
}
Vec2f Mat2f::GetRow(int index) const
{
  return Vec2f(m_XYMat[index][0], m_XYMat[index][1]);
}
Vec2f Mat2f::GetColumn(int index) const
{
  Vec2f v;
  for (int i = 0; i < MAT2_ROW; ++i) v.SetValue(i, m_XYMat[i][index]);
  return v;
}