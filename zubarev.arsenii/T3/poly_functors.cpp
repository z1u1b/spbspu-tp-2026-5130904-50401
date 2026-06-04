#include "poly_functors.hpp"
#include <algorithm>
#include <iostream>
namespace zubarev
{
  double AreaCount::operator()(const Polygon& pol)
  {
    std::vector< Polygon > tmp;
    std::transform(pol.points.begin(), pol.points.end(), std::back_inserter(tmp), AreaTriangleCount{pol.points});
    double sum = std::accumulate(tmp.begin(), tmp.end(), 0.0);
    return abs(sum) / 2.0;
  }
  double AreaTriangleCount::operator()(const Point& p1)
  {
    const Point& p2 = points.at((i + 1) % points.size());
    double res = p1.x * p2.y - p2.x * p1.y;
    return res;
  }

  bool FilterByVert::operator()(const Polygon& pol)
  {
    if (pol.points.size() == count_vert) {
      return true;
    }
    return false;
  }
}
