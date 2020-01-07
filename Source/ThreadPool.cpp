#include "ThreadPool.h"

void ThreadPool::InitWorkers(size_t numberOfWorkers)
{
  m_NumberOfWorkers = std::move(numberOfWorkers);
  //m_Workers.reserve(m_NumberOfWorkers);
  //for (int i = 0; i < m_NumberOfWorkers; ++i)
  //{
  //  m_Workers.emplace_back(std::thread());
  //}

  for (int i = 0; i < m_NumberOfWorkers; ++i)
  {
    m_Workers.emplace_back([this]()
    {
      while (true)
      {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(this->m_Mutex);
          this->m_CV.wait(lock, [this]()
          {
            return !this->m_Tasks.empty();
          });
          task = std::move(this->m_Tasks.front());
          this->m_Tasks.pop();
        }
        task();
      }

    }
    );
  }
}

void ThreadPool::AssignWorkersForJobs()
{
  for (int i = 0; i < m_NumberOfWorkers; ++i)
  {
    m_Workers[i] = std::move(std::thread([this]()
    {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lock(this->m_Mutex);
        this->m_CV.wait(lock, [this]()
        {
          return !this->m_Tasks.empty();
        });
        task = std::move(this->m_Tasks.front());
        this->m_Tasks.pop();
      }
      task();
    }
    ));
  }
}

void ThreadPool::StartWork()
{
  m_CV.notify_all();
  m_StartWork = true;
  for (int i = 0; i < m_NumberOfWorkers; ++i)
  {
    //if(m_Workers[i].joinable()) 
      m_Workers[i].join();
  }
  
}
