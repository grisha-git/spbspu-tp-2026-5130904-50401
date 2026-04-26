#ifndef NOTES_HPP
#define NOTES_HPP
#include<unordered_map>
#include"Note.hpp"

namespace donkeev
{
  using noteMap_t = std::unordered_map< std::string, std::shared_ptr< donkeev::Note > >;

  void createNote(std::istream&, std::ostream&, noteMap_t&);
  void addLine(std::istream&, std::ostream&, noteMap_t&);
  void showNote(std::istream&, std::ostream&, noteMap_t&);
  void deleteNote(std::istream&, std::ostream&, noteMap_t&);

  void addLink(std::istream&, std::ostream&, noteMap_t&);
  void showLinks(std::istream&, std::ostream&, noteMap_t&);
  void deleteLink(std::istream&, std::ostream&, noteMap_t&);
  void showExpiredLinks(std::istream&, std::ostream&, noteMap_t&);
  void deleteExpiredLinks(std::istream&, std::ostream&, noteMap_t&);
}

#endif
