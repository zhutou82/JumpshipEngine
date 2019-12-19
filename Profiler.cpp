#include "Profiler.h"

//void Profiler::InsertBlock(const std::string & blockName, profilerBlockColor c)
//{
//	EASY_FUNCTION(m_ColorToProfilerColorMap[c]);
//	EASY_BLOCK(blockName.c_str()) 
//}

Profiler::Profiler()
{
	m_ColorToProfilerColorMap[ProfilerBlockColor::FUNCTION_COLOR] = profiler::colors::Blue;
	m_ColorToProfilerColorMap[ProfilerBlockColor::LOOP_COLOR] = profiler::colors::Red;
}
