#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <vector>

namespace zubarev
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& is, Point& p);
  std::istream& operator<<(std::ostream& os, const Point& p);
  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream& operator>>(std::istream& is, Polygon& p);
  std::istream& operator<<(std::ostream& os, const Polygon& p);

}

#endif
