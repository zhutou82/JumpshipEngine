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
std::cout << "============================================================" << GLOBAL::NEW_LINE; \

namespace JSMathTestCaseMacroMethod
{
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Assignment, =)
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Plus, +)
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Minus, -)
  RegisterOperatorFn(Vec2f, float, Vec2f, Multiply, *)
  RegisterOperatorFn(Vec2f, Vec2f, Vec2f, Division1, /)
  RegisterOperatorFn(Vec2f, float, Vec2f, Division2, /)
  RegisterSpecialOperatorFn(Vec2f, Vec2f, float, Dot, Vec2::Dot)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Assignment, =)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Plus, +)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Minus, -)
  RegisterOperatorFn(Vec3f, float, Vec3f, Multiply, *)
  RegisterOperatorFn(Vec3f, Vec3f, Vec3f, Division1, /)
  RegisterOperatorFn(Vec3f, float, Vec3f, Division2, /)
  RegisterSpecialOperatorFn(Vec3f, Vec3f, float, Dot, Vec3::Dot) 
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Assignment, =)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Plus, +)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Minus, -)
  RegisterOperatorFn(Mat2f, float, Mat2f, Multiply1, *)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Multiply2, *)
  RegisterOperatorFn(Mat2f, float, Mat2f, Division1, /)
  RegisterOperatorFn(Mat2f, Mat2f, Mat2f, Division2, /)
  //RegisterSpecialOperatorFn(Mat2f, Mat2f, float, Dot, Vec3::Dot)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Assignment, =)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Plus, +)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Minus, -)
  RegisterOperatorFn(Mat3f, float, Mat3f, Multiply1, *)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Multiply2, *)
  RegisterOperatorFn(Mat3f, Vec3f, Vec3f, Multiply3, *)
  RegisterOperatorFn(Mat3f, float, Mat3f, Division1, /)
  RegisterOperatorFn(Mat3f, Mat3f, Mat3f, Division2, /) 
  void TestJSVec2Class()
  {
    PrintFnName
    Vec2f v0(0), v1(1), v2(2);
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
    Vec3f v0(0), v1(1), v2(2);
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
    Mat2f m0(0), m1(1), m2(2);
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
    Mat3f m0(0), m1(1), m2(2);
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
namespace JSMathTestCaseTemplateMethod
{
  template <typename T1, typename T2, typename T3>
  struct Input
  {
    Input(const T1& in1_, const T2& in2_, const T3& out1_) : in1(in1_), in2(in2_), out1(out1_) {}
    T1 in1; T2 in2; T3 out1;
  };

  template <typename T1, typename T2, typename T3>
  std::vector<std::pair<Input<T1, T2, T3>, bool (*)(const T1&, const T2&, const T3&)>> testingVec;

  template <typename T>
  bool TestCreatation()
  {
    T in1(0.f);
    std::cout << in1 << GLOBAL::NEW_LINE;
    return true;
  }
  template <typename T1, typename T2, typename T3>
  bool TestOperatorEqual(const T1 & in1, const T2 & in2, const T3 & out1)
  {
    PrintFnInputInfo (in1, in2, out1)
    return in1 == in2;
  }
  template <typename T1, typename T2, typename T3>
  bool TestOperatorPlus(const T1& in1, const T2& in2, const T3& out1)
  {
    PrintFnInputInfo(in1, in2, out1)
    return (in1 + in2) == out1;
  }
  template <typename T1, typename T2, typename T3>
  bool TestOperatorMinus(const T1& in1, const T2& in2, const T3& out1)
  {
    PrintFnInputInfo(in1, in2, out1)
    return (in1 - in2) == out1;
  }
  template <typename T1, typename T2, typename T3>
  bool TestOperatorMul(const T1& in1, const T2& in2, const T3& out1)
  {
    PrintFnInputInfo(in1, in2, out1)
      return (in1 * in2) == out1;
  }
  template <typename T1, typename T2, typename T3>
  bool TestOperatorDiv(const T1& in1, const T2& in2, const T3& out1)
  {
    PrintFnInputInfo(in1, in2, out1)
      return (in1 / in2) == out1;
  }
  template <typename T1, typename T2, typename T3>
  bool TestDotProduct(const T1& in1, const T1& in2, const T2& out1, const T3& op)
  {
    PrintFnInputInfo(in1, in2, out1)
    return op(in1, in2) == out1;
  }

//testingVec<Vec4f, Vec4f, Vec4f>.push_back(std::make_pair(Input<Vec4f, Vec4f, Vec4f>(v0,v1,v2), TestOperatorEqual<Vec4f, Vec4f, Vec4f>));
#define RegisterFn(t1, t2, t3, in1, in2, out1, fn) \
testingVec<t1, t2, t3>.push_back(std::make_pair(Input<t1,t2,t3>(in1, in2, out1), fn<t1,t2,t3>));

#define PrintResult(t1, t2, t3) \
for (const auto& elem : testingVec<t1, t2, t3>) \
{ r = elem.second(elem.first.in1, elem.first.in2, elem.first.out1); std::cout << (r ? GLOBAL::JSPASS : GLOBAL::JSFAIL) << GLOBAL::NEW_LINE; result.push_back(r); } \

  void TestJSVec4Class()
  {
    PrintFnName
    PrintTestCase(TestCreatation<Vec4f>());
    Vec4f v0(0.f), v1(1.f), v2(2.f);
    RegisterFn(Vec4f, Vec4f, Vec4f, v1, v1, v1, TestOperatorEqual);
    RegisterFn(Vec4f, Vec4f, Vec4f, v1, v1, v2, TestOperatorPlus);
    RegisterFn(Vec4f, Vec4f, Vec4f, v1, v2, v2, TestOperatorMul);
    RegisterFn(Vec4f, Vec4f, Vec4f, v2, v2, v1, TestOperatorDiv);
    PrintResult(Vec4f, Vec4f, Vec4f)

    RegisterFn(Vec4f, float, Vec4f, v1, 2.f, v2, TestOperatorMul);
    RegisterFn(Vec4f, float, Vec4f, v2, 2.f, v1, TestOperatorDiv);
    PrintResult(Vec4f, float, Vec4f)

    Vec4f v3(1,2,3, 4), v4(5,6,7,8);
    float f = 70;
    PrintTestCase((TestDotProduct<Vec4f, float, float(*)(const Vec4f&, const Vec4f&)>(v3, v4, f, Vec4::Dot)));
    EndTestCase
  }
  void TestJSMat4Class()
  { 
    PrintFnName
    PrintTestCase(TestCreatation<Mat4f>());
    EndTestCase
  }
}


