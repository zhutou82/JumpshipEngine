#include "JumpshipEngine.h"
#include "Logger.h"


void JumpshipEngine::Initialize()
{
	m_logger->debug()<< "Initialize" << std::endl;
}
void JumpshipEngine::Load()
{
	m_logger->debug() << "Load level" << std::endl;
}
void JumpshipEngine::Update()
{
	m_logger->debug() << "Update" << std::endl;
}
void JumpshipEngine::Unload()
{
	m_logger->debug() << "Unload" << std::endl;
}
void JumpshipEngine::Release()
{
	m_logger->debug() << "Release" << std::endl;
}