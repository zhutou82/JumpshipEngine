#pragma once
#include <iostream>
#include <vector>
#include "Math/JSMath.h"

namespace JSMathTestCaseMacroMethod
{
  void TestJSVec2Class();
  void TestJSVec3Class();
  //void TestJSVec4Class();
  void TestJSMat2Class();
  void TestJSMat3Class();
}

namespace JSMathTestCaseTemplateMethod
{
  void TestJSVec4Class();
  void TestJSMat4Class();
}

namespace JSMathStreeTest
{
  void TestJSMat3Class();
  void TestJSMat4Class();
}

//#include <iostream>
//#include <vector>
//#include <functional>
//#include "Math/JSMath.h"
////template <typename T>
////bool(*vec2Testcases[])(const T& t1, const T& t2);
//
//template <typename T>
//std::vector<bool(*)(const T&, const T&)> VecTestcasesVector;
////namespace JSMathTestingcase
//
//#define PrintFnName std::cout << __FUNCTION__ << GLOBAL::NEW_LINE;
//bool TestAssignment(const Vec2f& t1, const Vec2f& t2)
//{
//  PrintFnName
//    Vec2f v = t1;
//  return v == Vec2f(1, 2);
//}
//bool TestOpeartorplus(const Vec2f& t1, const Vec2f& t2)
//{
//  PrintFnName
//    Vec2f tmp = t1;
//  //return (Vec2f(t1) += t2) == Vec2f(1, 2);
//  return false;
//}
//
//void TestJSVec2()
//{
//  std::cout << "Testing Vec2f class" << std::endl;
//  Vec2f TestObj1(1, 2);
//  Vec2f TestObj2(3, 4);
//  TestObj1 += TestObj2;
//
//  VecTestcasesVector<Vec2f>.push_back(TestAssignment);
//  for (size_t i = 0, n = VecTestcasesVector<Vec2f>.size(); i < n; ++i)
//  {
//    std::cout << "Testcase " << i + 1 << GLOBAL::COLON;
//    std::cout << (VecTestcasesVector<Vec2f>[i](TestObj1, TestObj2) ? GLOBAL::JSPASS : GLOBAL::JSFAIL) << GLOBAL::NEW_LINE;
//  }
//
//}

//void TestJSVec2();

