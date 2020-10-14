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
  {
    auto result = std::move(messages.front());
    messages.pop_front();

    return result;
  }
}

void MessageQueue::write(std::string newMessage)
{
  std::scoped_lock l(m);
  messages.push_back(std::move(newMessage));
}
