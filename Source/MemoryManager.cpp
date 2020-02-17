#include "Common/MemoryManager.h"
#include <thread>


#ifndef USING_GLOBAL_NEW
void * operator new (size_t size)
{ 
  return g_MemoryManager.AllocateMemory(size, 1);
}
//void* operator new [](size_t size)
//{
//  return g_MemoryManager.AllocateMemory(size);
//}
////
void operator delete(void* toDelete)
{
  return g_MemoryManager.DeallocateMemory(toDelete);
}
//
//void operator delete[](void * toDelete)
//{
//  
//}
#endif

void * MemoeryManager::AllocateMemory(JSuint64 sz, JSuint32 numberOfAllocations)
{
  LogDebug("AllocateMemory, numberOfAllocations: %u\n", numberOfAllocations);
  JSuint64 size = sz * numberOfAllocations + 2 * PADDING_SIZE;
  JSuint64 pageSize = size > PAGE_SIZE ? size : PAGE_SIZE;
  for (JSuint32 i = 0; i < NUMBER_OF_PAGES; ++i)
  {
    PageHeader& page = m_PageHeaderAllocationVec[i];
    if(!page.isInitialized) page.Init(pageSize, true);
    LogDebug("Page start address: %p End address: %p\n", reinterpret_cast<JSvoid*>(page.startAddr), reinterpret_cast<JSvoid*>(page.endAddr));
    JSint32 indexToUse = 0;
    //find available index
    for (JSint32 j = 0; j < NUMBER_OF_MAX_ALLOCATION_IN_ONE_PAGE; ++j)
    {
      if (page.freeAllocationIndex.IsCurrentIndexIsSet(j) == false)
      {
        indexToUse = j;
        break;  
      }
    }
    //if free allocation index number to use is equal to max number of allocation, means it has run out of all allocations
    JSassert(indexToUse < NUMBER_OF_MAX_ALLOCATION_IN_ONE_PAGE);
    AllocationHeader& newAllocationHeader = page.allocationHeaderVec[indexToUse];
    newAllocationHeader.Init(page.startAddr, size, indexToUse);
    //insert into allcation list and update new allocation properties
    if (page.allocationList.InsertAllocation(&newAllocationHeader, page.endAddr))
    {
      newAllocationHeader.AddPadding();
      page.freeAllocationIndex.SetKBitToOne(indexToUse);
      return newAllocationHeader.startAddr + PADDING_SIZE;
    }
  }
  return JSNULL;
}
 
void MemoeryManager::DeallocateMemory(JSvoid * toDelete)
{
  JSvoid* realToDeleteAddr = reinterpret_cast<JSbyte*>(toDelete) - PADDING_SIZE;
  JSassert(toDelete != JSNULL);
  //bad pointer if to delete addr is padding
  LogDebug("Addr to delete: %p\n", realToDeleteAddr);
  JSassert(*reinterpret_cast<JSint32*>(realToDeleteAddr) == MAGIC_NUMBER);
  for (auto& page : m_PageHeaderAllocationVec)
  {
    if(realToDeleteAddr <= page.endAddr && realToDeleteAddr >= page.startAddr)
    {
      LogDebug("Page start address: %p End address: %p\n", reinterpret_cast<JSvoid*>(page.startAddr), reinterpret_cast<JSvoid*>(page.endAddr));
      AllocationHeader* allocationToDelete = page.allocationList.RemoveAllocation(realToDeleteAddr);
      //printf("Size to delete: %u\n", allocationToDelete->size);
      if (allocationToDelete)
      {
        JSassert(*reinterpret_cast<JSint32*>(reinterpret_cast<JSbyte*>(realToDeleteAddr) + allocationToDelete->size - PADDING_SIZE) == MAGIC_NUMBER);
        page.RemoveAllocation(allocationToDelete);
        return;
      }
      LogDebug("Bad pointer as could not be find in this page\n");
      return;
    }
  }
  LogDebug("Bad pointer as could not be found at any page\n");
}
//free all memory allocated by page
void MemoeryManager::Release()
{
  for (auto& page : m_PageHeaderAllocationVec) free(page.startAddr);
}





