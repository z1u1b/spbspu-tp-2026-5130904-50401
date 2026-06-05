#ifndef POLY_STRUCTS_HPP
#define POLY_STRUCTS_HPP

#include <vector>
#include <iostream>
namespace zubarev
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& is, Point& p);
  std::ostream& operator<<(std::ostream& os, const Point& p);
  bool operator==(const Point& lhs, const Point& rhs);
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& is, Polygon& p);
  std::ostream& operator<<(std::ostream& os, const Polygon& p);

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
    char expected;
    char& last;
  };
  std::istream& operator>>(std::istream& is, delimeter_t del);
  char check(std::istream& is, const char& expected);

}

#endif
