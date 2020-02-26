#include "JumpshipEngine.h"
#include "Input.h"
#include "Graphics.h"
#include "JSMathTestcases.h"
#include "Common/MemoryManager.h"
#include "Serializer/BinSerializer.h"

JumpshipEngine::JumpshipEngine()
: 
m_RecourseFolderPath("Resource/"),
m_XMLFolderPath (m_RecourseFolderPath + "XML/"),
m_EngineConfigXMLFile (m_XMLFolderPath + "EngineConfig.xml")
{

}
JSbool JumpshipEngine::Initialize(_In_ HINSTANCE hInstance,
                                                             _In_ LPSTR lpCmdLine,
                                                             _In_ int nCmdShow)
{ 
    EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
    g_Logger.Init("LogFiles/");
	LogDebug("Initialize\n");
	LogDebug("Serializering data\n");

    //int * i6 = JSNewArray(int, 118);
    //int * i7 = JSNewArray(int, 1);
    //JSDelete(i7);
    //int * i8 = JSNewArray(int, 1);
    //int * i9 = JSNewArray(int, 10);
    //JSDelete(i8);
    //int * i10 = JSNewArray(int, 1);

    //g_MemoryManager.DeallocateMemory(i);
    //g_MemoryManager.DeallocateMemory(i3);
    //int * i = reinterpret_cast<int*>(g_MemoryManager.AllocateMemory(sizeof(int), 1));
    //int * i2 = reinterpret_cast<int*>(g_MemoryManager.AllocateMemory(sizeof(int), 2));
    //g_MemoryManager.DeallocateMemory(i);
    //g_MemoryManager.DeallocateMemory(i2);

    //Mat4f* m = reinterpret_cast<Mat4f*>(g_MemoryManager.AllocateMemory(sizeof(Mat4f), 1));
    //g_MemoryManager.DeallocateMemory(m); 

	LoadEnginePathConfig();
    g_Logger.Init(g_EngineConfigstringConfigVec[stringConfig_Index::LOG_FOLDER].c_str());
    GetThreadPool.InitWorkers();    
	g_Profiler.Init(g_EngineConfigstringConfigVec[stringConfig_Index::PROFILER_FOLDERER],
                                     g_EngineConfigstringConfigVec[stringConfig_Index::PROFILER_FILENAME]);
    //init graphics engine
    if (GLOBAL::JSPFAILED == g_GraphicsEngine.Initialize(hInstance, 
                                                        lpCmdLine, 
                                                        nCmdShow, 
                                                        g_EngineConfigVec2iConfigVec[Vec2iConfig_Index::WINDOW_RESOLUTION],
                                                        g_EngineConfigstringConfigVec[stringConfig_Index::WINDOWS_NAME],
                                                        g_Engine.GetRecourceFolderPath() + g_EngineConfigstringConfigVec[stringConfig_Index::SHADER_FOLDER],
                                                        g_EngineConfigboolConfigVec[boolConfig_Index::IS_WINDOW_FULLSCREEN],
                                                        g_EngineConfigboolConfigVec[boolConfig_Index::IS_WINDOW_SHOW])
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


    return GLOBAL::JSPSUCCESSED;
}

#define SerializeConfig(x) \
g_Serializer.Serialize(#x, g_EngineConfig##x##ConfigVec); \
PrintCont(g_EngineConfig##x##ConfigVec) \

void JumpshipEngine::LoadEnginePathConfig()
{
#ifdef SerializeByXML
    EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	//Serializering Engine Config
	LogDebug("Serializering Engine Config");
    g_Serializer.Init(m_EngineConfigXMLFile);
    SerializeConfig(string);
    SerializeConfig(Vec2i);
    SerializeConfig(bool);
#else
#ifdef WriteDataToBinary
    g_Binserializer.Write();
#endif
    g_Binserializer.StartReading();
    g_Binserializer.Read(g_EngineConfigstringConfigVec, stringConfig_MAX_SIZE);
    g_Binserializer.Read(g_EngineConfigVec2iConfigVec, Vec2iConfig_MAX_SIZE);
    g_Binserializer.Read(g_EngineConfigboolConfigVec, boolConfig_MAX_SIZE);
    g_Binserializer.EndReading();
#endif
}
void JumpshipEngine::Load()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Loading scene\n");
}
void JumpshipEngine::Update()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Engine Loop\n");
    //Engine loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        g_GraphicsEngine.Frame();
        TranslateMessage(&msg);
        //checking input
        DispatchMessage(&msg);
        CheckInput();
    }
    LogDebug("Exit Engine Loop\n");
}
void JumpshipEngine::Unload()
{
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
	LogDebug("Unload\n");
}
void JumpshipEngine::Release()
{
    LogDebug("Release\n");
	EASY_FUNCTION(GetProfilerBLKColor(FUNCTION_COLOR));
    //create profiler file
    g_Profiler.DumpblockToFile();
    g_GraphicsEngine.Shutdown();
    g_MemoryManager.Release();
}

void JumpshipEngine::CheckInput()
{
    if (GetInput.IsKeyboardKeyPressed('K'))
    {
        LogDebug("K");
    }
    if (GetInput.IsKeyboardKeyPressed(VK_UP) || GetInput.IsKeyboardKeyPressed('W'))
    {
        g_Camera->SetPosition(g_Camera->GetPosition() + Vec4f(0, 0.1f, 0.0f, 0));
    }
    if (GetInput.IsKeyboardKeyPressed(VK_DOWN) || GetInput.IsKeyboardKeyPressed('S'))
    {
        g_Camera->SetPosition(g_Camera->GetPosition() + Vec4f(0, -0.1f, 0.0f, 0));
    }
    if (GetInput.IsKeyboardKeyPressed(VK_LEFT) || GetInput.IsKeyboardKeyPressed('A'))
    {
        g_Camera->SetPosition(g_Camera->GetPosition() + Vec4f(-0.1f, 0, 0.0f, 0));
    }
    if (GetInput.IsKeyboardKeyPressed(VK_RIGHT) || GetInput.IsKeyboardKeyPressed('D'))
    {
        g_Camera->SetPosition(g_Camera->GetPosition() + Vec4f(0.1f, 0, 0.0f, 0));
    }
    if (GetInput.IsKeyboardKeyPressed('Q'))
    {
        g_Camera->SetPosition(g_Camera->GetPosition() + Vec4f(0.f, 0.f, 0.1f, 0));
    }
    if (GetInput.IsKeyboardKeyPressed('E'))
    {
        g_Camera->SetPosition(g_Camera->GetPosition() + Vec4f(0.f, 0.f, -0.1f, 0));
    }
    if (GetInput.IsKeyboardKeyPressed('G'))
    {
        g_Camera->SetRosition(g_Camera->GetRotation() + Vec4f(1.f, 0.f, 0.f, 0));
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
//    PrintFnName
//    Vec2f v = t1;
//    return v == Vec2f(1, 2);
//}
//bool TestOpeartorplus(const Vec2f& t1, const Vec2f& t2)
//{
//    PrintFnName
//     Vec2f tmp = t1 + Vec2f(2,2);
//    return tmp == t2;
//    //return false;
//}
//
//bool TestOpeartorMinus(const Vec2f& t1, const Vec2f& t2)
//{
//    PrintFnName
//        Vec2f tmp = t2 - Vec2f(2, 2);
//    return tmp == t1;
//    //return false;
//}
//
//void TestJSVec2()
//{
//    std::cout << "Testing Vec2f class" << std::endl;
//    Vec2f TestObj1(1, 2);
//    Vec2f TestObj2(3, 4);
//
//    VecTestcasesVector<Vec2f>.push_back(TestAssignment);
//    VecTestcasesVector<Vec2f>.push_back(TestOpeartorplus);
//    VecTestcasesVector<Vec2f>.push_back(TestOpeartorMinus);
//
//    for (size_t i = 0, n = VecTestcasesVector<Vec2f>.size(); i < n; ++i)
//    {
//        std::cout << "Testcase " << i + 1 << GLOBAL::COLON;
//        std::cout << (VecTestcasesVector<Vec2f>[i](TestObj1, TestObj2) ? GLOBAL::JSPASS : GLOBAL::JSFAIL) << GLOBAL::NEW_LINE;
//    }
//
//}
