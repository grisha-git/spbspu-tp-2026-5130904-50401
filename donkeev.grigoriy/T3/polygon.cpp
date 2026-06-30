#include "polygon.hpp"

#include <iostream>

donkeev::IOGuard::IOGuard(std::basic_ios<char>& s):
  s_(s),
  precision_(s.precision()),
  width_(s.width()),
  flags_(s.flags()),
  fill_(s.fill())
{}

donkeev::IOGuard::~IOGuard()
{
  s_.precision(precision_);
  s_.width(width_);
  s_.flags(flags_);
  s_.fill(fill_);
}

std::istream& donkeev::operator>>(std::istream& is, Point& p)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }

  IOGuard guard(is);
  char last = 0;
  Point temp = {0, 0};
  is >> Delimiter{'(', last} >> temp.x >> Delimiter{';', last} >> temp.y >> Delimiter{')', last};

  if (is)
  {
    p = temp;
  }
  return is;
}

std::ostream& donkeev::operator<<(std::ostream& os, const Point& p)
{
  os << '(' << p.x << ';' << p.y << ')';
  return os;
}

  bool donkeev::operator==(const Point& lhs, const Point& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
