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
    std::vector<std::pair<std::string, std::weak_ptr<Note>>> links_;

  public:
    void addLine(const std::string);
    
    void addLink(const std::string, const std::shared_ptr< Note >&);
    void deleteLink(const std::shared_ptr< Note >&);
    void deleteExpiredLinks();

    std::ostream& showText(std::ostream&);
    std::ostream& showLinks(std::ostream&);
    std::ostream& showExpiredLinks(std::ostream&);
  };
}

#endif
