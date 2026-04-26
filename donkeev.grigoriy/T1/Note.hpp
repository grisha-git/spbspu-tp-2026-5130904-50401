#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>
#include <vector>
#include <memory>

namespace donkeev
{
  class Note
  {
    std::vector< std::string > textLines_;
    std::vector< std::weak_ptr< Note > > links_;

  public:
    void addLine(std::string);
    
    void addLink(const std::shared_ptr< Note >& ptr);
    void deleteLink(const std::shared_ptr< Note >& ptr);
  };
}

#endif
