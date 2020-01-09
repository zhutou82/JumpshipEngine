#include "ThreadPool.h"

void ThreadPool::InitWorkers()
{
  for (int i = 0; i < m_NumberOfWorkers; ++i)
  {
    m_Workers.emplace_back([this] () {
      //put while true to make workers wait jobs till program exit
      while (true)
      {
        std::function<void()> task;
        { //grab the lock make sure no race condition of getting the tasks
          std::unique_lock<std::mutex> lock(this->m_Mutex);
          //put worker to sleep while there is no task
          this->m_CV.wait(lock, [this](){ return !this->m_Tasks.empty() || this->m_StopWork; }); /*while (this->m_Tasks.empty() && !this->m_StopWork) this->m_CV.wait(lock); */
          //exit thread when there is no tasks left and stop work is true (will only be set at threadpool destructor
          if (this->m_Tasks.empty() && this->m_StopWork)
            return;
          //get the task from the task queue
          task = std::move(this->m_Tasks.front());
          //remove the task from task queue
          this->m_Tasks.pop();
        }//release the lock
        //perform task
        task();
      }
    }
    );
  }
}
