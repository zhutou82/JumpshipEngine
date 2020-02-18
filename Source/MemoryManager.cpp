#include "Common/MemoryManager.h"
#include <thread>


#ifndef USING_GLOBAL_NEW
void * operator new (size_t size)
{
    return g_MemoryManager.AllocateMemory(size, 1);
}
//void* operator new [](size_t size)
//{
//        return g_MemoryManager.AllocateMemory(size);
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
        if (!page.isInitialized) page.Init(pageSize, true);
        //LogDebug("Page start address: %p End address: %p\n", reinterpret_cast<JSvoid*>(page.startAddr), reinterpret_cast<JSvoid*>(page.endAddr));
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
        if (realToDeleteAddr <= page.endAddr && realToDeleteAddr >= page.startAddr)
        {
            //LogDebug("Page start address: %p End address: %p\n", reinterpret_cast<JSvoid*>(page.startAddr), reinterpret_cast<JSvoid*>(page.endAddr));
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

//Allocation Header
void AllocationHeader::AddPadding()
{
    //set start and end addr to the addr without padding
    //add padding to start and end of new allocation
    *reinterpret_cast<JSint32*>(startAddr) = MAGIC_NUMBER;
    *reinterpret_cast<JSint32*>(endAddr - PADDING_SIZE) = MAGIC_NUMBER;
    //fill the allocated space to 0
    memset(startAddr + PADDING_SIZE, INIT_VALUE, size - 2 * PADDING_SIZE);
}
void AllocationHeader::Init(JSbyte * s, JSuint64 sz, JSuint32 indexToUse)
{
    JSassert(s != JSNULL);
    startAddr = s;
    endAddr = startAddr + sz;
    size = sz;
    index = indexToUse;
}

//AllocationLinkedList
void AllocationLinkedList::AddAllocation(AllocationHeader * data)
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
bool AllocationLinkedList::InsertAllocation(AllocationHeader * data, JSbyte * pageEndAddr)
{
    JSassert(data != JSNULL || pageEndAddr != JSNULL);
    if (data->endAddr > pageEndAddr) return false;
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
AllocationHeader * AllocationLinkedList::RemoveAllocation(void * addr)
{
    JSassert(addr != JSNULL);
    AllocationHeader* curr = head;
    AllocationHeader* prev = head;
    while (curr)
    {
        if (curr->startAddr == addr)
        {
            prev->next = curr->next;
            if (curr == head)            head = curr->next;
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

void AllocationLinkedList::PrintList()
{
    AllocationHeader* tmpHead = head;
    if (tmpHead == JSNULL)
    {
        LogDebug("Empty Page after deletion");
        return;
    }

    for (; tmpHead->next; tmpHead = tmpHead->next)
    {

        //LogDebug("[ %p - %p ](%llu)->", reinterpret_cast<JSvoid*>(tmpHead->startAddr), reinterpret_cast<JSvoid*>(tmpHead->endAddr), tmpHead->size);
        //std::cout << GLOBAL::SQUARE_BRACKET_O << reinterpret_cast<JSvoid*>(tmpHead->startAddr) << GLOBAL::DASH << reinterpret_cast<JSvoid*>(tmpHead->endAddr) << GLOBAL::SQUARE_BRACKET_C
        //                    << GLOBAL::BRACKET_O << tmpHead->size << GLOBAL::BRACKET_C << GLOBAL::ARROW;
    }
    //LogDebug("[ %p - %p ](%llu)\n", reinterpret_cast<JSvoid*>(tmpHead->startAddr), reinterpret_cast<JSvoid*>(tmpHead->endAddr), tmpHead->size);

}
//PageHeader

void PageHeader::Init(JSuint64 size, JSbool init)
{
    startAddr = reinterpret_cast<JSbyte*>(malloc(size));
    JSassert(startAddr != JSNULL);
    endAddr = startAddr + size;
    memset(startAddr, INIT_VALUE, size);
    isInitialized = init;
    PrintPage();
}
void PageHeader::RemoveAllocation(AllocationHeader * allocationToRemove)
{
    //clear the value 
    memset(allocationToRemove->startAddr, INIT_VALUE, allocationToRemove->size);
    freeAllocationIndex.SetKBitToZero(allocationToRemove->index);
}
void PageHeader::PrintPage()
{
    //printf("New page allocated\n Start address: %p End address: %p \n", reinterpret_cast<JSvoid*>(startAddr), reinterpret_cast<JSvoid*>(endAddr));
}


