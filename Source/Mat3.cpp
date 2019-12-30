#include "Math/Mat3.h"

const Mat3f & Mat3f::operator=(const Mat3f & rhs)
{
  m_XYZMM[0] = rhs.m_XYZMM[0];
  m_XYZMM[1] = rhs.m_XYZMM[1];
  return *this;
}

const Mat3f & Mat3f::operator+=(const Mat3f & rhs)
{
  m_XYZMM[0] = _mm256_add_ps(m_XYZMM[0], rhs.m_XYZMM[0]);
  m_XYZMM[1] = _mm256_add_ps(m_XYZMM[1], rhs.m_XYZMM[1]);
  return *this;
};

const Mat3f & Mat3f::operator-=(const Mat3f & rhs)
{
  m_XYZMM[0] = _mm256_sub_ps(m_XYZMM[0], rhs.m_XYZMM[0]);
  m_XYZMM[1] = _mm256_sub_ps(m_XYZMM[1], rhs.m_XYZMM[1]);
  return *this;
}

const Mat3f & Mat3f::operator*=(const Mat3f & rhs)
{
  // TODO: insert return statement here
  //float result[16] = {
  //x1 = m_XYZMat[0][0] * rhs.m_XYZMat[0][0] + m_XYZMat[0][1] * rhs.m_XYZMat[1][0] + m_XYZMat[0][2] * rhs.m_XYZMat[2][0],
  //y1 = m_XYZMat[0][0] * rhs.m_XYZMat[0][1] + m_XYZMat[0][1] * rhs.m_XYZMat[1][1] + m_XYZMat[0][2] * rhs.m_XYZMat[2][1],
  //z1 = m_XYZMat[0][0] * rhs.m_XYZMat[0][2] + m_XYZMat[0][1] * rhs.m_XYZMat[1][2] + m_XYZMat[0][2] * rhs.m_XYZMat[2][2],
  //w1,
  //x2 = m_XYZMat[1][0] * rhs.m_XYZMat[0][0] + m_XYZMat[1][1] * rhs.m_XYZMat[1][0] + m_XYZMat[1][2] * rhs.m_XYZMat[2][0],
  //y2 = m_XYZMat[1][0] * rhs.m_XYZMat[0][1] + m_XYZMat[1][1] * rhs.m_XYZMat[1][1] + m_XYZMat[1][2] * rhs.m_XYZMat[2][1],
  //z2 = m_XYZMat[1][0] * rhs.m_XYZMat[0][2] + m_XYZMat[1][1] * rhs.m_XYZMat[1][2] + m_XYZMat[1][2] * rhs.m_XYZMat[2][2],
  //w2,

  //x3 = m_XYZMat[2][0] * rhs.m_XYZMat[0][0] + m_XYZMat[2][1] * rhs.m_XYZMat[1][0] + m_XYZMat[2][2] * rhs.m_XYZMat[2][0],
  //y3 = m_XYZMat[2][0] * rhs.m_XYZMat[0][1] + m_XYZMat[2][1] * rhs.m_XYZMat[1][1] + m_XYZMat[2][2] * rhs.m_XYZMat[2][1],
  //z3 = m_XYZMat[2][0] * rhs.m_XYZMat[0][2] + m_XYZMat[2][1] * rhs.m_XYZMat[1][2] + m_XYZMat[2][2] * rhs.m_XYZMat[2][2],
  //w3,
  //0.f, 0.f, 0.f, 0.f
  //};
  float tmp1[4] = { rhs.m_XYZMat[0][0], rhs.m_XYZMat[1][0], rhs.m_XYZMat[2][0], 0.f };
  float tmp2[4] = { rhs.m_XYZMat[0][1], rhs.m_XYZMat[1][1], rhs.m_XYZMat[2][1], 0.f };
  float tmp3[4] = { rhs.m_XYZMat[0][2], rhs.m_XYZMat[1][2], rhs.m_XYZMat[2][2], 0.f };
  __m128 rhsXYZ1 = _mm_load_ps(tmp1);
  __m128 rhsXYZ2 =  _mm_load_ps(tmp2);
  __m128 rhsXYZ3 =  _mm_load_ps(tmp3);
  __m256 rhsXYZ8 = _mm256_set_m128(rhsXYZ1, rhsXYZ1);
  __m256 rhsXYZ18 = _mm256_set_m128(rhsXYZ2, rhsXYZ2);
  __m256 rhsXYZ28 = _mm256_set_m128(rhsXYZ3, rhsXYZ3);
  m_XYZMM[0] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[0], rhsXYZ8), _mm256_mul_ps(m_XYZMM[0], rhsXYZ18)),
                              _mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[0], rhsXYZ28), _mm256_setzero_ps()));
  m_XYZMM[1] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[1], rhsXYZ8), _mm256_mul_ps(m_XYZMM[1], rhsXYZ18)),
                              _mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[1], rhsXYZ28), _mm256_setzero_ps()));

  return *this;
}

const Mat3f & Mat3f::operator*=(float rhs)
{
  __m256 d = _mm256_set1_ps(rhs);
  m_XYZMM[0] = _mm256_mul_ps(m_XYZMM[0], d);
  m_XYZMM[1] = _mm256_mul_ps(m_XYZMM[1], d);
  return *this;
}

Vec3f Mat3f::operator*=(const Vec3f& rhs)
{
  __m256 r1 = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[0], _mm256_set_m128(rhs.GetXMM(), rhs.GetXMM())), 
                                            _mm256_mul_ps(m_XYZMM[1], _mm256_set_m128(rhs.GetXMM(), rhs.GetXMM()))),
                             _mm256_setzero_ps());
  return Vec3f(r1.m256_f32[0], 
               r1.m256_f32[4], 
               r1.m256_f32[1]);
}



const Mat3f & Mat3f::operator/=(const Mat3f & rhs)
{
  m_XYZMM[0] = _mm256_div_ps(m_XYZMM[0], rhs.m_XYZMM[0]);
  m_XYZMM[1] = _mm256_div_ps(m_XYZMM[1], rhs.m_XYZMM[1]);
  return *this;
}

const Mat3f & Mat3f::operator/=(float rhs)
{
  __m256 d = _mm256_set1_ps(rhs);
  m_XYZMM[0] = _mm256_div_ps(m_XYZMM[0], d);
  m_XYZMM[1] = _mm256_div_ps(m_XYZMM[1], d);
  return *this;
}
