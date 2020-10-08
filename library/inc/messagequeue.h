#include <condition_variable>
#include <list>
#include <mutex>
#include <optional>
#include <string>

class MessageQueue
{
public:
  std::optional<std::string> try_read();
  std::string                read();
  void                       write(std::string newMessage);

private:
  std::string pop_and_get();

  std::mutex              m;
  std::condition_variable c;
  std::list<std::string>  messages;
};
