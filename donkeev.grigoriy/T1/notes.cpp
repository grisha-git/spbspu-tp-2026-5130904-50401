#include<string>
#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>
#include<vector>
#include "Note.hpp"
#include "notes.hpp"

  void donkeev::createNote(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    if (notesMap.find(noteName) == notesMap.end())
    {
      notesMap[noteName] = std::make_shared< Note >();
    }

    std::string extraText;
    if (input >> extraText)
    {
      auto toignore = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(toignore, '\n');

      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
