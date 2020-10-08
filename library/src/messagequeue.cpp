#include "messagequeue.h"

#include <cassert>
#include <thread>

using namespace std::literals::chrono_literals;

std::optional<std::string> MessageQueue::try_read()
{
  std::scoped_lock l(m);
  if(messages.empty())
    return std::nullopt;
  else
    return pop_and_get();
}

std::string MessageQueue::read()
{
  std::unique_lock<std::mutex> l(m);

  while(messages.empty())
  {
    c.wait(l);
  }

  return pop_and_get();
}

void MessageQueue::write(std::string newMessage)
{
  std::scoped_lock l(m);
  messages.push_back(std::move(newMessage));
  c.notify_one();
}

std::string MessageQueue::pop_and_get()
{
  assert(!messages.empty());

  auto result = std::move(messages.front());
  messages.pop_front();

  return result;
}