#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>
#include<vector>
#include"notes.hpp"

using noteMap_t = std::unordered_map< std::string, std::shared_ptr< donkeev::Note > >;
using namespace donkeev;

int main()
{
  noteMap_t notesMap;
  std::unordered_map< std::string, void(*)(std::istream&, std::ostream&, noteMap_t&) > commands;
  commands["note"] = createNote;
  commands["line"] = addLine;
  commands["show"] = showNote;
  commands["drop"] = deleteNote;
  commands["link"] = addLink;
  commands["mind"] = showLinks;
  commands["halt"] = deleteLink;
  commands["expired"] = showExpiredLinks;
  commands["refresh"] = deleteExpiredLinks;

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, notesMap);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
  }
}
