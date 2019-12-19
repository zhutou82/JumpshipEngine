#pragma once
#include "CommonHeader.h"
#include "SingletonBaseClass.h"

#define GetProfiler Singleton<Profiler>::GetInstance()
enum ProfilerBlockColor
{
	FUNCTION_COLOR,
	LOOP_COLOR
};

class Profiler : Singleton<Profiler>
{
public:
	friend class Singleton<Profiler>;
	const Profiler& operator=(const Profiler&) = delete;
	Profiler(const Profiler&) = delete;
	void Init() { EASY_PROFILER_ENABLE };
	profiler::color_t GetColor(ProfilerBlockColor c) { return m_ColorToProfilerColorMap[c]; }
	void DumpblockToFile(const std::string& fileName) { profiler::dumpBlocksToFile(std::string(m_ProfileOutputFolder + fileName).c_str()); }
	//void InsertBlock(const std::string& blockName, profilerBlockColor c = profilerBlockColor::FUNCTION_COLOR);
	//void Insert(const std::string& blockName) { EASY_BLOCK(blockName.c_str()) }
	//void EndBlock() { EASY_END_BLOCK }

private:
	Profiler();
	std::string m_ProfileOutputFolder;
	std::map<ProfilerBlockColor, profiler::color_t> m_ColorToProfilerColorMap;
};