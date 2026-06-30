#include "cli.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

void readData(std::istream& is, std::vector<donkeev::Polygon>& polygons)
{
  if (is.eof())
  {
    return;
  }

  donkeev::Polygon p;
  if (is >> p)
  {
    polygons.push_back(p);
    readData(is, polygons);
    return;
  }

  if (is.eof())
  {
    return;
  }

  is.clear();
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  readData(is, polygons);
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Cannot open file: " << argv[1] << '\n';
    return 1;
  }

  std::vector<donkeev::Polygon> polygons;
  readData(file, polygons);
  donkeev::Command::polygons = &polygons;

  std::vector<donkeev::Command> commands;
  std::copy(
    std::istream_iterator<donkeev::Command>{std::cin},
    std::istream_iterator<donkeev::Command>{},
    std::back_inserter(commands));

  return 0;
}
