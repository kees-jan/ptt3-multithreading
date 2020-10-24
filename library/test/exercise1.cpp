#include <thread>

#include <messagequeue.h>

#include <gtest/gtest.h>

#include "test-helpers.h"

TEST(dummy, apparently_gtest_needs_at_least_one_test) {}


TEST(exercise1, queue_is_initially_empty)
{
  MessageQueue               queue;
  std::optional<std::string> message = queue.try_read();

  EXPECT_EQ(message, std::nullopt);
}

TEST(exercise1, each_message_is_read_only_once)
{
  const std::string message = random_string();

  MessageQueue queue;
  queue.write(message);

  EXPECT_EQ(queue.try_read(), message);
  EXPECT_EQ(queue.try_read(), std::nullopt);
}

TEST(exercise1, a_sequence_of_messages_can_be_sent)
{
  auto messages = {random_string(), random_string(), random_string()};

  MessageQueue queue;

  for(auto& message: messages)
  {
    queue.write(message);
    EXPECT_EQ(queue.try_read(), message);
  }
}

namespace
{
  void write_repeatedly(MessageQueue& queue, unsigned count)
  {
    for(unsigned i = 0; i < count; ++i)
    {
      queue.write(random_string());
    }
  }

  void read_repeatedly(MessageQueue& queue, unsigned count)
  {
    for(unsigned i = 0; i < count; ++i)
      static_cast<void>(queue.try_read());
  }
} // namespace

TEST(exercise1, stress_test)
{
  const unsigned number_of_threads = 100;
  const unsigned number_of_actions = 10000;

  MessageQueue             queue;
  std::vector<std::thread> threads;

  for(unsigned i = 0; i < number_of_threads; ++i)
  {
    threads.emplace_back(write_repeatedly, std::ref(queue), number_of_actions);
    threads.emplace_back(read_repeatedly, std::ref(queue), number_of_actions);
    threads.emplace_back(read_repeatedly, std::ref(queue), number_of_actions);
  }

  for(auto& thread: threads)
  {
    thread.join();
  }
}
