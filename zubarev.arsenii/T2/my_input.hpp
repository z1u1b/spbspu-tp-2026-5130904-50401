#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace zubarev
{
  // struct p_t
  // {
  //   int x, y;
  // };
  //   std::ostream& operator<<(std::ostream& os, p_t p);
  // std::istream& operator>>(std::istream& is, p_t& p);
  // bool operator<(p_t lhs, p_t rhs);
  // std::istream& zubarev::operator>>(std::istream& is, p_t& p)
  // {
  //   std::istream::sentry s(is);
  //   if (!s) {
  //     return is;
  //   }
  //   IOGuard g(is);
  //   using del_t = delimeter_t;
  //   char last = 0;
  //   int x = 0, y = 0;
  //   is >> del_t{'(', last} >> x >> del_t{',', last} >> y >> del_t{')', last};

  //   if (is) {
  //     p = p_t{x, y};
  //   }
  //   return is;
  // }
  // std::ostream& zubarev::operator<<(std::ostream& os, p_t p)
  // {
  //   std::ostream::sentry s(os);
  //   if (!s) {
  //     return os;
  //   }
  //   return os << "(" << p.x << ", " << p.y << ")";
  // }

  // bool zubarev::operator<(p_t lhs, p_t rhs)
  // {
  //   if (lhs.x < rhs.x) {
  //     return true;
  //   }
  //   if (lhs.x == rhs.x) {
  //     if (lhs.y < rhs.y) {
  //       return true;
  //     }
  //     return false;
  //   }
  //   return false;
  // }

  struct DblSci
  {
    double d;
  };
  std::istream& operator>>(std::istream& is, DblSci& ul);
  std::ostream& operator<<(std::ostream& os, const DblSci& ul);
  bool operator<(const DblSci& lhs, const DblSci& rhs);
  bool operator==(const DblSci& lhs, const DblSci& rhs);

  struct SllLit
  {
    long long s;
  };
  std::istream& operator>>(std::istream& is, SllLit& ul);
  std::ostream& operator<<(std::ostream& os, const SllLit& ul);
  bool operator<(const SllLit& lhs, const SllLit& rhs);
  bool operator==(const SllLit& lhs, const SllLit& rhs);

  struct DataStruct
  {
    DblSci key1;
    SllLit key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);

  // struct IntUll
  // {
  //   unsigned int& u;
  // };
  // std::ostream& operator<<(std::ostream& os, const IntUll& u)
  // {
  //   os << u.u << "ull";
  //   return os;
  // }

  struct IOGuard
  {
    explicit IOGuard(std::basic_ios< char >& s):
      s_(s),
      precision_(s.precision()),
      width_(s.width()),
      flags_(s.flags()),
      fill_(s.fill())
    {}
    ~IOGuard()
    {
      s_.precision(precision_);
      s_.width(width_);
      s_.flags(flags_);
      s_.fill(fill_);
    }

  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios< char >::fmtflags flags_;
    char fill_;
  };

  struct delimeter_t
  {
    std::vector< char > expected;
    char& last;
  };
  std::istream& operator>>(std::istream& is, delimeter_t del);

  char check(std::istream& is, std::vector< char >& expected);

}
