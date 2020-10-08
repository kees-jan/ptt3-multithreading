#include <iostream>
#include <thread>

#include <messagequeue.h>
#include <sys/times.h>
#include <time.h>

#include <gtest/gtest.h>

#include "test-helpers.h"

namespace
{
  class echo
  {
  public:
    echo()
      : thread(&echo::do_echo, this)
    {}

    ~echo()
    {
      write(terminateCommand);
      thread.join();
    }

    [[nodiscard]] std::string read() { return outgoing.read(); }
    void                      write(std::string newMessage) { incoming.write(std::move(newMessage)); }

  private:
    void do_echo()
    {
      for(;;)
      {
        std::string message = incoming.read();
        if(message == terminateCommand)
          break;

        outgoing.write(std::move(message));
      }
    }

    static const std::string terminateCommand;

    MessageQueue incoming;
    MessageQueue outgoing;
    std::thread  thread;
  };

  const std::string echo::terminateCommand = "terminate";

  class Timer
  {
  public:
    Timer()
      : start(std::chrono::steady_clock::now())
    {
      auto t = times(&cpu_start);
      if(t == -1)
        perror("times");
    }

    ~Timer()
    {
      auto       end = std::chrono::steady_clock::now();
      struct tms cpu_end;
      auto       t = times(&cpu_end);
      if(t == -1)
        perror("times");

      auto cpu_time =
        (cpu_end.tms_utime + cpu_end.tms_stime - cpu_start.tms_utime - cpu_start.tms_stime) * 1000 / sysconf(_SC_CLK_TCK);

      std::cout << "That took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms "
                << "and " << cpu_time << "ms of cpu time\n";
    }

  private:
    std::chrono::steady_clock::time_point start;
    struct tms                            cpu_start;
  };
} // namespace

TEST(exercise4, communicating_threads)
{
  Timer timer;

  const unsigned number_of_threads = 4*std::thread::hardware_concurrency();
  const unsigned number_of_actions = 10;

  std::vector<echo>        echoers(number_of_threads);
  std::vector<std::thread> threads;

  for(unsigned i = 0; i < number_of_threads; ++i)
  {
    threads.emplace_back([&echoer = echoers[i]] {
      const auto messages = many_random_strings(number_of_actions);
      for(auto& message: messages)
      {
        echoer.write(message);
        auto result = echoer.read();

        EXPECT_EQ(result, message);
      }
    });
  }

  for(auto& thread: threads)
  {
    thread.join();
  }
}
