#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iostream>
#include <vector>
#include <ios>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <limits>

namespace donkeev
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream&, Point&);
  std::ostream& operator<<(std::ostream&, const Point&);
  bool operator==(const Point&, const Point&);

  struct Polygon
  {
    std::vector<Point> points;
  };

  std::istream& operator>>(std::istream&, Polygon&);
  std::ostream& operator<<(std::ostream&, const Polygon&);

  struct IOGuard
  {
    explicit IOGuard(std::basic_ios<char>&);
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

  std::istream& operator>>(std::istream&, Delimiter);
  char check(std::istream&, char);

  double getArea(const Polygon&);
  bool hasEvenVertices(const Polygon&);
  bool hasOddVertices(const Polygon&);
  bool hasNVertices(const Polygon&, size_t);
  bool isRightShape(const Polygon&);
  bool isRect(const Polygon&);
}

#endif
