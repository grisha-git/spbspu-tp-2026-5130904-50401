#include "polygon.hpp"

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

std::istream& donkeev::operator>>(std::istream& is, Polygon& p)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }

  IOGuard guard(is);
  Polygon temp;
  size_t count_points = 0;
  is >> count_points;

  if (count_points < 3)
  {
    is.setstate(std::ios_base::failbit);
    return is;
  }

  temp.points.reserve(count_points);
  std::copy_n(std::istream_iterator<Point>(is), count_points, std::back_inserter(temp.points));

  if (temp.points.size() != count_points || !is)
  {
    is.setstate(std::ios_base::failbit);
    return is;
  }

  p = temp;
  return is;
}

std::ostream& donkeev::operator<<(std::ostream& os, const Polygon& p)
{
  if (p.points.empty())
  {
    return os;
  }

  os << p.points.size() << " ";
  std::copy(p.points.begin(), p.points.end() - 1,
            std::ostream_iterator<Point>(os, " "));
  os << *(p.points.end() - 1);
  return os;
}

std::istream& donkeev::operator>>(std::istream& is, Delimiter d)
{
  d.last = check(is, d.expected);
  return is;
}

std::istream& donkeev::operator>>(std::istream& is, Delimiter d)
{
  d.last = check(is, d.expected);
  return is;
}

double donkeev::getArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }

  double area = 0.0;
  size_t n = polygon.points.size();

  for (size_t i = 0; i < n; ++i)
  {
    const Point& p1 = polygon.points[i];
    const Point& p2 = polygon.points[(i + 1) % n];
    area += static_cast<double>(p1.x) * p2.y - static_cast<double>(p2.x) * p1.y;
  }

  return std::abs(area) / 2.0;
}

bool donkeev::hasEvenVertices(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool donkeev::hasOddVertices(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

bool donkeev::hasNVertices(const Polygon& polygon, size_t n)
{
  return polygon.points.size() == n;
}

 bool donkeev::isRightShape(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return false;
  }

  size_t n = polygon.points.size();

  for (size_t i = 0; i < n; ++i)
  {
    const Point& a = polygon.points[i];
    const Point& b = polygon.points[(i + 1) % n];
    const Point& c = polygon.points[(i + 2) % n];

    long long abx = static_cast<long long>(b.x) - a.x;
    long long aby = static_cast<long long>(b.y) - a.y;
    long long bcx = static_cast<long long>(c.x) - b.x;
    long long bcy = static_cast<long long>(c.y) - b.y;

    if (abx * bcx + aby * bcy == 0)
    {
      return true;
    }
  }

  return false;
}

bool donkeev::isRect(const Polygon& polygon)
{
  if (polygon.points.size() != 4)
  {
    return false;
  }

  const auto& pts = polygon.points;
  long long dx01 = static_cast<long long>(pts[1].x) - pts[0].x;
  long long dy01 = static_cast<long long>(pts[1].y) - pts[0].y;
  long long dx12 = static_cast<long long>(pts[2].x) - pts[1].x;
  long long dy12 = static_cast<long long>(pts[2].y) - pts[1].y;
  long long dx23 = static_cast<long long>(pts[3].x) - pts[2].x;
  long long dy23 = static_cast<long long>(pts[3].y) - pts[2].y;
  long long dx30 = static_cast<long long>(pts[0].x) - pts[3].x;
  long long dy30 = static_cast<long long>(pts[0].y) - pts[3].y;

  return (dx01 * dx12 + dy01 * dy12 == 0) &&
          (dx12 * dx23 + dy12 * dy23 == 0) &&
          (dx23 * dx30 + dy23 * dy30 == 0) &&
          (dx30 * dx01 + dy30 * dy01 == 0);
}
