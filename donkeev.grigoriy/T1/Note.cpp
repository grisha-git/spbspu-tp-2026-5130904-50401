#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Note.hpp"

void donkeev::Note::addLine(const std::string text)
{
  textLines_.push_back(text);
}

void donkeev::Note::addLink(const std::string noteName, const std::shared_ptr< Note >& ptr)
{
  for (auto it = links_.begin(); it != links_.end();)
  {
    auto ptrToFind = it->second;
    if (!ptrToFind.owner_before(ptr) && !ptr.owner_before(ptrToFind))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    else
    {
      ++it;
    }
  }

  links_.push_back({noteName, ptr});
}
void donkeev::Note::deleteLink(const std::shared_ptr< Note >& ptr)
{
  bool isSuchLink = false;
  for (auto it = links_.begin(); it != links_.end();)
  {
    auto ptrToFind = it->second;
    if (!ptrToFind.owner_before(ptr) && !ptr.owner_before(ptrToFind))
    {
      it = links_.erase(it);
      isSuchLink = true;
      break;
    }
    else
    {
      ++it;
    }
  }

  if (!isSuchLink)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}
void donkeev::Note::deleteExpiredLinks()
{
  auto it = links_.cbegin();
  while (it != links_.cend())
  {
    if (it->second.expired())
    {
      it = links_.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

std::ostream& donkeev::Note::showText(std::ostream& output)
{
  auto it = textLines_.cbegin();

  if (it == textLines_.cend())
  {
    output << '\n';
  }

  while (it != textLines_.cend())
  {
    output << *it << '\n';
    ++it;
  }

  return output;
}
std::ostream& donkeev::Note::showLinks(std::ostream& output)
{
  auto it = links_.cbegin();
  
  if (it == links_.cend())
  {
    output << '\n';
  }
  
  while (it != links_.cend())
  {
    if (!it->second.expired())
    {
      output << it->first << '\n';
    }
    ++it;
  }

  return output;
}
std::ostream& donkeev::Note::showExpiredLinks(std::ostream& output)
{
  auto it = links_.cbegin();
  size_t count = 0;
  while (it != links_.cend())
  {
    if (it->second.expired())
    {
      ++count;
    }
    ++it;
  }

  output << count << '\n';

  return output;
}
