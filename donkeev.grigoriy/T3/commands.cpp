#include "commands.hpp"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <string>
#include <cctype>
#include <limits>

bool isNumber(const std::string& str)
{
  return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

void donkeev::area(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons)
{
  std::string arg;
  is >> arg;

  if (!is)
  {
    throw std::invalid_argument("invalid command");
  }

  std::vector<Polygon> filtered;

  if (arg == "EVEN")
  {
    std::copy_if(polygons.begin(), polygons.end(),
                  std::back_inserter(filtered), hasEvenVertices);
  }
  else if (arg == "ODD")
  {
    std::copy_if(polygons.begin(), polygons.end(),
                  std::back_inserter(filtered), hasOddVertices);
  }
  else if (arg == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("no polygons for mean");
    }
    filtered = polygons;
  }
  else if (isNumber(arg))
  {
    size_t count = std::stoull(arg);
    if (count < 3)
    {
      throw std::invalid_argument("invalid vertex count");
    }
    std::copy_if(polygons.begin(), polygons.end(),
                  std::back_inserter(filtered),
                  [count](const Polygon& p) { return hasNVertices(p, count); });
  }
  else
  {
    throw std::invalid_argument("invalid command");
  }

  std::vector<double> areas(filtered.size());
  std::transform(filtered.begin(), filtered.end(), areas.begin(), getArea);
  double result = std::accumulate(areas.begin(), areas.end(), 0.0);

  if (arg == "MEAN")
  {
    result /= static_cast<double>(polygons.size());
  }

  os << std::fixed << std::setprecision(1) << result << '\n';
}

void donkeev::max(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("no polygons for max");
  }

  std::string arg;
  is >> arg;

  if (!is)
  {
    throw std::invalid_argument("invalid command");
  }

  if (arg == "AREA")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon& lhs, const Polygon& rhs)
        {
          return getArea(lhs) < getArea(rhs);
        });
    os << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
  }
  else if (arg == "VERTEXES")
  {
    auto it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon& lhs, const Polygon& rhs)
        {
          return lhs.points.size() < rhs.points.size();
        });
    os << it->points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("invalid command");
  }
}

void donkeev::min(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("no polygons for min");
  }

  std::string arg;
  is >> arg;

  if (!is)
  {
    throw std::invalid_argument("invalid command");
  }

  if (arg == "AREA")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon& lhs, const Polygon& rhs)
        {
          return getArea(lhs) < getArea(rhs);
        });
    os << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
  }
  else if (arg == "VERTEXES")
  {
    auto it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon& lhs, const Polygon& rhs)
        {
          return lhs.points.size() < rhs.points.size();
        });
    os << it->points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("invalid command");
  }
}

void donkeev::count(std::istream& is, std::ostream& os, const std::vector<Polygon>& polygons)
{
  std::string arg;
  is >> arg;

  if (!is)
  {
    throw std::invalid_argument("invalid command");
  }

  size_t result = 0;

  if (arg == "EVEN")
  {
    result = std::count_if(polygons.begin(), polygons.end(), hasEvenVertices);
  }
  else if (arg == "ODD")
  {
    result = std::count_if(polygons.begin(), polygons.end(), hasOddVertices);
  }
  else if (isNumber(arg))
  {
    size_t count = std::stoull(arg);
    if (count < 3)
    {
      throw std::invalid_argument("invalid vertex count");
    }
    result = std::count_if(polygons.begin(), polygons.end(),
        [count](const Polygon& p) { return hasNVertices(p, count); });
  }
  else
  {
    throw std::invalid_argument("invalid command");
  }

  os << result << '\n';
}
  