#include "Common/MemoryManager.h"

void * operator new (size_t size)
{
  return GetMemoryManager.AllocateMemory(size);
}
void* operator new [](size_t size)
{
  return GetMemoryManager.AllocateMemory(size);
}

void operator delete(void* toDelete)
{
  GetMemoryManager.DeallocateMemory(toDelete);
}

void operator delete[](void * toDelete)
{
  
}

void MemoeryManager::Init()
{
  m_Head = reinterpret_cast<FreeStore*>(malloc(TOTAL_MEMORY_TO_ALLOCATE_FOR_ENGINE));
  m_FreeHead = m_Head;
  for (int i = 0, n = m_NumOfBlocks; i < n; ++i)
  {
    m_FreeHead->isFree = true;
    m_FreeHead->next = m_FreeHead + POOL_SIZE;
    m_FreeHead = m_FreeHead->next;
  }
  m_FreeHead = m_Head;
}

void * MemoeryManager::AllocateMemory(size_t size)
{
  int numberOfBlockNeeded = ceil(size/POOL_SIZE);
  for (int i = 0; i < numberOfBlockNeeded; ++i)
  {
    if (m_FreeHead->isFree == true)
    {
      m_FreeHead->isFree = false;
    }
  }

  return nullptr;
}
 
void MemoeryManager::DeallocateMemory(void * toDelete)
{
  
}

MemoeryManager::~MemoeryManager()
{
  free(m_Head);
}
