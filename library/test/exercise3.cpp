#include <thread>

#include <messagequeue.h>

#include <gtest/gtest.h>

#include "test-helpers.h"

using namespace std::literals::chrono_literals;

// TEST(exercise3, blocking_wait)
// {
//   auto         message = random_string();
//   MessageQueue queue;
//   semaphore    s;

//   std::thread t([&] {
//     std::string read = queue.read();
//     EXPECT_EQ(read, message);
//     s.signal();
//   });

//   EXPECT_FALSE(s.wait_for(2s));

//   queue.write(message);

//   EXPECT_TRUE(s.wait_for(10s));

//   t.join();
// }
