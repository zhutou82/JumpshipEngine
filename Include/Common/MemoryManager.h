#pragma once
#include <stdlib.h>
#include "Common\GlobalVariables.h"
#include "Common/SingletonBaseClass.h"
#include "DataStructure/BitArrary.h"
#include <cstddef>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <array>
#include "Logger.h"

//#define USING_GLOBAL_NEW
#define g_MemoryManager Singleton<MemoeryManager>::GetInstance()
static constexpr const JSint16 NUMBER_OF_PAGES = 100;
static constexpr const JSint16 NUMBER_OF_MAX_ALLOCATION_IN_ONE_PAGE = 100;
static constexpr const JSint16 PAGE_SIZE = 512;
static constexpr const JSint16 PADDING_SIZE = 32;
static constexpr const JSint32 MAGIC_NUMBER = 0x1234ABCD;
static constexpr const JSint8  INIT_VALUE = 0x0;
struct PageHeader;
struct AllocationHeader;
struct AllocationLinkedList;

struct AllocationHeader
{
    AllocationHeader() {}
    JSuint64 size = 0;
    JSbyte* startAddr = JSNULL;
    JSbyte* endAddr = JSNULL;
    AllocationHeader* next = JSNULL;
};
struct AllocationLinkedList
{
    void InitAllocation(AllocationHeader *& newAllocation, JSbyte* startAddr, JSuint64 size);
    AllocationHeader* InsertAllocation(JSuint64 allocationSize);
    AllocationHeader* RemoveAllocation(void* addr);
    void PrintList();
    AllocationHeader* head = JSNULL;
    AllocationHeader* tail = JSNULL;
    PageHeader* currentPage = JSNULL;
};
struct PageHeader
{
    PageHeader() 
    : 
    isInitialized(false)
    {
        allocationList.currentPage = this;
    }
    void Init(JSuint64 size, JSbool init = true);
    void PrintPage();
    BitArray freeAllocationIndex;
    AllocationLinkedList allocationList;
    std::array<AllocationHeader, NUMBER_OF_MAX_ALLOCATION_IN_ONE_PAGE> allocationHeaderVec;
    JSbyte* startAddr = JSNULL;
    JSbyte* endAddr = JSNULL;
    JSbool isInitialized = true;
};

class MemoeryManager : public Singleton<MemoeryManager>
{
public:
    friend class Singleton<MemoeryManager>;
    void Release();
    void * AllocateMemory(JSuint64 size, JSuint32 numberOfAllocations);
    void DeallocateMemory(JSvoid * toDelete);
private:
    MemoeryManager() {}
    std::array<PageHeader, NUMBER_OF_PAGES> m_PageHeaderAllocationVec;
};

#ifndef USING_GLOBAL_NEW
void * operator new (size_t size);
void operator delete(void* toDelete);
#endif 

//void* operator new[](size_t size);
//void operator delete[](void* toDelete);

#ifdef USING_GLOBAL_NEW

#define JSNew(x)                \
new x;                                    \
std::cout << "Memory allocation dected: " << std::endl;                        \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE     \
                    << "File line: " << __LINE__    << GLOBAL::NEW_LINE                                    \
                    << "Type: " << #x    << GLOBAL::NEW_LINE                                    \
                    << "Allocation Size: " << sizeof(x) << " BYTE(s) " << GLOBAL::NEW_LINE ;

#define JSDelete(x) assert(x != NULL); \
delete x; x = NULL;    //deletion will access destructor

#define JSNewArray(x, y) new x[y]

#define JSDeleteArray(x) assert(x != NULL); \
delete []x; x = NULL;

#else
//reinterpret_cast<x*>(g_MemoryManager.AllocateMemory(sizeof(x), 1));                                                                 \

#define JSNew(x)                                                                                                                    \
new x;                                                                                                                              \
LogDebug ("Memory allocation dected: \n");                                                                                          \
LogDebug ("File Name: %s\nFile line: %i\nType: %s\nAllocation Size: %llu BYTE(s)\n",__FILE__, __LINE__, #x, sizeof(x) );            \
LogDebug ("=======================================\n");                                                                               

//reinterpret_cast<x*>(g_MemoryManager.AllocateMemory(sizeof(x), sz));                                                                \

#define JSNewArray(x, sz)                                                                                                           \
new x[sz];                                                                                                                          \
LogDebug ("Array memory allocation dected: \n");                                                                                    \
LogDebug ("File Name: %s\nFile line: %i\nType: %s\nAllocation Size for One: %llu BYTE(s)\n",__FILE__, __LINE__, #x, sizeof(x) );    \
LogDebug ("Number of allocations:  %llu\nTotal allocation Size: %llu BYTE(s)\n", sz, sizeof(x) * sz);                               \
LogDebug ("=======================================\n");   

//g_MemoryManager.DeallocateMemory(x);                                                                                                \

#define JSDelete(x) assert(x != NULL);                                                                                              \
delete x;                                                                                                                           \
LogDebug("Memory deallocation dected: \n");                                                                                         \
LogDebug("File Name: %s\nFile line: %i\n", __FILE__, __LINE__);                                                                     \
LogDebug ("=======================================\n");                                                                               

//g_MemoryManager.DeallocateMemory(x);                                                                                                \

#define JSDeleteArray(x) assert(x != NULL);                                                                                         \
delete x;                                                                                                                           \
LogDebug("Array Memory deallocation dected: \n");                                                                                   \
LogDebug("File Name: %s\nFile line: %i\n", __FILE__, __LINE__);                                                                     \
LogDebug ("=======================================\n");                                                                               

#endif