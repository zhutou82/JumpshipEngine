#include "Common/MemoryManager.h"

//void * operator new (size_t size)
//{
//  return GetMemoryManager.AllocateMemory(size);
//}
//void* operator new [](size_t size)
//{
//  return GetMemoryManager.AllocateMemory(size);
//}
//
//void operator delete(void* toDelete)
//{
//  GetMemoryManager.DeallocateMemory(toDelete);
//}
//
//void operator delete[](void * toDelete)
//{
//  
//}

void MemoeryManager::Init()
{
  m_realPageSize = PAGE_SIZE + PADDING_SIZE * 2;
  size_t totalSizeOfMemory = NUMBER_OF_PAGES * m_realPageSize;
  // padding | page size | padding
  m_Head = reinterpret_cast<JSBYTE*>(malloc(totalSizeOfMemory));
  memset(m_Head, 0, totalSizeOfMemory);
  for (int i = 0, n = NUMBER_OF_PAGES; i < n; ++i)
  {
    PageHeader pageHeader;
    pageHeader.startAddr = m_Head + i * m_realPageSize;
    pageHeader.endAddr = m_Head + (i + 1) * m_realPageSize;
    pageHeader.isFree = true;
    pageHeader.freeAddr = pageHeader.startAddr + PADDING_SIZE;
    m_PageHeaderAllocationVec.push_back(pageHeader);
    //assign front and back padding to a magic number
    *(reinterpret_cast<int*>(pageHeader.startAddr)) = MAGIC_NUMBER;
    *(reinterpret_cast<int*>(pageHeader.startAddr + PADDING_SIZE + PAGE_SIZE)) = MAGIC_NUMBER; 
    //std::cout << "m_FreeAllocAddrInPage " << (void*)m_FreeAllocAddrInPage << std::endl;
    //std::cout << "m_FreeAllocAddrInPage front padding: " << *(reinterpret_cast<int*>(pageHeader.startAddr)) << std::endl;
    //std::cout << "m_FreeAllocAddrInPage back number: " << *(reinterpret_cast<int*>(pageHeader.startAddr + PAGE_SIZE + PADDING_SIZE)) << std::endl;
  }
}

void * MemoeryManager::AllocateMemory(size_t size)
{
  JSBYTE * endAddr = NULL;
  AllocationHeader allocation;
  for (auto& elem : m_PageHeaderAllocationVec)
  {
    bool foundLocationInBetweenAlloc = false;
    //if page is free, meaning it still have space
    if (elem.isFree)
    {
      endAddr = elem.freeAddr + size;
      //if current allocaton is able to allocate between two existing allcations
      for (auto& allocation : elem.allocationHeaderVec)
      {
        if (endAddr < allocation.startAddr)
        {
          foundLocationInBetweenAlloc = true;
          allocation.size = size;
          allocation.startAddr = elem.freeAddr;
          elem.freeAddr += size;
          //add allocation object to current page
          elem.allocationHeaderVec.push_back(allocation);
          std::cout << "Return adddr: " << reinterpret_cast<void*>(elem.freeAddr - size) << std::endl;
          return elem.freeAddr - size;
        }
      }
      //if current allocaton is not able to allocate between two existing allcations
      if (foundLocationInBetweenAlloc == false)
      {
        //current page has space for current allocation
        if (endAddr < elem.endAddr)
        {
          allocation.size = size;
          allocation.startAddr = elem.freeAddr;
          elem.freeAddr += size;
          //add allocation object to current page
          elem.allocationHeaderVec.push_back(allocation);
          std::cout << "Return adddr: " << reinterpret_cast<void*>(elem.freeAddr - size) << std::endl;
          return elem.freeAddr - size;
        }
        //if current page has no space for current allocation
        else
        { 
          continue;
        }
      }
    }
  }
  //return NULL, if the current allocation is greater than current page
  return NULL;
}
 
void MemoeryManager::DeallocateMemory(void * toDelete)
{
  std::cout << "Addr to delete: " << toDelete << std::endl;
  for (auto& elem : m_PageHeaderAllocationVec)
  {
    if (toDelete < elem.endAddr)
    {
      bool pointerFound = false;
      for (auto& allocation : elem.allocationHeaderVec)
      {
        if (allocation.startAddr == toDelete)
        {
          pointerFound = true;
          //clear the value
          memset(allocation.startAddr, 0, allocation.size);
          elem.freeAddr = allocation.startAddr;
          return;
        }
      }
      if (pointerFound == false)
      {
        std::cout << "Bad pointer " << std::endl;
      }

    }
  }
}



MemoeryManager::~MemoeryManager()
{
  for (auto& elem : m_PageHeaderAllocationVec)
  {
    
  }


  free(m_Head);
}
