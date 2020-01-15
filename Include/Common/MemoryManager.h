#pragma once
#include <stdlib.h>
#include "Common\GlobalVariables.h"
#include "Common/SingletonBaseClass.h"
#include <math.h>

#define JSNew(x) \
new x;           \
std::cout << "Memory allocation dected: " << std::endl;            \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE   \
          << "File line: " << __LINE__  << GLOBAL::NEW_LINE                  \
          << "Type: " << #x  << GLOBAL::NEW_LINE                  \
          << "Allocation Size: " << sizeof(x) << " BYTE(s) " << GLOBAL::NEW_LINE ;

#define GetMemoryManager Singleton<MemoeryManager>::GetInstance()
class MemoeryManager : public Singleton<MemoeryManager>
{
  public:

  static const size_t TOTAL_MEMORY_TO_ALLOCATE_FOR_ENGINE = 1024;
  static const size_t POOL_SIZE = 32;

  friend class Singleton<MemoeryManager>;
  struct FreeStore
  {
    FreeStore * next;
    bool isFree;
  };

  void Init();
  void * AllocateMemory(size_t size);
  void DeallocateMemory(void * toDelete);

  private:
  MemoeryManager() :
  m_NumOfBlocks(TOTAL_MEMORY_TO_ALLOCATE_FOR_ENGINE/POOL_SIZE)
  {};
  ~MemoeryManager();
  FreeStore * m_FreeHead;
  FreeStore * m_Head;
  int m_NumOfBlocks;

};

void * operator new (size_t size);
void* operator new[](size_t size);
void operator delete(void* toDelete);
void operator delete[](void* toDelete);
