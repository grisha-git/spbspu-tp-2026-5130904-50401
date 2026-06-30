#include <iostream>
#include <iomanip>
namespace donkeev
{
  struct IOGuard
  {
    explicit IOGuard(std::basic_ios< char >&);

    ~IOGuard();

  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios< char >::fmtflags flags_;
    char fill_;
  };

  struct DelimiterIO
  {
    char exp_;
  };

  std::istream& operator>>(std::istream&, DelimiterIO&&);

  struct DblSci
  {
    double double_;
  };

  std::istream& operator>>(std::istream&, DblSci&);
  std::ostream& operator<<(std::ostream&, const DblSci&);
  bool operator<(const DblSci&, const DblSci&);
  bool operator==(const DblSci&, const DblSci&);


  struct ChrLit
  {
    char char_;
  };

  std::istream& operator>>(std::istream&, ChrLit&);
  std::ostream& operator<<(std::ostream&, const ChrLit&);
  bool operator<(const ChrLit&, const ChrLit&);
  bool operator==(const ChrLit&, const ChrLit&);

  struct DataStruct
  {
    DblSci key1;
    ChrLit key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream&, DataStruct&);
  std::ostream& operator<<(std::ostream&, const DataStruct&);
  bool operator<(const DataStruct&, const DataStruct&);
}
