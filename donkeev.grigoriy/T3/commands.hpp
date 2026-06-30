#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace donkeev
{
  void area(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons);
  void max(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons);
  void min(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons);
  void count(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons);
  void inframe(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons);
  void rightShapes(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons);
}

#endif
