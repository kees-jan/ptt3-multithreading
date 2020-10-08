#include <thread>

#include <messagequeue.h>

#include <gtest/gtest.h>

#include "test-helpers.h"

// TEST(exercise2, a_sequence_of_messages_can_be_queued)
// {
//   auto messages = {random_string(), random_string(), random_string()};

//   MessageQueue queue;

//   for(auto& message: messages)
//     queue.write(message);

//   for(auto& message: messages)
//     EXPECT_EQ(queue.try_read(), message);
// }

// namespace
// {
//   void write_messages(MessageQueue& queue, const std::vector<std::string>& messages)
//   {
//     for(auto& message: messages)
//       queue.write(message);
//   }

//   void read_expecting(MessageQueue& queue, const std::vector<std::string>& messages)
//   {
//     for(auto& expected: messages)
//     {
//       std::optional<std::string> current_message;

//       do
//       {
//         current_message = queue.try_read();
//       } while(!current_message);

//       EXPECT_EQ(current_message, expected);
//     }
//   }
// } // namespace

// TEST(exercise2, stress_test)
// {
//   const unsigned number_of_messages = 1000;
//   const auto     messages           = many_random_strings(number_of_messages);

//   MessageQueue             queue;
//   std::vector<std::thread> threads;

//   threads.emplace_back(write_messages, std::ref(queue), std::cref(messages));
//   threads.emplace_back(read_expecting, std::ref(queue), std::cref(messages));

//   for(auto& thread: threads)
//   {
//     thread.join();
//   }
// }
