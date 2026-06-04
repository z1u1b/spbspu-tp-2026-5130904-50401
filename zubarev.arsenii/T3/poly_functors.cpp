#include "poly_functors.hpp"
namespace zubarev
{
  double AreaCount::operator()(const Polygon& p)
  {
    std::vector< Polygon > tmp;
    std::transform(p.points.begin(), p.points.end(), std::back_inserter(tmp), AreaTriangleCount{p.points});
    double sum = std::accumulate(tmp.begin(), tmp.end(), 0.0);
    return abs(sum) / 2.0;
  }
  double AreaTriangleCount::operator()(const Point& p1)
  {
    const Point& p2 = points.at((i + 1) % points.size());
    double res = p1.x * p2.y - p2.x * p1.y;
    return res;
  }
}
