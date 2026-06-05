#include "structs.hpp"
#include <sstream>
#include <iterator>
#include <algorithm>
namespace zubarev
{
  std::istream& operator>>(std::istream& is, Point& p)
  {
    std::istream::sentry s(is);
    if (!s) {
      return is;
    }
    IOGuard g(is);
    int x = 0, y = 0;
    char last = 0;
    is >> delimeter_t{'(', last};
    is >> x;
    is >> delimeter_t{';', last};
    is >> y;
    is >> delimeter_t{')', last};
    if (is) {
      p.x = x;
      p.y = y;
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const Point& p)
  {
    std::ostream::sentry s(os);
    if (!s) {
      return os;
    }
    return os << '(' << p.x << ';' << p.y << ')';
  }
  bool operator==(const Point& lhs, const Point& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  std::istream& operator>>(std::istream& is, Polygon& p)
  {
    std::istream::sentry s(is);
    if (!s) {
      return is;
    }
    IOGuard g(is);

    std::string line;
    if (std::getline(is, line)) {
      p.points.clear();
      if (line.empty()) {
        return is;
      }

      std::stringstream ss(line);
      size_t count = 0;

      if (ss >> count) {
        std::vector< Point > tmp;
        std::copy(std::istream_iterator< Point >(ss), std::istream_iterator< Point >(), std::back_inserter(tmp));

        std::string dummy;
        if (tmp.size() == count && !(ss >> dummy)) {
          p.points = std::move(tmp);
          return is;
        }
      }
    }
    is.setstate(std::ios_base::failbit);
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const Polygon& p)
  {
    std::ostream::sentry s(os);
    if (!s) {
      return os;
    }
    os << p.points.size() << " ";
    if (!p.points.empty()) {
      os << " ";
      std::copy(p.points.begin(), p.points.end(), std::ostream_iterator< Point >(os, " "));
    }
    return os;
  }

  char check(std::istream& is, const char& expected)
  {
    char c = 0;
    is >> c;

    if (c != expected) {
      is.setstate(std::ios_base::failbit);
    }
    return c;
  }

  std::istream& operator>>(std::istream& is, zubarev::delimeter_t del)
  {
    del.last = zubarev::check(is, del.expected);
    return is;
  }
}
