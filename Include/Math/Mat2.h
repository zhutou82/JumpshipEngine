#pragma once
#include "Common/CommonMath.h"
#include "Math/Vec2.h"

class Mat2f
{
  public:
   constexpr static  const int MAT2_ROW = 2;
   constexpr static  const int MAT2_COL = 2;


  Mat2f(float x1 = 0.f, float x2 = 0.f, float y1 = 0.f, float y2 = 0.f) 
  : m_XY {x1, x2, y1, y2}
  {
    m_XYMM = _mm_load_ps(m_XY);
  }
  Mat2f(const Mat2f& rhs){ *this = rhs;}
  const Mat2f& operator=(const Mat2f& rhs);
  bool         operator==(const Mat2f& rhs) { return _mm_movemask_ps(_mm_cmp_ps(m_XYMM, rhs.m_XYMM, _CMP_EQ_OQ)) == 0x0F; }
  const Mat2f& operator+=(const Mat2f& rhs);
  const Mat2f& operator-=(const Mat2f& rhs);
  const Mat2f& operator*=(const Mat2f& rhs);
  const Mat2f& operator*=(const Vec2f& rhs);
  const Mat2f& operator*=(float rhs);
  const Mat2f& operator/=(const Mat2f& rhs);
  const Mat2f& operator/=(float rhs);
  Vec2f GetRow(int index)    const;
  Vec2f GetColumn(int index) const;
  float GetValue(int xIndex, int yIndex) const { return m_XYMat[xIndex][yIndex]; }
  
  friend std::ostream& operator<<(std::ostream& os, const Mat2f& rhs)
  {
    os << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYMat[0][0] << GLOBAL::COMMA << rhs.m_XYMat[0][1] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE;
    os << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYMat[1][0] << GLOBAL::COMMA << rhs.m_XYMat[1][1] << GLOBAL::SQUARE_BRACKET_C;
    return os;
  }

  private:
  union 
  { 
    __m128 m_XYMM; 
    float m_XY[4]; 
    float m_XYMat[2][2]; 
  };
};

