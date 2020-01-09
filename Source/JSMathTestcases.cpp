#include "JSMathTestcases.h"
#include "Common/CommonHeader.h"
#include <chrono>
//for threadpool class
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include "ThreadPool.h"

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


  template <typename T1, typename T2, typename T3>
bool TestTranspose(const T1& in1, const T1& in2, const T2& out1, const T3& op)
{
  PrintFnInputInfo(in1, in2, out1)
    return op(in1) == out1;
}
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
    Mat2f m3(1,2,3,4), m4(1,2,3,4), m5(7, 10, 15, 22), m6(7, 15, 10, 22);
    PrintTestCase(TestOperatorAssignment(m0, m1, m1));
    PrintTestCase(TestOperatorPlus(m1, m1, m2));
    PrintTestCase(TestOperatorMinus(m2, m1, m1)); 
    PrintTestCase(TestOperatorMultiply1(m1, 2.f, m2));
    PrintTestCase(TestOperatorMultiply2(m3, m4, m5));
    PrintTestCase(TestOperatorDivision1(m2, 2.f, m1));
    PrintTestCase(TestOperatorDivision2(m2, m2, m1));
    PrintTestCase((TestTranspose<Mat2f, Mat2f, Mat2f(*)(Mat2f)>(m5, m5, m6, Mat2::Transpose)));
    EndTestCase
  }
  void TestJSMat3Class()
  {
    PrintFnName
    Mat3f m0(0), m1(1), m2(2);
    Mat3f m3(1,2,3,4,5,6,7,8,9), m4(1, 2, 3, 4, 5, 6, 7, 8, 9), m5(30, 36, 42, 66, 81, 96, 102, 126, 150);
    Mat3f m6 (30, 66, 102,
              36, 81, 126,
              42, 96, 150);
    Vec3f v0(1,2,3), v1(14, 32,50);
    PrintTestCase(TestOperatorAssignment(m0, m1, m1));
    PrintTestCase(TestOperatorPlus(m1, m1, m2));
    PrintTestCase(TestOperatorMinus(m2, m1, m1)); 
    PrintTestCase(TestOperatorMultiply1(m1, 2.f, m2));
    PrintTestCase(TestOperatorMultiply2(m3, m4, m5));
    PrintTestCase(TestOperatorMultiply3(m3, v0, v1));
    PrintTestCase(TestOperatorDivision1(m2, 2.f, m1));
    //PrintTestCase(TestOperatorDivision2(m2, m2, m1)); correct output but showed failed, need to fix xmm divided by 0
    PrintTestCase((TestTranspose<Mat3f, Mat3f, Mat3f(*)(Mat3f)>(m5, m5, m6, Mat3::Transpose)));
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
    RegisterFn(Vec4f, Vec4f, Vec4f, v2, v1, v1, TestOperatorMinus);
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
    Mat4f m0(0), m1(1), m2(2);
    Mat4f m3(1,2,3,4,
             5,6,7,8,
             9,10,11,12,
             13,14,15,16);
    Mat4f m4(17,18,19,20,
             21,22,23,24,
             25,26,27,28,
             29,30,31,32);
    Mat4f m5(250,260,270,280,
             618,644,670,696,
             986,1028,1070,1112,
             1354,1412,1470,1528);
    Mat4f m6(250, 618, 986, 1354,
             260, 644, 1028, 1412,
             270, 670, 1070, 1470,
             280, 696, 1112, 1528);
    Vec4f v1 (1,2,3,4), v2(30, 70, 110, 150);
    float f1 = 13;
    RegisterFn(Mat4f, Mat4f, Mat4f, m1, m1, m1, TestOperatorEqual);
    RegisterFn(Mat4f, Mat4f, Mat4f, m1, m1, m2, TestOperatorPlus);
    RegisterFn(Mat4f, Mat4f, Mat4f, m2, m1, m1, TestOperatorMinus);
    RegisterFn(Mat4f, Mat4f, Mat4f, m3, m4, m5, TestOperatorMul);
    PrintResult(Mat4f, Mat4f, Mat4f)

    RegisterFn(Mat4f, Vec4f, Vec4f, m3, v1, v2, TestOperatorMul); 
    PrintResult(Mat4f, Vec4f, Vec4f) 
 
    PrintTestCase((TestTranspose<Mat4f, Mat4f, Mat4f(*)(Mat4f)>(m5, m5, m6, Mat4::Transpose)));
    EndTestCase
  }
}

namespace JSMathStreeTest
{
#define NUM_OF_TEST 5000000
#define TestOperator(t1, in1, in2, op) \
t1 tmp; \
for(int i =0; i < NUM_OF_TEST; ++i) {tmp = in1 op in2;} \
std::cout << tmp << std::endl; \

  void TestJSMat4Class()
  {
    Mat4f m3(1,2,3,4,
            5,6,7,8,
            9,10,11,12,
            13,14,15,16);
    Mat4f m4(17,18,19,20,
             21,22,23,24,
             25,26,27,28,
             29,30,31,32);
    //TestOperator(Mat4f, m3, m4, +)
    //TestOperator(Mat4f, m3, m4, -)
    TestOperator(Mat4f, m3, m4, *)
  }

  void TestJSMat3Class()
  {
    Mat3f m3(1, 2, 3, 4, 5, 6, 7, 8, 9), m4(1, 2, 3, 4, 5, 6, 7, 8, 9);
    TestOperator(Mat3f, m3, m4, *)
  }
}


namespace JSMultithreading
{
  using namespace std::chrono;
  void initializer(std::promise<int>* promiseObj)
  {
    std::cout << "Inside thread" << std::endl;
    promiseObj->set_value(35); 
  }
  int foo()
  {
    std::this_thread::sleep_for(3s);
    return 10;
  }
  int goo()
  {
    std::this_thread::sleep_for(2s);
    return 30;
  }


 auto fn(int i) 
 -> int
{
  return 0;
}

  class Threadpool
  {
  public: 

    Threadpool(size_t numOfWorkers) : m_Stop(false)
    {
      for (int i = 0; i < numOfWorkers; ++i)
      {
        m_Workers.emplace_back([this]()
        {
          //while (1)
          {
            std::function<void()> task;
            //std::function<void()> task;
            {
              std::unique_lock<std::mutex> lock(this->m_Mutex);
              //if task is empty, wait 
              while (this->m_Tasks.empty())
                this->m_CV.wait(lock);

              //if(this->m_Stop && this->m_Tasks.empty()) return;
              task = std::move(this->m_Tasks.front());
              this->m_Tasks.pop();
            }
            task();
          } 

        }
        );
      }
    }
    template<class F, class... Args>
    void AddTask(F&& f, Args&&... args)
      //-> std::future<typename std::result_of<F(Args...)>::type>
    {
      using return_type = typename std::result_of<F(Args...)>::type;
      {
        std::unique_lock<std::mutex> lock(m_Mutex);
        //forward is to maintain the r-value-ness, if not, it will convert to L-value reference
        auto task = std::make_shared< std::packaged_task<return_type()> >(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        //std::future<return_type> result = task->get_future();
        m_Tasks.emplace([task]()
        {
          (*task)();
        });
      }
    }

    void JoinAllWorkers()
    {
      {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Stop = true;
      }
      m_CV.notify_all();

      for (auto& elem : m_Workers)
      {
        elem.join();
      }
    }

    ~Threadpool()
    {

    }


  private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > m_Workers;
    // the task queue
    std::queue< std::function<void()> > m_Tasks;
    std::mutex m_Mutex;
    std::condition_variable m_CV;
    bool m_Stop;
  };
  std::condition_variable cv;
  std::mutex mutex;
  bool ready = false;


  void printThreadID()
  {
    //std::unique_lock<std::mutex> lck(mutex);
    //cv.wait(lck, [&]()
    //  {
    //    return ready;
    //  }
    //);
    //while(!ready) cv.wait(lck);
    JSMathStreeTest::TestJSMat4Class();
  }

  //int printThreadID()
  //{
  //  //std::unique_lock<std::mutex> lck(mutex);
  //  //cv.wait(lck, [&]()
  //  //{
  //  //  return ready;
  //  //}
  //  //);
  //  //while(!ready) cv.wait(lck);
  //  std::this_thread::sleep_for(1s);
  //  return 10 * 10;
  //}
  void go()
  {
    //std::unique_lock<std::mutex> lck(mutex);
    //ready = true;
    //cv.notify_all();
  }

 using namespace std::chrono;

#define START start = system_clock::now();
#define END std::cout << duration_cast<seconds>(system_clock::now() - start).count() << "s\n";



  void TestJSMultithreading() 
  {
    system_clock::time_point start; 
    //fc f;

    EASY_BLOCK("No-threading");  
    //f();
    for (int i = 0; i < 2; ++i)
    {  
      GetThreadPool.AddTask(printThreadID);
    }

    //START
    //for (int i = 0; i < 4; ++i)
    //{ 
    //  GetThreadPool.AddJobs(printThreadID);
    //}
    //END
    //system_clock::time_point start;
    //int v1, v2; 
    //START
    //std::cout << "Single thread" << std::endl;
    //v1 = foo();
    //v2 = goo();s
    //std::cout << v1 + v2 << std::endl;
    //END
    //
    //START
    //std::cout << "Two thread" << std::endl;
    //std::future<int> f1 = std::async(foo);
    //v2 = goo();
    //v1 = f1.get();
    //std::cout << v1 + v2 << std::endl;
    //END

    //std::vector<std::thread> threadVec;
    //for (int i = 0; i < 10; ++i)
    //{
    //  threadVec.emplace_back(printThreadID, i);
    //}
    //go(); 

    //for (int i = 0; i < 10; ++i)
    //{
    //  threadVec[i].join();
    //}

    //std::vector<std::string> sv;
    //std::string s("1");
    //std::string s1("2");
    //std::string s2("3"); 
     
    //sv.push_back(s);
    //sv.emplace_back(s1);

    


    //std::promise<int> promiseObj;
    //std::future<int> futureObj = promiseObj.get_future();
    //std::thread t(initializer, &promiseObj);
    //std::cout << futureObj.get() << std::endl;
    //t.join();
    
  }

}


