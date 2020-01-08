#pragma once

#include "Common/CommonHeader.h"
#include "Common/SingletonBaseClass.h"
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#define GetThreadPool Singleton<ThreadPool>::GetInstance()
class ThreadPool : public Singleton<ThreadPool>
{
public:
  friend class Singleton<ThreadPool>;
  void InitWorkers(size_t numberOfWorkers);
  //template <class F, class... Args>
  //void AddJobs(F&& f, Args&&... args)
  void AddTask(std::function<void()> task)
    //-> std::future< typename std::result_of<F(Args...)>::type>
  {
    //using returnType = typename std::result_of<F(Args...)>::type;
    //auto task = std::make_shared<std::packaged_task<void()> >(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    //std::future<returnType> ret = task->get_future();

    { //grab lock to make sure no race condition of assigning task to task queue
      std::unique_lock<std::mutex> lock(m_Mutex);
      m_Tasks.emplace(task);
    }
      //m_Tasks.emplace([task]() 
      //{
      //  (*task)();
      //})
    //wake up worker to do task since the task queue is assigned a new task
    m_CV.notify_one();
  }
private:
  ThreadPool() 
  : 
  m_StopWork(false), 
  m_NumberOfWorkers(std::thread::hardware_concurrency()) 
  {}
  ~ThreadPool()
  {
    { //grab lock to make sure no race condition of setting the stop work flag
      std::unique_lock<std::mutex> lock(m_Mutex);
      m_StopWork = true;
    }
    //wake up all workers, let them exit while loop so that main program is able to exit
    m_CV.notify_all();
    //wait for all workers to join before exiting the main program
    for (int i = 0; i < m_NumberOfWorkers; ++i) m_Workers[i].join();
  }

  std::vector<std::thread> m_Workers;
  std::queue<std::function<void()>> m_Tasks;
  bool m_StopWork;

  size_t m_NumberOfWorkers;
  std::mutex m_Mutex;
  std::condition_variable m_CV;
};

