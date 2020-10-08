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
  std::mutex             m;
  std::list<std::string> messages;
};
