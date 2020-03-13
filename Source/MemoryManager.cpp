#include "Common/MemoryManager.h"
#include <thread>

#ifndef USING_GLOBAL_NEW
void * operator new (size_t size)
{
    return g_MemoryManager.AllocateMemory(size, 1);
}
void operator delete(void* toDelete) noexcept(true)
{
    return g_MemoryManager.DeallocateMemory(toDelete);
}
#endif

void * MemoeryManager::AllocateMemory(JSuint64 sz, JSuint32 numberOfAllocations)
{
    LogDebug("AllocateMemory, numberOfAllocations: %u\n", numberOfAllocations);
    JSuint64 allocationStrSize = sizeof(AllocationHeader);
    JSuint64 allocationSize = PADDING_SIZE + allocationStrSize + sz * numberOfAllocations + PADDING_SIZE;
    JSuint64 pageSize = allocationSize > PAGE_SIZE ? allocationSize : PAGE_SIZE;
    for (JSuint16 i = 0; i < NUMBER_OF_PAGES; ++i)
    {
        PageHeader& page = m_PageHeaderAllocationVec[i];
        if (!page.isInitialized)             page.Init(pageSize);
        else if (allocationSize > PAGE_SIZE) continue;             //if current page is initialized but allocaion is greater than current page, continue
        AllocationHeader* newAllocation = JSNULL;
        { //protect critical section
            std::unique_lock<std::mutex> lock(page.m_PageMutex);
            LogDebug("Current Allocated Page:\n");
            page.PrintPage();
            //if free allocation index number to use is equal to max number of allocation, means it has run out of all allocations
            newAllocation = page.allocationList.InsertAllocation(allocationSize);
        }
        
        //insert into allcation list and update new allocation properties
        if (newAllocation)
        {
            return newAllocation->startAddr + PADDING_SIZE + allocationStrSize;
        }
    }
    return JSNULL;
}

void MemoeryManager::DeallocateMemory(JSvoid * toDelete)
{
    LogDebug("Addr to delete: %p\n", toDelete);
    JSvoid* realToDeleteAddr = reinterpret_cast<JSbyte*>(toDelete) - sizeof(AllocationHeader) - PADDING_SIZE;
    JSassert(toDelete != JSNULL);
    //bad pointer if to delete addr is padding
    LogDebug("Real Addr to delete: %p\n", realToDeleteAddr);
    JSassert(*reinterpret_cast<JSint32*>(realToDeleteAddr) == MAGIC_NUMBER);
    for (auto& page : m_PageHeaderAllocationVec)
    {
        if (realToDeleteAddr <= page.endAddr && realToDeleteAddr >= page.startAddr)
        {
            AllocationHeader* allocationToDelete = JSNULL;
            { //protect critical section
                std::unique_lock<std::mutex> lock(page.m_PageMutex);
                page.PrintPage();
                allocationToDelete = page.allocationList.RemoveAllocation(realToDeleteAddr);
            }
            //printf("Size to delete: %u\n", allocationToDelete->size);
            if (allocationToDelete)
            {
                JSassert(*reinterpret_cast<JSint32*>(reinterpret_cast<JSbyte*>(realToDeleteAddr) + allocationToDelete->size - PADDING_SIZE) == MAGIC_NUMBER);
                memset(allocationToDelete->startAddr, INIT_VALUE, allocationToDelete->size);
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
    for (auto& page : m_PageHeaderAllocationVec)
    {
        free(page.startAddr);
    }
}

void AllocationLinkedList::InitAllocation(AllocationHeader *& newAllocation, JSbyte* startAddr, JSuint64 size)
{
    newAllocation = reinterpret_cast<AllocationHeader*>(reinterpret_cast<JSbyte*>(startAddr) + PADDING_SIZE);
    newAllocation->size = size;
    newAllocation->startAddr = startAddr;
    newAllocation->endAddr = startAddr + size;
    newAllocation->next = JSNULL;
    //set start and end addr to the addr without padding
    //add padding to start and end of new allocation
    *reinterpret_cast<JSint32*>(startAddr) = MAGIC_NUMBER;
    *reinterpret_cast<JSint32*>(startAddr + size - PADDING_SIZE) = MAGIC_NUMBER;
    memset(startAddr + PADDING_SIZE + sizeof(AllocationHeader),
           INIT_VALUE,
           size - 2 * PADDING_SIZE - sizeof(AllocationHeader));
}

AllocationHeader* AllocationLinkedList::InsertAllocation(JSuint64 allocationSize)
{
    JSbyte * endAddr = currentPage->startAddr + allocationSize;
    if (endAddr > currentPage->endAddr) return JSNULL;
    JSbyte * startAddr = currentPage->startAddr;
    AllocationHeader* curr = head;
    AllocationHeader* prev = head;
    AllocationHeader * newAllocation = JSNULL;
    bool locationToInsertFound = false;
    if (head == JSNULL)
    {
        InitAllocation(head, currentPage->startAddr, allocationSize);
        newAllocation = head;
        tail = head;
        locationToInsertFound = true;
    }
    while (curr && !locationToInsertFound)
    {
        if (endAddr <= curr->startAddr)
        {
            InitAllocation(newAllocation, startAddr, allocationSize);
            if (curr == head)
            {
                newAllocation->next = curr;
                head = newAllocation;
            }
            else
            {
                prev->next = newAllocation;
                newAllocation->next = curr;
            }
            locationToInsertFound = true;
        }
        startAddr = curr->endAddr;
        endAddr = startAddr + allocationSize;
        prev = curr;
        curr = curr->next;
    }
    if (endAddr < currentPage->endAddr && !locationToInsertFound)
    {
        InitAllocation(newAllocation, startAddr, allocationSize);
        tail->next = newAllocation;
        tail = tail->next;
    }
    PrintList();
    return newAllocation;
}
AllocationHeader * AllocationLinkedList::RemoveAllocation(void * addr)
{
    JSassert(addr != JSNULL);
    AllocationHeader* toDelete = JSNULL;
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
            toDelete = curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    PrintList();
    return toDelete;
}

void AllocationLinkedList::PrintList()
{
    AllocationHeader* tmpHead = head;
    if (!tmpHead)
    {
        LogDebug("Empty Page after deletion");
        return;
    }
    for (; tmpHead->next; tmpHead = tmpHead->next)
    {
        LogDebug("[ %p - %p ](%llu)->", reinterpret_cast<JSvoid*>(tmpHead->startAddr), reinterpret_cast<JSvoid*>(tmpHead->endAddr), tmpHead->size);
    }
    LogDebug("[ %p - %p ](%llu)\n", reinterpret_cast<JSvoid*>(tmpHead->startAddr), reinterpret_cast<JSvoid*>(tmpHead->endAddr), tmpHead->size);

}
//PageHeader

void PageHeader::Init(JSuint64 size, JSbool init)
{
    startAddr = reinterpret_cast<JSbyte*>(malloc(size));
    JSassert(startAddr != JSNULL);
    endAddr = startAddr + size;
    memset(startAddr, INIT_VALUE, size);
    isInitialized = init;
    LogDebug("New page allocated\n");
    PrintPage();
}

void PageHeader::PrintPage()
{
    LogDebug("Start address: %p End address: %p \n", reinterpret_cast<JSvoid*>(startAddr), 
                                                     reinterpret_cast<JSvoid*>(endAddr));
}


