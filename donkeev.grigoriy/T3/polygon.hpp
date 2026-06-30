#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>
#include <ios>

namespace donkeev
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& is, Point& p);
  std::ostream& operator<<(std::ostream& os, const Point& p);
  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector<Point> points;
  };

  std::istream& operator>>(std::istream& is, Polygon& p);
  std::ostream& operator<<(std::ostream& os, const Polygon& p);

  struct IOGuard
  {
    explicit IOGuard(std::basic_ios<char>& s);
    ~IOGuard();

  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios<char>::fmtflags flags_;
    char fill_;
  };

  struct Delimiter
  {
    char expected;
    char& last;
  };

  std::istream& operator>>(std::istream& is, Delimiter d);
  char check(std::istream& is, char expected);

  
}

#endif
