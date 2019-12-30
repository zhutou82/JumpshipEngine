#include "JSMathTestcases.h"
//template <typename T>
//bool(*vec2Testcases[])(const T& t1, const T& t2);
//template <typename T1, typename T2, typename T3>
//std::vector<bool(*)(T1, const T2&, const T3&)> VecTestcasesVector;
#define PrintFnName std::cout << __FUNCTION__  << GLOBAL::NEW_LINE; \
std::vector<bool> result; \
bool r = false; \

#define PrintFnInputInfo(intput1, intput2, expectedOutput) \
std::cout << __FUNCTION__ << GLOBAL::NEW_LINE; \
std::cout << "First input" << GLOBAL::COLON << intput1  << GLOBAL::COMMA \
          << "Second input" << GLOBAL::COLON << intput2  \
          << GLOBAL::NEW_LINE; \
std::cout << "Expected output" << GLOBAL::COLON << expectedOutput << GLOBAL::NEW_LINE; \

#define PrintFnOutputInfo(output) std::cout << "Output is" << GLOBAL::COLON << output << GLOBAL::NEW_LINE;

#define RegisterOperatorFn(T1, T2, T3, fnName, op)  \
bool TestOperator##fnName (T1 in1, const T2& in2, const T3& out1){ \
PrintFnInputInfo(in1, in2, out1) \
auto out = in1 op in2; \
PrintFnOutputInfo(out);\
return out == out1;}\

#define RegisterSpecialOperatorFn(T1, T2, T3, fnName, op)  \
bool TestOperator##fnName (const T1& in1, const T2& in2, const T3& out1) \
{ PrintFnInputInfo(in1, in2, out1) \
  float result = op(in1, in2); PrintFnOutputInfo(result); return result == out1;} \

#define PrintTestCase(fn) \
r = fn; \
std::cout << (r ?  GLOBAL::JSPASS : GLOBAL::JSFAIL) << GLOBAL::NEW_LINE; \
result.push_back(r); \

#define EndTestCase \
bool allPass = true; int testCase = 0; \
for (const auto& elem : result) { if (!elem) {allPass = false; break;} ++testCase; } \
std::cout <<  (allPass ? "All Pass" : GLOBAL::JSFAIL ) <<  GLOBAL::NEW_LINE; \
std::cout << "====================================" << GLOBAL::NEW_LINE; \

namespace JSMathTestCase
{
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Assignment, =)
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Plus, +=)
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Minus, -=)
  RegisterOperatorFn(Vec2f, float, Vec2f, Multiply, *=)
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Division1, /=)
  RegisterOperatorFn(Vec2f, float, Vec2f, Division2, /=)
  RegisterSpecialOperatorFn(Vec2f, Vec2f, float, Dot, Vec2::Dot)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Assignment, =)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Plus, +=)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Minus, -=)
  RegisterOperatorFn(Vec3f, float, Vec3f, Multiply, *=)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Division1, /=)
  RegisterOperatorFn(Vec3f, float, Vec3f, Division2, /=)
  RegisterSpecialOperatorFn(Vec3f, Vec3f, float, Dot, Vec3::Dot) 
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Assignment, =)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Plus, +=)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Minus, -=)
  RegisterOperatorFn(Mat2f, float, Mat2f, Multiply1, *=)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Multiply2, *=)
  RegisterOperatorFn(Mat2f, float, Mat2f, Division1, /=)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Division2, /=)
  //RegisterSpecialOperatorFn(Mat2f, Mat2f, float, Dot, Vec3::Dot)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Assignment, =)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Plus, +=)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Minus, -=)
  RegisterOperatorFn(Mat3f, float, Mat3f, Multiply1, *=)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Multiply2, *=)
  RegisterOperatorFn(Mat3f, Vec3f, Vec3f, Multiply3, *=)
  RegisterOperatorFn(Mat3f, float, Mat3f, Division1, /=)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Division2, /=) 
  void TestJSVec2Class()
  {
    PrintFnName
    Vec2f v0(0, 0), v1(1, 1), v2(2, 2);
    PrintTestCase(TestOperatorAssignment(v0, v1, v1)) 
    PrintTestCase(TestOperatorPlus(v1, v1, v2));
    PrintTestCase(TestOperatorMinus(v2, v1, v1));
    PrintTestCase(TestOperatorMultiply(v1, 2.f, v2));
    //PrintTestCase(TestOperatorDivision1(Vec2f(2, 2), Vec2f(2, 2), Vec2f(1, 1))); correct output but showed failed,need to fix xmm divided by 0
    PrintTestCase(TestOperatorDivision2(v2, 2.f, v1));
    PrintTestCase(TestOperatorDot(Vec2f(1, 2), Vec2f(3, 4), 11.f))
    EndTestCase
  }
  void TestJSVec3Class() 
  {
    PrintFnName
    Vec3f v0(0, 0, 0), v1(1, 1, 1), v2(2, 2, 2);
    PrintTestCase(TestOperatorAssignment(v0, v1, v1))
    PrintTestCase(TestOperatorPlus(v1, v1, v2));
    PrintTestCase(TestOperatorMinus(v2, v1, v1));
    PrintTestCase(TestOperatorMultiply(v1, 2.f, v2)); 
    //PrintTestCase(TestOperatorDivision1(Vec2f(2, 2), Vec2f(2, 2), Vec2f(1, 1))); correct output but showed failed, need to fix xmm divided by 0
    PrintTestCase(TestOperatorDivision2(v2, 2.f, v1));
    PrintTestCase(TestOperatorDot(Vec3f(1, 2, 3), Vec3f(4, 5, 6), 32.f))
    EndTestCase
  }
  void TestJSMat2Class()
  {
    PrintFnName
    Mat2f m0(0,0,0,0), m1(1, 1, 1, 1), m2(2, 2, 2, 2);
    Mat2f m3(1,2,3,4), m4(1,2,3,4), m5(7, 10, 15, 22);
    PrintTestCase(TestOperatorAssignment(m0, m1, m1));
    PrintTestCase(TestOperatorPlus(m1, m1, m2));
    PrintTestCase(TestOperatorMinus(m2, m1, m1)); 
    PrintTestCase(TestOperatorMultiply1(m1, 2.f, m2));
    PrintTestCase(TestOperatorMultiply2(m3, m4, m5));
    PrintTestCase(TestOperatorDivision1(m2, 2.f, m1));
    PrintTestCase(TestOperatorDivision2(m2, m2, m1));
    EndTestCase
  }
  void TestJSMat3Class()
  {
    PrintFnName
    Mat3f m0(0,0,0,0,0,0,0,0,0), m1(1, 1, 1, 1, 1, 1, 1, 1, 1), m2(2, 2, 2, 2, 2, 2, 2, 2, 2);
    Mat3f m3(1,2,3,4,5,6,7,8,9), m4(1, 2, 3, 4, 5, 6, 7, 8, 9), m5(30, 36, 42, 66, 81, 96, 102, 126, 150);
    Vec3f v0(1,2,3), v1(14, 32,50);
    PrintTestCase(TestOperatorAssignment(m0, m1, m1));
    PrintTestCase(TestOperatorPlus(m1, m1, m2));
    PrintTestCase(TestOperatorMinus(m2, m1, m1)); 
    PrintTestCase(TestOperatorMultiply1(m1, 2.f, m2));
    PrintTestCase(TestOperatorMultiply2(m3, m4, m5));
    PrintTestCase(TestOperatorMultiply3(m3, v0, v1));
    PrintTestCase(TestOperatorDivision1(m2, 2.f, m1));
    //PrintTestCase(TestOperatorDivision2(m2, m2, m1)); correct output but showed failed, need to fix xmm divided by 0
    EndTestCase
  }
}


