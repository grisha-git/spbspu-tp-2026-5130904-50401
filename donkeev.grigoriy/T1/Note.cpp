#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Note.hpp"

void donkeev::Note::addLine(std::string text)
{
  textLines_.push_back(text);
}

void donkeev::Note::addLink(const std::shared_ptr< Note >& ptr)
{
  for (auto it = links_.begin(); it != links_.end();)
  {
    if (!it->owner_before(ptr) && !ptr.owner_before(*it))
    {
      return;
    }
    else
    {
      ++it;
    }
  }

  links_.push_back(ptr);
}
void donkeev::Note::deleteLink(const std::shared_ptr< Note >& ptr)
{
  for (auto it = links_.begin(); it != links_.end();)
  {
    if (!it->owner_before(ptr) && !ptr.owner_before(*it))
    {
      it = links_.erase(it);
      return;
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
  while (it != textLines_.cend())
  {
    output << *it << '\n';
    ++it;
  }

  return output;
}
