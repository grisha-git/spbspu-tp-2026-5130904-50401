#include <iostream>
namespace donkeev
{
  struct DblSci
  {
    double double_;
  };

  std::istream& operator>>(std::istream&, DblSci&);
  std::ostream& operator<<(std::ostream&, const DblSci&);

  struct ChrLit
  {
    char char_;
  };

  std::istream& operator>>(std::istream&, ChrLit&);
  std::ostream& operator<<(std::ostream&, const ChrLit&);

  struct DataStruct
  {
    DblSci key1;
    ChrLit key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream&, DataStruct&);
  std::ostream& operator<<(std::ostream&, const DataStruct&);
}