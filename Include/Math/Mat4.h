#pragma once
#include "Common/CommonMath.h"

class Mat4f
{
  public:
  Mat4f(float x1, float x2, float x3, float x4,
        float y1, float y2, float y3, float y4,
        float z1, float z2, float z3, float z4, 
        float w1, float w2, float w3, float w4 ) 
        :
        m_XYZW {x1, x2, x3, x4,
                y1, y2, y3, y4,
                z1, z2, z3, z4,
                w1, w2, w3, w4} {}
  Mat4f(float x = 0.f)
  :
  m_XYZW{ x, x, x, x,
          x, x, x, x,
          x, x, x, x,
          x, x, x, x } {}



  friend std::ostream& operator<<(std::ostream& os, const Mat4f& rhs)
  {
    os << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[0][0] << GLOBAL::COMMA << rhs.m_XYZWMat[0][1] << GLOBAL::COMMA << rhs.m_XYZWMat[0][2] << GLOBAL::COMMA << rhs.m_XYZWMat[0][3] << GLOBAL::SQUARE_BRACKET_C <<  GLOBAL::NEW_LINE
       << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[1][0] << GLOBAL::COMMA << rhs.m_XYZWMat[1][1] << GLOBAL::COMMA << rhs.m_XYZWMat[1][2] << GLOBAL::COMMA << rhs.m_XYZWMat[1][3] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE
       << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[2][0] << GLOBAL::COMMA << rhs.m_XYZWMat[2][1] << GLOBAL::COMMA << rhs.m_XYZWMat[2][2] << GLOBAL::COMMA << rhs.m_XYZWMat[2][3] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE
       << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[3][0] << GLOBAL::COMMA << rhs.m_XYZWMat[3][1] << GLOBAL::COMMA << rhs.m_XYZWMat[3][2] << GLOBAL::COMMA << rhs.m_XYZWMat[3][3] << GLOBAL::SQUARE_BRACKET_C;

    return os;
  }
  private:
  union {
    __m256 m_XYZWMM[2];
    float m_XYZW[16];
    float m_XYZWMat[4][4];
  };
};