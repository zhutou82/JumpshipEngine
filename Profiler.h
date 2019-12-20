#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"

REGISTER_ENUM_START(ProfilerBlockColor)
REGISTER_ENUM_ENTRY(FUNCTION_COLOR)
REGISTER_ENUM_ENTRY(LOOP_COLOR)
REGISTER_ENUM_END(ProfilerBlockColor)

#define GetProfiler Singleton<Profiler>::GetInstance()
class Profiler : Singleton<Profiler>
{
public:
	friend class Singleton<Profiler>;
	const Profiler& operator=(const Profiler&) = delete;
	Profiler(const Profiler&) = delete;
	void Init(const std::string& outputFolderPath, const std::string& outputFileName) { m_ProfilerFile = outputFolderPath + outputFileName; };
	constexpr profiler::color_t GetColor(ProfilerBlockColor c) { return m_ColorToProfilerColorArr[c]; }
	void DumpblockToFile(const std::string& fileName) { profiler::dumpBlocksToFile(std::string(m_ProfilerFile + ".prof").c_str()); }
	//void InsertBlock(const std::string& blockName, profilerBlockColor c = profilerBlockColor::FUNCTION_COLOR);
	//void Insert(const std::string& blockName) { EASY_BLOCK(blockName.c_str()) }
	//void EndBlock() { EASY_END_BLOCK }

private:
	Profiler();
	std::string m_ProfilerFile;
	profiler::color_t m_ColorToProfilerColorArr[ProfilerBlockColor::ProfilerBlockColor_MAX_SIZE];
};