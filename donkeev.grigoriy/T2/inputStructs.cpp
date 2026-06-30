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

std::istream& donkeev::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  IOGuard guard(in);

  DataStruct input;
  bool hasKey1 = false;
  bool hasKey2 = false;
  bool hasKey3 = false;

  in >> DelimiterIO{ '(' };
  in >> DelimiterIO{ ':' };

  while (in && in.peek() != ')')
  {
    std::string field;
    in >> field;

    if (!in)
    {
      return in;
    }

    if (field == "key1")
    {
      in >> input.key1;
      hasKey1 = true;
    }
    else if (field == "key2")
    {
      in >> input.key2;
      hasKey2 = true;
    }
    else if (field == "key3")
    {
      in >> std::quoted(input.key3);
      hasKey3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> DelimiterIO{ ':' };
  }

  in >> DelimiterIO{ ':' };
  in >> DelimiterIO{ ')' };

  if (in && hasKey1 && hasKey2 && hasKey3)
  {
    dest = input;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& donkeev::operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  IOGuard guard(out);
  out << "(:key1 " << src.key1;
  out << ":key2 " << src.key2;
  out << ":key3 " << std::quoted(src.key3) << ":)";

  return out;
}

bool donkeev::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 < rhs.key1)
  {
    return true;
  }
  if (rhs.key1 < lhs.key1)
  {
    return false;
  }

  if (lhs.key2 < rhs.key2)
  {
    return true;
  }
  if (rhs.key2 < lhs.key2)
  {
    return false;
  }

  return lhs.key3.length() < rhs.key3.length();
}
