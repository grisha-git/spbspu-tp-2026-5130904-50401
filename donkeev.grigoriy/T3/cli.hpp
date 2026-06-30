#ifndef CLI_HPP
#define CLI_HPP

#include <iosfwd>
#include <vector>
#include "polygon.hpp"

namespace donkeev
{
  struct Command
  {
    static const std::vector<donkeev::Polygon>* polygons;
  };

  std::istream& operator>>(std::istream& is, Command&);
}

#endif
