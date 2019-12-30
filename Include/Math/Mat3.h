#pragma once
#include "Common/CommonMath.h"
#include "Math/Vec3.h"

class Mat3f
{
  public:
  Mat3f(float x1 = 0.f, float y1 = 0.f, float z1 = 0.f, 
        float x2 = 0.f, float y2 = 0.f, float z2 = 0.f,
        float x3 = 0.f, float y3 = 0.f, float z3 = 0.f )
  :
  m_XYZ {x1, y1, z1, 0.f,
         x2, y2, z2, 0.f,
         x3, y3, z3, 0.f,
         0.f, 0.f, 0.f, 0.f} {}
  Mat3f(const Mat3f& rhs) {*this = rhs;} 
  const Mat3f& operator=(const Mat3f& rhs);
  bool         operator==(const Mat3f& rhs) {return _mm256_movemask_ps(_mm256_cmp_ps(m_XYZMM[0], rhs.m_XYZMM[0], _CMP_EQ_OQ)) == 0xFF &&
                                                    _mm256_movemask_ps(_mm256_cmp_ps(m_XYZMM[1], rhs.m_XYZMM[1], _CMP_EQ_OQ)) == 0xFF;}
  const Mat3f& operator+=(const Mat3f& rhs);
  const Mat3f& operator-=(const Mat3f& rhs);
  const Mat3f& operator*=(const Mat3f& rhs);
  const Mat3f& operator*=(float);
  Vec3f        operator*=(const Vec3f& rhs);
  const Mat3f& operator/=(const Mat3f& rhs);
  const Mat3f& operator/=(float rhs);
  friend std::ostream& operator<<(std::ostream& os, const Mat3f& rhs)
  {
    os << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZMat[0][0] << GLOBAL::COMMA << rhs.m_XYZMat[0][1] << GLOBAL::COMMA << rhs.m_XYZMat[0][2] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE
       << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZMat[1][0] << GLOBAL::COMMA << rhs.m_XYZMat[1][1] << GLOBAL::COMMA << rhs.m_XYZMat[1][2] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE
       << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZMat[2][0] << GLOBAL::COMMA << rhs.m_XYZMat[2][1] << GLOBAL::COMMA << rhs.m_XYZMat[2][2] << GLOBAL::SQUARE_BRACKET_C;                       
    return os;
  }

  private:
  
  union
  {
    __m256 m_XYZMM[2];
    float m_XYZ[16];
    float m_XYZMat[4][4];
  };

};