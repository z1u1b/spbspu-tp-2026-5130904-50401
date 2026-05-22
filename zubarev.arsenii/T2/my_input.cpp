#include "my_input.hpp"
#include <iomanip>
#include <cmath>
namespace zubarev
{
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
  std::istream& operator>>(std::istream& is, DblSci& db)
  {
    std::istream::sentry s(is);
    if (!s) {
      return is;
    }
    IOGuard g(is);
    using del_t = zubarev::delimeter_t;
    char last = 0;

    double mantissa = 0.0;
    char sign = 0;
    int power = 0;

    is >> mantissa;
    is >> del_t{{'E', 'e'}, last};
    is >> del_t{{'+', '-'}, last};
    if (is) {
      sign = last;
    }
    is >> power;
    if (is) {
      if (sign == '-') {
        power = -power;
      }
      db.d = mantissa * std::pow(10, power);
    }
    return is;
  }

  std::ostream& operator<<(std::ostream& os, const DblSci& db)
  {
    std::ostream::sentry s(os);
    if (!s) {
      return os;
    }
    IOGuard g(os);

    double value = std::abs(db.d);
    int power = 0;
    if (value == 0.0) {
      return os << "0.0e+0";
    }
    while (value >= 10.0) {
      value /= 10.0;
      ++power;
    }
    while (value > 0.0 && value < 1.0) {
      value *= 10.0;
      --power;
    }
    if (db.d < 0.0) {
      value *= -1;
    }

    os << value;
    os << 'e';
    if (power >= 0) {
      os << '+';
    }
    os << power;
    return os;
  }
  bool operator<(const DblSci& lhs, const DblSci& rhs)
  {
    return lhs.d < rhs.d;
  }
  bool operator==(const DblSci& lhs, const DblSci& rhs)
  {
    return lhs.d == rhs.d;
  }

  std::istream& operator>>(std::istream& is, SllLit& sl)
  {
    std::istream::sentry s(is);
    if (!s) {
      return is;
    }
    IOGuard g(is);
    using del_t = zubarev::delimeter_t;
    char last = 0;

    long long number = 0;

    is >> number;
    is >> del_t{{'L', 'l'}, last};
    is >> del_t{{'L', 'l'}, last};

    if (is) {
      sl.s = number;
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const SllLit& sl)
  {
    std::ostream::sentry s(os);
    if (!s) {
      return os;
    }
    return os << sl.s << "ll";
  }
  bool operator<(const SllLit& lhs, const SllLit& rhs)
  {
    return lhs.s < rhs.s;
  }
  bool operator==(const SllLit& lhs, const SllLit& rhs)
  {
    return lhs.s == rhs.s;
  }

  std::istream& operator>>(std::istream& is, DataStruct& ds)
  {
    std::istream::sentry s(is);
    if (!s) {
      return is;
    }
    IOGuard g(is);
    using del_t = zubarev::delimeter_t;
    char last = 0;
    is >> del_t{{'('}, last};

    DblSci key1;
    SllLit key2;
    std::string key3;
    bool has1 = false, has2 = false, has3 = false;
    while (is) {

      is >> del_t{{':'}, last};
      std::string field;
      is >> field;
      if (field == "key1") {
        is >> key1;
        has1 = true;
      } else if (field == "key2") {
        is >> key2;
        has2 = true;
      } else if (field == "key3") {
        is >> std::quoted(key3);
        has3 = true;
      } else {
        is.setstate(std::ios::failbit);
      }
    }

    if (is && has1 && has2 && has3) {
      ds.key1 = key1;
      ds.key2 = key2;
      ds.key3 = key3;
    } else {
      is.setstate(std::ios::failbit);
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
  {
    std::ostream::sentry s(os);

    if (!s) {
      return os;
    }
    return os << "(:key1 " << ds.key1 << ":key2 " << ds.key2 << ":key3 " << std::quoted(ds.key3) << ":)";
  }
  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1<lhs.key1) {
      return true;
    }
    if (rhs.key1<lhs.key1) {
      return false;
    }
    if (rhs.key2<lhs.key2) {
      return true;
    }
    if (lhs.key2<rhs.key2) {
      return false;
    }
    return lhs.key3<rhs.key3;
  }

  char check(std::istream& is, const std::vector< char >& expected)
  {
    char c = 0;
    is >> c;
    for (auto it = expected.begin(); it != expected.end(); ++it) {
      if (c != *it) {
        is.setstate(std::ios_base::failbit);
        break;
      }
    }

    return c;
  }

  std::istream& operator>>(std::istream& is, zubarev::delimeter_t del)
  {
    del.last = zubarev::check(is, del.expected);
    return is;
  }
}
