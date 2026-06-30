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

std::istream& donkeev::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  
  char c = 0;
  in >> c;
  if (in && (c != dest.exp_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
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

std::ostream& donkeev::operator<<(std::ostream& out, const DblSci& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
    
  IOGuard guard(out);
  out << std::fixed << std::setprecision(1);
    
  double test = val.double_;
  if (test == 0.0)
  {
    out << "0.0e+0";
    return out;
  }
  
  int exponent = 0;
  double mantissa = test;
  
  if (std::abs(mantissa) >= 10.0)
  {
    while (std::abs(mantissa) >= 10.0)
    {
      mantissa /= 10.0;
      ++exponent;
    }
  }
  else if (std::abs(mantissa) < 1.0 && test != 0.0)
  {
    while (std::abs(mantissa) < 1.0)
    {
      mantissa *= 10.0;
      --exponent;
    }
  }
    
  out << mantissa << 'e';
  if (exponent >= 0)
  {
    out << '+';
  }
  out << exponent;
  
  return out;
}

bool donkeev::operator<(const DblSci& lhs, const DblSci& rhs)
{
  return lhs.double_ < rhs.double_;
}

bool donkeev::operator==(const DblSci& lhs, const DblSci& rhs)
{
  return lhs.double_ == rhs.double_;
}

std::istream& donkeev::operator>>(std::istream& in, ChrLit& val)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  
  char quote1 = 0;
  in >> quote1;
  
  if (quote1 != '\'')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  
  char ch = 0;
  in >> ch;
  
  char quote2 = 0;
  in >> quote2;
  
  if (quote2 != '\'')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  
  if (in)
  {
    val.char_ = ch;
  }
  
  return in;
}

std::ostream& donkeev::operator<<(std::ostream& out, const ChrLit& val)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  
  out << '\'' << val.char_ << '\'';
  return out;
}

bool donkeev::operator<(const ChrLit& lhs, const ChrLit& rhs)
{
  return lhs.char_ < rhs.char_;
}

bool donkeev::operator==(const ChrLit& lhs, const ChrLit& rhs)
{
  return lhs.char_ == rhs.char_;
}


