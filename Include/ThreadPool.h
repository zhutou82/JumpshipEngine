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
  void AssignWorkersForJobs();
  template <class F, class... Args>
  void AddJobs(F&& f, Args&&... args)
    //-> std::future< typename std::result_of<F(Args...)>::type>
  {
    //using returnType = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<void()> >(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    //std::future<returnType> ret = task->get_future();
    {
      std::unique_lock<std::mutex> lock(m_Mutex);
      m_Tasks.emplace([task]() 
      {
        (*task)();
      });
    }
    m_CV.notify_one();
  }
  void StartWork();
private:
  ThreadPool() {}
  std::vector<std::thread> m_Workers;
  std::queue<std::function<void()>> m_Tasks;
  bool m_StartWork;

  size_t m_NumberOfWorkers;
  std::mutex m_Mutex;
  std::condition_variable m_CV;

};

