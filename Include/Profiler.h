#pragma once
#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"

enum ProfilerBlockColor
{
  FUNCTION_COLOR,
  LOOP_COLOR,
  ProfilerBlockColor_MAX_SIZE
};
constexpr uint32_t RED = 0x00FF0000;
constexpr uint32_t BLUE = 0x000000FF;
constexpr uint32_t GREEN = 0x0000FF00;

constexpr uint32_t m_ColorToProfilerColorArr[] =
{ 
  BLUE,
  GREEN,
  RED
};

#define GetProfiler Singleton<Profiler>::GetInstance()
#define GetProfilerBLKColor(x) m_ColorToProfilerColorArr[x]

class Profiler : Singleton<Profiler>
{
public:
	friend class Singleton<Profiler>;
	const Profiler& operator=(const Profiler&) = delete;
	Profiler(const Profiler&) = delete;
	void Init(const std::string& outputFolderPath, const std::string& outputFileName) { m_ProfilerFile = outputFolderPath + outputFileName; };
	void DumpblockToFile() { profiler::dumpBlocksToFile(std::string(m_ProfilerFile + ".prof").c_str()); }
	//void InsertBlock(const std::string& blockName, profilerBlockColor c = profilerBlockColor::FUNCTION_COLOR);
	//void Insert(const std::string& blockName) { EASY_BLOCK(blockName.c_str()) }
	//void EndBlock() { EASY_END_BLOCK }

private:
	Profiler();
	std::string m_ProfilerFile;
	
};