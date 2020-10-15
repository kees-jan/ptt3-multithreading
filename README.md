# Multithreading workshop

This archive contains the exercises for the multithreading workshop

## Initial setup

These instructions are for the Ubuntu image provided by Fontys. If you're using anything else, things may be different for you.
* Clone this archive
* You should now be able to `make` the archive without errors
* You can then run `library/test/testMessageQueue`. That should not run any tests (yet), but otherwise be succesful.

## Tip: Use more than one core
Writing unittests to find threading issues is hard. So even if you have errors, the tests are not guaranteed to fail.

I've noticed that tests are more likely to fail if your machine (or VM) has more than 1 core. Unfortunately, the Fontys VM doesn't have that by default. I recommend you change it.

## If you happen to use Ubuntu 18.04 or 20.04 (but not the Fontys image)

* Install `cmake` and `googletest` before building the archive.

## Assignment

In `library/test`, you'll find four files, called `exercise1.cpp` through `exercise4.cpp`. These contain google tests that are currently commented out. You are to uncomment these tests, one by one, and make them pass. For that, you'll want to edit `library/inc/messagequeue.h` and `library/src/messagequeue.cpp`

You should not change any of the tests (other than uncommenting them). When you're done, all tests for all four exercises should be uncommented. No commenting them out again!

Details on the 4 exercises are further down. Be sure to read at least the description of exercise 4, since it is different from the other three.

When you're done, test output should roughly look as follows:

    Running main() from gtest_main.cc
    [==========] Running 9 tests from 4 test cases.
    [----------] Global test environment set-up.

    [----------] 1 test from dummy
    [ RUN      ] dummy.apparently_gtest_needs_at_least_one_test
    [       OK ] dummy.apparently_gtest_needs_at_least_one_test (0 ms)
    [----------] 1 test from dummy (0 ms total)

    [----------] 5 tests from exercise1
    [ RUN      ] exercise1.queue_is_initially_empty
    [       OK ] exercise1.queue_is_initially_empty (0 ms)
    [ RUN      ] exercise1.queue_can_be_written_to_and_read_from
    [       OK ] exercise1.queue_can_be_written_to_and_read_from (1 ms)
    [ RUN      ] exercise1.each_message_is_read_only_once
    [       OK ] exercise1.each_message_is_read_only_once (0 ms)
    [ RUN      ] exercise1.a_sequence_of_messages_can_be_sent
    [       OK ] exercise1.a_sequence_of_messages_can_be_sent (0 ms)
    [ RUN      ] exercise1.stress_test
    [       OK ] exercise1.stress_test (57 ms)
    [----------] 5 tests from exercise1 (58 ms total)
    
    [----------] 2 tests from exercise2
    [ RUN      ] exercise2.a_sequence_of_messages_can_be_queued
    [       OK ] exercise2.a_sequence_of_messages_can_be_queued (0 ms)
    [ RUN      ] exercise2.stress_test
    [       OK ] exercise2.stress_test (5 ms)
    [----------] 2 tests from exercise2 (5 ms total)
    
    [----------] 1 test from exercise3
    [ RUN      ] exercise3.blocking_wait
    [       OK ] exercise3.blocking_wait (2001 ms)
    [----------] 1 test from exercise3 (2001 ms total)
    
    [----------] 1 test from exercise4
    [ RUN      ] exercise4.communicating_threads
    That took 5ms and 10ms of cpu time
    [       OK ] exercise4.communicating_threads (5 ms)
    [----------] 1 test from exercise4 (5 ms total)
    
    [----------] Global test environment tear-down
    [==========] 10 tests from 5 test cases ran. (2069 ms total)
    [  PASSED  ] 10 tests.
    


## Tip: CppReference

In the exercise, you'll be using a number of classes from the standard library. If you want to know how they work, I recommend visiting [cppreference.com](https://www.cppreference.com). It is very extensive, and has a great search facility.

## Variation: Test driven development

Test driven development is about taking small, incremental steps. At its extreme, you write the smallest failing test possible (and not compiling is considered a failure), and then make the smallest change possible to fix the failure, and so on until there are no more failing tests to write.

If you want to try that, you could uncomment not a whole testcase at a time, but instead uncomment it line by line.

For example, the first test reads:

    TEST(exercise1, queue_is_initially_empty)
    {
      MessageQueue               queue;
      std::optional<std::string> message = queue.try_read();

      EXPECT_EQ(message, std::nullopt);
    }
The first line of this test would force you to create the `MessageQueue` class (which I've done for you). The second line then forces you to create the `try_read()` method. In order to compile, that should always return something (i.e. `std::nullopt`). Having done so, the test passes. No `write()` method needed yet, nor any class members.

## Variation: Pair programming

You could choose to do this exercise in pairs. Two see more than one. You take turns. When it is your turn
* Cleanup the code that's currently there (if necessary)
* Uncomment a (line of a) test
* Check that it fails
* Fix it
* End of turn

## A note on VS code

This archive contains some settings files for VS Code. Most stuff should just work. On the other had, I am by no means a VS Code expert. Therefore, it still reports many warnings and issues that are not correct (for example because it assumes an ancient C++ standard), and that I've not been able to silence.

* Make sure you have `bear` and `clang` installed
* After cloning the repository do a `bear make` instead of a regular `make`
  * This will create the database with compilation commands `compile_commands.json` that VS Code needs.
  * You only need to do this once. Call `make` normally from now on (or trigger a build from within VS Code)

Pull requests for the settings files are very welcome ;-)

## More detailed exercise descriptions

### Exercise 1

Write a simple `MessageQueue` class, that has a `write()` method for storing messages, and a non-blocking `try_read()` method for reading them. That is, when there is a message available, `try_read()` should return it, but otherwise not. For this we'll be using the [std::optional](https://en.cppreference.com/w/cpp/utility/optional) class from the standard library

### Exercise 2

A very simple `MessageQueue` contains only one item, the last one written to it. In this exercise, we're going to extend it to contain multiple messages.

### Exercise 3

Up until now, we've been using the non-blocking `try_read()` method. Often, we'll want to simply wait until a message becomes available. In this exercise, we'll write a blocking `read()` method that does just that.

### Exercise 4

A very simple blocking `read()` method just does `try_read()` in a loop, until it finally returns a message. In order to not use too much CPU, you might put a [sleep](https://en.cppreference.com/w/cpp/thread/sleep_for) in there. However, it is hard to know upfront how long to sleep exactly.

When you finished Exercise 3, the test of this exercise will pass without further problems. It will also print how long the test took to execute, and how much cpu you used.

For a solution without sleeps, that might read:

    That took 264ms
    and 3840ms of cpu time

On the other hand, for a solution with a rather long sleep, it might read:

    That took 16502ms
    and 20ms of cpu time

As you can see, we have one solution that is quick, but expensive (CPU-wise), and one solution that is slow but cheap. In this exercise, we aim for the best of both worlds: A solution that sleeps just long enough, but not longer. 

The time to beat:

    That took 3ms
    and 20ms of cpu time

Tip: Use a [condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable).

Tip: Run only the test in exercise 4 by typing
    
    ./library/test/testMessageQueue --gtest_filter=exercise4.\*
