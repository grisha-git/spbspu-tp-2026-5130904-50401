#include<iostream>
#include<unordered_map>
#include<memory>
#include<vector>
#include"notes.hpp"

using noteMap_t = std::unordered_map< std::string, std::shared_ptr< donkeev::Note > >;


int main()
{
  std::unordered_map< std::string, std::shared_ptr< donkeev::Note > > notesMap;
  std::unordered_map< std::string, void(*)(const std::string&, noteMap_t&) > notesCommands;
  notesCommands["note"] = createNote;
  notesCommands["line"] = addLine;
  notesCommands["show"] = showNote;
  notesCommands["drop"] = deleteNote;

  std::unordered_map< std::string, void(*)(const std::string&, const std::string&, noteMap_t&) > linksCommands;
  linksCommands["link"] = addLink;
  linksCommands["mind"] = showLinks;
  linksCommands["halt"] = deleteLink;
  linksCommands["expired"] = showExpiredLinks;
  linksCommands["refresh"] = deleteExpiredLinks;
}