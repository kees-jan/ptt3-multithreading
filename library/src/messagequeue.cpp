#include "messagequeue.h"

#include <cassert>
#include <thread>

using namespace std::literals::chrono_literals;

std::optional<std::string> MessageQueue::try_read()
{
  std::scoped_lock l(m);
  auto             result = std::move(message);
  message                 = std::nullopt;

  return result;
}

void MessageQueue::write(std::string newMessage)
{
  std::scoped_lock l(m);
  message = std::move(newMessage);
}
