#include "test-helpers.h"

std::ostream& operator<<(std::ostream& os, std::nullopt_t) { return os << "(nullopt)"; }

std::string random_string(unsigned length)
{
  static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

  std::string result;

  for(unsigned i = 0; i < length; ++i)
    result += alphanum[rand() % (sizeof(alphanum) - 1)];

  return result;
}

std::string random_string() { return random_string(16); }

std::vector<std::string> many_random_strings(unsigned count)
{
  std::vector<std::string> result;
  result.reserve(count);

  for(unsigned i = 0; i < count; ++i)
    result.push_back(random_string());

  return result;
}

// semaphore //////////////////////////////////////////////////////////

semaphore::semaphore(unsigned int count_)
  : count(count_)
{}

void semaphore::wait()
{
  std::unique_lock<std::mutex> lock(mut);

  cond.wait(lock, [&] { return count > 0; });

  count--;
}

bool semaphore::try_wait()
{
  std::lock_guard lock(mut);
  if(count > 0)
  {
    count--;
    return true;
  }

  return false;
}

void semaphore::signal()
{
  std::lock_guard lock(mut);
  count++;
  cond.notify_one();
}
