#include "Math/Mat4.h"

const Mat4f & Mat4f::operator=(const Mat4f & rhs)
{
  m_XYZWMM[0] = rhs.m_XYZWMM[0];
  m_XYZWMM[1] = rhs.m_XYZWMM[1];
  return *this;
}

const Mat4f & Mat4f::operator+=(const Mat4f & rhs)
{
  m_XYZWMM[0] = _mm256_add_ps(m_XYZWMM[0], rhs.m_XYZWMM[0]);
  m_XYZWMM[1] = _mm256_add_ps(m_XYZWMM[1], rhs.m_XYZWMM[1]);
  return *this;
}

const Mat4f & Mat4f::operator-=(const Mat4f & rhs)
{
  m_XYZWMM[0] = _mm256_sub_ps(m_XYZWMM[0], rhs.m_XYZWMM[0]);
  m_XYZWMM[1] = _mm256_sub_ps(m_XYZWMM[1], rhs.m_XYZWMM[1]);
  return *this;
}

int operator""_s(unsigned long long in)
{
  return 0;
}

#define s _s



const Mat4f & Mat4f::operator*=(const Mat4f & rhs)
{
  
  float x0 = m_XYZWMat[0][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][0];
  float y0 = m_XYZWMat[1][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][0];
  float z0 = m_XYZWMat[2][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][0];
  float w0 = m_XYZWMat[3][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][0];
                                                                                                                                   
  float x1 = m_XYZWMat[0][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][1];
  float y1 = m_XYZWMat[1][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][1];
  float z1 = m_XYZWMat[2][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][1];
  float w1 = m_XYZWMat[3][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][1];
                                                                                                                                  
  float x2 = m_XYZWMat[0][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][2];
  float y2 = m_XYZWMat[1][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][2];
  float z2 = m_XYZWMat[2][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][2];
  float w2 = m_XYZWMat[3][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][2];
                                                                                                                                   
  float x3 = m_XYZWMat[0][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][3];
  float y3 = m_XYZWMat[1][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][3];
  float z3 = m_XYZWMat[2][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][3];
  float w3 = m_XYZWMat[3][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][3];

  float x0w1[8] = { rhs.m_XYZWMat[0][0], rhs.m_XYZWMat[1][0], rhs.m_XYZWMat[2][0],  rhs.m_XYZWMat[3][0],
                    rhs.m_XYZWMat[0][0], rhs.m_XYZWMat[1][0], rhs.m_XYZWMat[2][0],  rhs.m_XYZWMat[3][0] };

  //__m256 r1 = _mm256_mul_ps(m_XYZWMM[0], ;


  return *this;
}

const Mat4f & Mat4f::operator*=(float rhs)
{
  m_XYZWMM[0] = _mm256_sub_ps(m_XYZWMM[0], _mm256_set1_ps(rhs));
  m_XYZWMM[1] = _mm256_sub_ps(m_XYZWMM[1], _mm256_set1_ps(rhs));
  return *this;
}

Vec4f Mat4f::operator*=(const Vec4f& rhs)
{
  __m256 r = _mm256_set_m128(rhs.GetMM(), rhs.GetMM());
  __m256 r1 = _mm256_mul_ps(m_XYZWMM[0], r);
  __m256 r2 = _mm256_mul_ps(m_XYZWMM[1], r);
  r = _mm256_hadd_ps(r1, r2);
  r = _mm256_hadd_ps(r, r);
  return Vec4f(r.m256_f32[0],
               r.m256_f32[4],
               r.m256_f32[1],
               r.m256_f32[5]);
}

const Mat4f & Mat4f::operator/=(const Mat4f & rhs)
{
  return *this;
}

const Mat4f & Mat4f::operator/=(float rhs)
{
  return *this;
}

const Mat4f & Mat4f::operator/=(const Vec4f & rhs)
{
  return *this; 
}

const Mat4f & Mat4f::TransposeThis()
{
  return *this;
}
