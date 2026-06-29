#include "inputStructs.hpp"

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
