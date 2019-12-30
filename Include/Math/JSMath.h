#pragma once
#include "Common/CommonMath.h"
#include "Math/Vec2.h"
#include "Math/Mat2.h"
#include "Math/Vec3.h"
#include "Math/Mat3.h"


//static const Vec2i operator+(Vec2i lhs, const Vec2i& rhs) { return lhs += rhs; }
//static const Vec2i operator-(Vec2i lhs, const Vec2i& rhs) { return lhs -= rhs; }
//static const Vec2i operator*(Vec2i lhs, const Vec2i& rhs) { return lhs *= rhs; }
//static int Dot(Vec2i lhs, const Vec2i& rhs) { return lhs.Dot(rhs); }

//namespace Mat2
//{
//  static const Mat2f Transpose(const Mat2f& mat2f)
//  {
//    return Mat2f(mat2f.GetValue(0, 0), mat2f.GetValue(1, 0),
//                 mat2f.GetValue(0, 1), mat2f.GetValue(1, 1));
//  }
//}


//namespace Vec3
//{
//  const Vec2f operator+(Vec2f lhs, const Vec2f& rhs) { return lhs += rhs; }
//  const Vec2f operator-(Vec2f lhs, const Vec2f& rhs) { return lhs -= rhs; }
//  const Vec2f operator*(Vec2f lhs, const Vec2f& rhs) { return lhs *= rhs; }
//
//  const Vec2i operator+(Vec2i lhs, const Vec2i& rhs) { return lhs += rhs; }
//  const Vec2i operator-(Vec2i lhs, const Vec2i& rhs) { return lhs -= rhs; }
//  const Vec2i operator*(Vec2i lhs, const Vec2i& rhs) { return lhs *= rhs; }
//
//}