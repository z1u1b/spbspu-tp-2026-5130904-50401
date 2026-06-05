#include "poly_functors.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>
namespace zubarev
{
  double AreaCount::operator()(const Polygon& pol) const
  {
    std::vector< double > tmp;
    std::transform(pol.points.begin(), pol.points.end(), std::back_inserter(tmp), AreaTriangleCount{pol.points});
    double sum = std::accumulate(tmp.begin(), tmp.end(), 0.0);
    return std::abs(sum) / 2.0;
  }
  double AreaTriangleCount::operator()(const Point& p1)
  {
    const Point& p2 = points.at((i + 1) % points.size());
    double res = p1.x * p2.y - p2.x * p1.y;
    ++i;
    return res;
  }

  bool FilterByCountVert::operator()(const Polygon& pol) const
  {
    if (pol.points.size() == count_vert) {
      return true;
    }
    return false;
  }
  bool FilterByOddVert::operator()(const Polygon& pol) const
  {
    return pol.points.size() % 2;
  }
  bool FilterByEvenVert::operator()(const Polygon& pol) const
  {
    return !(pol.points.size() % 2);
  }
}
