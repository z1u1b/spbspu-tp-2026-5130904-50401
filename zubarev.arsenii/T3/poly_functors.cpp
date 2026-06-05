#include "poly_functors.hpp"
#include <algorithm>
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

  size_t CountMax::operator()(const Polygon& pol)
  {
    if (ex_pol.points == pol.points) {
      count += 1;
    } else {
      count = 0;
    }
    return count;
  }

  Polygon NormalizePol::operator()(const Polygon& pol)
  {
    Point base = pol.points[0];
    Polygon p_new;
    std::transform(pol.points.begin(), pol.points.end(), std::back_inserter(p_new.points), NormalizePoint{base});
    return p_new;
  }
  Point NormalizePoint::operator()(const Point& pt)
  {
    return Point{pt.x - base.x, pt.y - base.y};
  }
  bool Overlay::operator()(const Polygon& pol)
  {
    Polygon A;
    Polygon B;

    std::transform(pol.points.begin(), pol.points.end(), std::back_inserter(A.points), NormalizePol{});
    std::transform(in_pol.points.begin(), in_pol.points.end(), std::back_inserter(B.points), NormalizePol{});

    Polygon BB;
    BB.points.reserve(B.points.size() * 2);
    BB.points.insert(BB.points.end(), B.points.begin(), B.points.end());
    BB.points.insert(BB.points.end(), B.points.begin(), B.points.end());

    return std::search(BB.points.begin(), BB.points.end(), A.points.begin(), A.points.end()) != BB.points.end();
  }

}
