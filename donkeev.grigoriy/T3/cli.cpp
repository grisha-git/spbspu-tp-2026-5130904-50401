#include "cli.hpp"
#include "commands.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

namespace donkeev
{
  const std::vector<Polygon>* Command::polygons = nullptr;

  std::istream& operator>>(std::istream& is, Command&)
  {
    std::string name;
    is >> name;

    if (!is)
    {
      return is;
    }

    static std::unordered_map<std::string,
        std::function<void(std::istream&, std::ostream&, const std::vector<Polygon>&)>> commands;

    if (commands.empty())
    {
      commands["AREA"] = area;
      commands["MAX"] = max;
      commands["MIN"] = min;
      commands["COUNT"] = count;
      commands["INFRAME"] = inframe;
      commands["RIGHTSHAPES"] = rightShapes;
    }

    try
    {
      commands.at(name)(is, std::cout, *Command::polygons);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      is.clear();
      is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return is;
  }
}
