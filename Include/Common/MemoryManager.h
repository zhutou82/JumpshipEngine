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

#ifdef USING_GLOBAL_NEW

#define JSNew(x)        \
new x;                  \
std::cout << "Memory allocation dected: " << std::endl;            \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE   \
          << "File line: " << __LINE__  << GLOBAL::NEW_LINE                  \
          << "Type: " << #x  << GLOBAL::NEW_LINE                  \
          << "Allocation Size: " << sizeof(x) << " BYTE(s) " << GLOBAL::NEW_LINE ;

#define JSDelete(x) assert(x != NULL); \
delete x; x = NULL;  //deletion will access destructor

#define JSNewArray(x, y) \
new x[y]

#define JSDeleteArray(x) assert(x != NULL); \
delete []x; x = NULL;

#else
#define JSNew(x)                                                                  \
reinterpret_cast<x*>(g_MemoryManager.AllocateMemory(sizeof(x), 1));               \
LogDebug ("Memory allocation dected: ");                                          \
LogDebug ("File Name: %s\nFile line: %i\nType: %s\nAllocation Size: %llu BYTE(s)",__FILE__, __LINE__, #x, sizeof(x) ); \
LogDebug ("=======================================");                             \

#define JSNewArray(x, sz)                                                                   \
reinterpret_cast<x*>(g_MemoryManager.AllocateMemory(sizeof(x), sz));                        \
LogDebug ("Memory allocation dected: ");                                                    \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE                                  \
          << "File line: " << __LINE__  << GLOBAL::NEW_LINE                                 \
          << "Type: " << #x  << GLOBAL::NEW_LINE                                            \
          << "Allocation Size for type: " << sizeof(x) << GLOBAL::NEW_LINE                  \
          << "Number of allocations: " << sz << GLOBAL::NEW_LINE                            \
          << "Total allocation Size: " << sizeof(x) * sz << " BYTE(s) " << GLOBAL::NEW_LINE \
          << "=======================================" << GLOBAL::NEW_LINE;               

#define JSDelete(x) assert(x != NULL);                                        \
g_MemoryManager.DeallocateMemory(x);                                          \
std::cout << "Memory deallocation dected: " << std::endl;                     \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE                    \
          << "File line: " << __LINE__  << GLOBAL::NEW_LINE                   \
          << "=======================================" << GLOBAL::NEW_LINE;    

#define JSDeleteArray(x) assert(x != NULL);                                   \
g_MemoryManager.DeallocateMemory(x);                                          \
std::cout << "Memory array deallocation dected: " << std::endl;               \
std::cout << "File Name: " << __FILE__ << GLOBAL::NEW_LINE                    \
          << "File line: " << __LINE__  << GLOBAL::NEW_LINE                   \
          << "=======================================" << GLOBAL::NEW_LINE;   
//#define JSDeleteArray(x) assert(x != NULL); \
//g_MemoryManager.DeallocateMemory(x); \
//std::cout << "Memory deallocation dected: " << std::endl;            \

#endif



class MemoeryManager : public Singleton<MemoeryManager>
{
  static const JSint16 NUMBER_OF_PAGES = 100;
  static const JSint16 NUMBER_OF_MAX_ALLOCATION_IN_ONE_PAGE = 100;
  static const JSint16 PAGE_SIZE = 512;
  static const JSint16 PADDING_SIZE = 32;
  static const JSint32 MAGIC_NUMBER = 0x1234ABCD;
  static const JSint8  INIT_VALUE = 0x0;

public:
  friend class Singleton<MemoeryManager>;
  void Release();
  void * AllocateMemory(JSuint64 size, JSuint32 numberOfAllocations);
  void DeallocateMemory(JSvoid * toDelete);

private:
  struct AllocationHeader
  {
    AllocationHeader() {}
    void AddPadding()
    {
      //set start and end addr to the addr without padding
      //add padding to start and end of new allocation
      *reinterpret_cast<JSint32*>(startAddr) = MAGIC_NUMBER;
      *reinterpret_cast<JSint32*>(endAddr - PADDING_SIZE) = MAGIC_NUMBER;
      //fill the allocated space to 0
      memset(startAddr + PADDING_SIZE, INIT_VALUE, size - 2 * PADDING_SIZE);
    }

    void Init(JSbyte* s, JSuint64 sz, JSuint32 indexToUse = 0)
    {
      JSassert(s != JSNULL);
      startAddr = s;
      endAddr = startAddr + sz;
      size = sz;
      index = indexToUse;
    }
    AllocationHeader* next;
    JSbyte* startAddr;
    JSbyte* endAddr;
    JSuint64 size;
    JSuint32 index;
  };

  struct AllocationLinkedList
  {
    AllocationHeader* head = JSNULL;
    AllocationHeader* tail = JSNULL;
    void AddAllocation(AllocationHeader* data)
    {
      JSassert(data != JSNULL);
      if (!head)
      {
        head = data;
        tail = data;
      }
      else
      {
        tail->next = data;
        tail = tail->next;
      }
      PrintList();
    }
    bool InsertAllocation(AllocationHeader* data, JSbyte * pageEndAddr)
    {
      JSassert(data != JSNULL || pageEndAddr != JSNULL);
      if(data->endAddr > pageEndAddr) return false;
      AllocationHeader* curr = head;
      AllocationHeader* prev = head;
      if (head == JSNULL)
      {
        AddAllocation(data);
        return true;
      }
      while (curr)
      {
        if (data->endAddr <= curr->startAddr)
        {
          if (curr == head)
          {
            data->next = curr;
            head = data;
          }
          else
          {
            prev->next = data;
            data->next = curr;
          }

          PrintList();
          return true;
        }
        data->startAddr = curr->endAddr;
        data->endAddr = data->startAddr + data->size;

        prev = curr;
        curr = curr->next;
      }
      if (data->endAddr < pageEndAddr)
      {
        AddAllocation(data);
        return true;
      }
      return false;
    }
    AllocationHeader* RemoveAllocation(void* addr)
    { 
      JSassert(addr != JSNULL);
      AllocationHeader* curr = head;
      AllocationHeader* prev = head;
      while (curr)
      {
        if (curr->startAddr == addr)
        {
          prev->next = curr->next;
          if (curr == head)      head = curr->next;
          else if (curr == tail) tail = curr == head ? JSNULL : prev;
          curr->next = JSNULL;
          PrintList();
          return curr;
        }
        prev = curr;
        curr = curr->next;
      }
      return JSNULL;
    }
    //Debug info
    void PrintList()
    {
      AllocationHeader* tmpHead = head;
      if (tmpHead == JSNULL)
      {
        //LogDebug("Empty Page after deletion");
        return;
      }
      
      for(;tmpHead->next; tmpHead = tmpHead->next)
      {
       
        //LogDebug("[ %p - %p ](%llu)->", reinterpret_cast<JSvoid*>(tmpHead->startAddr), reinterpret_cast<JSvoid*>(tmpHead->endAddr), tmpHead->size);
        //std::cout << GLOBAL::SQUARE_BRACKET_O << reinterpret_cast<JSvoid*>(tmpHead->startAddr) << GLOBAL::DASH << reinterpret_cast<JSvoid*>(tmpHead->endAddr) << GLOBAL::SQUARE_BRACKET_C
        //          << GLOBAL::BRACKET_O << tmpHead->size << GLOBAL::BRACKET_C << GLOBAL::ARROW;
      }
      //LogDebug("[ %p - %p ](%llu)\n", reinterpret_cast<JSvoid*>(tmpHead->startAddr), reinterpret_cast<JSvoid*>(tmpHead->endAddr), tmpHead->size);

    }
  };

  struct PageHeader
  {
    PageHeader() : 
    isInitialized(false) 
    {}
    void Init(JSuint64 size, JSbool init)
    {
      startAddr = reinterpret_cast<JSbyte*>(malloc(size));
      JSassert(startAddr != JSNULL);
      endAddr = startAddr + size;
      memset(startAddr, INIT_VALUE, size);
      isInitialized = init;
      PrintPage();
    }
    void RemoveAllocation(AllocationHeader* allocationToRemove)
    {
      //clear the value 
      memset(allocationToRemove->startAddr, INIT_VALUE, allocationToRemove->size);
      freeAllocationIndex.SetKBitToZero(allocationToRemove->index);
    }
    void PrintPage()
    {
      //printf("New page allocated\n Start address: %p End address: %p \n", reinterpret_cast<JSvoid*>(startAddr), reinterpret_cast<JSvoid*>(endAddr));
    }

    JSbyte* startAddr;
    JSbyte* endAddr;
    JSbool isInitialized;
    BitArray freeAllocationIndex;
    AllocationLinkedList allocationList;
    //std::vector<AllocationHeader> allocationHeaderVec;
    std::array<AllocationHeader, NUMBER_OF_MAX_ALLOCATION_IN_ONE_PAGE> allocationHeaderVec;
  };
  MemoeryManager(){}
  std::array<PageHeader, NUMBER_OF_PAGES> m_PageHeaderAllocationVec;
};

void * operator new (size_t size);
//void* operator new[](size_t size);
void operator delete(void* toDelete);
//void operator delete[](void* toDelete);
