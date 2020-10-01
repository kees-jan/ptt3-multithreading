#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <condition_variable>
#include <mutex>
#include <optional>
#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::optional<T> v)
{
  if(v)
    return os << *v;
  else
    return os << "(nullopt)";
}

std::ostream& operator<<(std::ostream& os, std::nullopt_t);

[[nodiscard]] std::string              random_string();
[[nodiscard]] std::vector<std::string> many_random_strings(unsigned count);

class semaphore
{
public:
  explicit semaphore(unsigned int count = 0);
  void signal();

  void               wait();
  [[nodiscard]] bool try_wait();

  template <class Rep, class Period>
  [[nodiscard]] bool wait_for(const std::chrono::duration<Rep, Period>& rel_time)
  {
    std::unique_lock<std::mutex> lock(mut);

    if(cond.wait_for(lock, rel_time, [&] { return count > 0; }))
    {
      count--;
      return true;
    }
    else
      return false;
  }

private:
  std::mutex              mut;
  std::condition_variable cond;
  unsigned int            count;
};

#endif
