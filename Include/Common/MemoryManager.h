#pragma once
#include <stdlib.h>
#include "Common\GlobalVariables.h"
#include "Common/SingletonBaseClass.h"
#include <cstddef>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>

#define JSNew(x) \
new x;           \
std::cout << "Memory allocation dected: " << std::endl;            \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE   \
          << "File line: " << __LINE__  << GLOBAL::NEW_LINE                  \
          << "Type: " << #x  << GLOBAL::NEW_LINE                  \
          << "Allocation Size: " << sizeof(x) << " BYTE(s) " << GLOBAL::NEW_LINE ;

#define g_MemoryManager Singleton<MemoeryManager>::GetInstance()
class MemoeryManager : public Singleton<MemoeryManager>
{
  public:
  typedef char JSBYTE;

  static const size_t NUMBER_OF_PAGES = 2;
  static const size_t PAGE_SIZE = 1024;
  static const size_t PADDING_SIZE = 8;
  static const size_t MAGIC_NUMBER = 1111;

  friend class Singleton<MemoeryManager>;
  struct AllocationHeader
  {
    JSBYTE* startAddr;
    size_t size;
  };
  struct PageHeader
  {
    JSBYTE* startAddr;
    JSBYTE* endAddr;
    JSBYTE* freeAddr;
    bool isFree;
    std::vector<AllocationHeader> allocationHeaderVec;
  };
  void Init();
  void * AllocateMemory(size_t size);
  void DeallocateMemory(void * toDelete);

  private:
  MemoeryManager()
  {};
  ~MemoeryManager();
  std::vector<PageHeader> m_PageHeaderAllocationVec;
  size_t m_realPageSize;
  JSBYTE * m_FreeAllocAddrInPage;
  JSBYTE * m_Head;

};

//void * operator new (size_t size);
//void* operator new[](size_t size);
//void operator delete(void* toDelete);
//void operator delete[](void* toDelete);
