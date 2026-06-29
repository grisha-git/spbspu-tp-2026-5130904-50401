#include "inputStructs.hpp"

donkeev::IOGuard::IOGuard(std::basic_ios< char >& s):
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

std::istream& donkeev::operator>>(std::istream& in, DblSci& val)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  double test;
  in >> test;
    
  if (in)
  {
    val.double_ = test;
  }

  return in;
}
