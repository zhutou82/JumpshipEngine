#include "JumpshipEngine.h"
#include "Input.h"
#include "Graphics.h"
#include "JSMathTestcases.h"



JumpshipEngine::JumpshipEngine()
: 
m_RecourseFolderPath("Resource/"),
m_XMLFolderPath (m_RecourseFolderPath + "XML/"),
m_EngineConfigXMLFile (m_XMLFolderPath + "EngineConfig.xml")
{

}

int JumpshipEngine::Initialize(_In_ HINSTANCE hInstance,
                                _In_ LPSTR lpCmdLine,
                                _In_ int nCmdShow)
{
  EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Initialize");
	LogDebug("Serializering data");
	LoadEnginePathConfig();
  GetThreadPool.InitWorkers();
	GetProfiler.Init(g_EngineConfigFolderPathVec[FolderPath_Index::PROFILER_FOLDERER],
                   g_EngineConfigFileNameVec[FileName_Index::PROFILER_FILENAME]);

  //init graphics engine
  if (GLOBAL::JSPFAILED == GetGraphicsEngine.Initialize(hInstance, 
                                                        lpCmdLine, 
                                                        nCmdShow, 
                                                        JSMath::StringToVec2i(g_EngineConfigGraphicsEngineVec[GraphicsEngine_Index::WindowResolution]),
                                                        g_EngineConfigGraphicsEngineVec[GraphicsEngine_Index::WindowName],
                                                        GetEngine.GetRecourceFolderPath() + g_EngineConfigFolderPathVec[FolderPath_Index::SHADER_FOLDER],
                                                        std::stoi(g_EngineConfigGraphicsEngineVec[GraphicsEngine_Index::WindowFullScreen]),
                                                        std::stoi(g_EngineConfigGraphicsEngineVec[GraphicsEngine_Index::WindowsShow]))
                                                        )
  {
    return GLOBAL::JSPFAILED;
  }

  //testing math library
  //JSMathTestCaseMacroMethod::TestJSVec2Class();
  //JSMathTestCaseMacroMethod::TestJSVec3Class();
  //JSMathTestCaseMacroMethod::TestJSMat2Class();
  //JSMathTestCaseMacroMethod::TestJSMat3Class();
  //JSMathTestCaseTemplateMethod::TestJSVec4Class();
  //JSMathTestCaseTemplateMethod::TestJSMat4Class();

  //EASY_BLOCK("TestJSMat4Class");
  //JSMathStreeTest::TestJSMat4Class();
  //EASY_END_BLOCK
 /* EASY_BLOCK("TestJSMat33Class");
  JSMathStreeTest::TestJSMat3Class();
  EASY_END_BLOCK*/
  //practicing mulithreading
  //JSMultithreading::TestJSMultithreading(); 
  
  //JSMemoeryAllocation::TestMemoeryAllocation();
#define TEST_3
#ifdef TEST_2                

  //testing vec2 class with simd
  Vec2f v(1.f, 2.f);
  Vec2f vv(1.f, 2.f);
  std::cout << Vec2::Dot(v, vv)  << std::endl;

  Vec2f v3(2.f, 2.f);
  Vec2f vv4(1.f, 2.f);
  std::cout << (v3 == vv4 ? "t" : "f") << std::endl;

  std::cout << (v3 *= 2.f) << std::endl;

  Mat2f m(1,2,3,4);
  Mat2f mm(1,2,3,4);
  //float* a = m.GetColumn(1);
  //std::cout << m << std::endl; 
  //std::cout << mm << std::endl;
  std::cout << (m *= 2.f) << std::endl;
#endif

#ifdef TEST_3
  //Vec3f v(1,2,3);
  //Vec3f vv(1,2,3);
  //std::cout << (v == vv ? "t" : "f") << std::endl;
  ////std::cout << (v *= vv)<< std::endl;

  //Mat3f m(1,2,3,
  //        4,5,6,
  //        7,8,9);
  //Mat3f m1(1,2,3,
  //         4,5,6,
  //         7,8,9);  
  //std::cout << (m *= m1) << std::endl;
  //std::cout << 123 << std::endl;

  // = _mm512_setzero_ps();
  //int i =0;

  //std::cout << m1 << std::endl;


#endif
  //
  //std::cout << (v += vv) << GLOBAL::NEW_LINE;
  //std::cout << (v -= vv) << GLOBAL::NEW_LINE;

  //Vec2<int> windowResolution(800, 600);
  //init graphics engine
  //GetGraphicsEngine.Init(windowResolution);
  return GLOBAL::JSPSUCCESSED;
 }

#define SerializeConfig(x) \
GetSerializer.Serialize(m_EngineConfigXMLFile, #x, g_EngineConfig##x##Vec); \
PrintCont(g_EngineConfig##x##Vec) \

void JumpshipEngine::LoadEnginePathConfig()
{
  EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	//Serializering Engine Config
	LogDebug("Serializering Engine Config");
  SerializeConfig(FolderPath);
  SerializeConfig(FileName);
  SerializeConfig(GraphicsEngine);
}
void JumpshipEngine::Load()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Loading scene");
}
void JumpshipEngine::Update()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Engine Loop");
  //Engine loop
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    GetGraphicsEngine.Frame();
    TranslateMessage(&msg);
    //checking input
    DispatchMessage(&msg);
    CheckInput();
  }
  LogDebug("Exit Engine Loop");
}
void JumpshipEngine::Unload()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Unload");
}
void JumpshipEngine::Release()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
  //create profiler file
  GetProfiler.DumpblockToFile();
  GetGraphicsEngine.Shutdown();
	LogDebug("Release");
}

void JumpshipEngine::CheckInput()
{
  if (GetInput.IsKeyboardKeyPressed('K'))
  {
    LogDebug("K");
  }
  if (GetInput.IsKeyboardKeyPressed(VK_UP) || GetInput.IsKeyboardKeyPressed('W'))
  {
    GetCamera->SetPosition(GetCamera->GetPosition() + Vec4f(0, 0.1f, 0.0f, 0));
  }
  if (GetInput.IsKeyboardKeyPressed(VK_DOWN) || GetInput.IsKeyboardKeyPressed('S'))
  {
    GetCamera->SetPosition(GetCamera->GetPosition() + Vec4f(0, -0.1f, 0.0f, 0));
  }
  if (GetInput.IsKeyboardKeyPressed(VK_LEFT) || GetInput.IsKeyboardKeyPressed('A'))
  {
    GetCamera->SetPosition(GetCamera->GetPosition() + Vec4f(-0.1f, 0, 0.0f, 0));
  }
  if (GetInput.IsKeyboardKeyPressed(VK_RIGHT) || GetInput.IsKeyboardKeyPressed('D'))
  {
    GetCamera->SetPosition(GetCamera->GetPosition() + Vec4f(0.1f, 0, 0.0f, 0));
  }
  if (GetInput.IsKeyboardKeyPressed('Q'))
  {
    GetCamera->SetPosition(GetCamera->GetPosition() + Vec4f(0.f, 0.f, 0.1f, 0));
  }
  if (GetInput.IsKeyboardKeyPressed('E'))
  {
    GetCamera->SetPosition(GetCamera->GetPosition() + Vec4f(0.f, 0.f, -0.1f, 0));
  }
  if (GetInput.IsKeyboardKeyPressed('G'))
  {
    GetCamera->SetRosition(GetCamera->GetRotation() + Vec4f(1.f, 0.f, 0.f, 0));
  }

  if (GetInput.IsKeyboardKeyDown('A'))
  {
    LogDebug("A");
  }
  if (GetInput.IsKeyboardKeyToggled('B'))
  {
    LogDebug("B");
  }
  if (GetInput.IsMouseKeyDown(VK_LBUTTON))
  {
    LogDebug("MouseL");
  }
  if (GetInput.IsKeyboardKeyPressed(VK_ESCAPE))
  {
    PostQuitMessage(0);
  }
}

//template <typename T>
//bool(*vec2Testcases[])(const T& t1, const T& t2);

//template <typename T>
//std::vector<bool(*)(const T&, const T&)> VecTestcasesVector;
//
////namespace JSMathTestingcase
//
//#define PrintFnName std::cout << __FUNCTION__ << GLOBAL::NEW_LINE;
//bool TestAssignment(const Vec2f& t1, const Vec2f& t2)
//{
//  PrintFnName
//  Vec2f v = t1;
//  return v == Vec2f(1, 2);
//}
//bool TestOpeartorplus(const Vec2f& t1, const Vec2f& t2)
//{
//  PrintFnName
//   Vec2f tmp = t1 + Vec2f(2,2);
//  return tmp == t2;
//  //return false;
//}
//
//bool TestOpeartorMinus(const Vec2f& t1, const Vec2f& t2)
//{
//  PrintFnName
//    Vec2f tmp = t2 - Vec2f(2, 2);
//  return tmp == t1;
//  //return false;
//}
//
//void TestJSVec2()
//{
//  std::cout << "Testing Vec2f class" << std::endl;
//  Vec2f TestObj1(1, 2);
//  Vec2f TestObj2(3, 4);
//
//  VecTestcasesVector<Vec2f>.push_back(TestAssignment);
//  VecTestcasesVector<Vec2f>.push_back(TestOpeartorplus);
//  VecTestcasesVector<Vec2f>.push_back(TestOpeartorMinus);
//
//  for (size_t i = 0, n = VecTestcasesVector<Vec2f>.size(); i < n; ++i)
//  {
//    std::cout << "Testcase " << i + 1 << GLOBAL::COLON;
//    std::cout << (VecTestcasesVector<Vec2f>[i](TestObj1, TestObj2) ? GLOBAL::JSPASS : GLOBAL::JSFAIL) << GLOBAL::NEW_LINE;
//  }
//
//}
