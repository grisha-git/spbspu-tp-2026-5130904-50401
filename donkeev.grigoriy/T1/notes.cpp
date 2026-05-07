#include<string>
#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>
#include<vector>
#include<iomanip>
#include "Note.hpp"
#include "notes.hpp"

  void donkeev::createNote(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    if (notesMap.find(noteName) == notesMap.end())
    {
      notesMap[noteName] = std::make_shared< Note >();
    }
  }

  void donkeev::addLine(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    std::string text;
    if (!(input >> std::quoted(text)))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    auto it = notesMap.find(noteName);
    if (it == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    it->second->addLine(text);
  }

  void donkeev::showNote(std::istream& input, std::ostream& output, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    auto it = notesMap.find(noteName);
    if (it == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    auto notePtr = it->second;
    notePtr->showText(output);
  }

  void donkeev::deleteNote(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    auto it = notesMap.find(noteName);
    if (it == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    notesMap.erase(noteName);
  }

  void donkeev::addLink(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteFromName;
    std::string noteToName;
    if (!(input >> noteFromName))
    {
      return;
    }
    if (!(input >> noteToName))
    {
      return;
    }

    auto itFrom = notesMap.find(noteFromName);
    auto itTo = notesMap.find(noteToName);
    if (itFrom == notesMap.end() || itTo == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    itFrom->second->addLink(noteToName, itTo->second);
  }

  void donkeev::showLinks(std::istream& input, std::ostream& output, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    auto it = notesMap.find(noteName);
    if (it == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    it->second->showLinks(output);
  }

  void donkeev::deleteLink(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteFromName;
    std::string noteToName;
    if (!(input >> noteFromName))
    {
      return;
    }
    if (!(input >> noteToName))
    {
      return;
    }

    auto itFrom = notesMap.find(noteFromName);
    auto itTo = notesMap.find(noteToName);
    if (itFrom == notesMap.end() || itTo == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    itFrom->second->deleteLink(itTo->second);
  }

  void donkeev::showExpiredLinks(std::istream& input, std::ostream& output, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    auto it = notesMap.find(noteName);
    if (it == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    it->second->showExpiredLinks(output);
  }

  void donkeev::deleteExpiredLinks(std::istream& input, std::ostream&, noteMap_t& notesMap)
  {
    std::string noteName;
    if (!(input >> noteName))
    {
      return;
    }

    auto it = notesMap.find(noteName);
    if (it == notesMap.end())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    std::string extraText;
    std::getline(input, extraText);
    if (!extraText.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    it->second->deleteExpiredLinks();
  }
