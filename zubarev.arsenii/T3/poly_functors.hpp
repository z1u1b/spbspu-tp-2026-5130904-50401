#ifndef POLY_FUNCTORS_HPP
#define POLY_FUNCTORS_HPP
#include "structs.hpp"
namespace zubarev
{
  struct AreaCount
  {
    double operator()(const Polygon&) const;
  };

  struct AreaTriangleCount
  {
    const std::vector< Point >& points;
    size_t i = 0;
    double operator()(const Point&);
  };
  struct FilterByCountVert
  {
    size_t count_vert = 0;
    bool operator()(const Polygon&) const;
  };
  struct FilterByOddVert
  {
    // size_t count_vert = 0;
    bool operator()(const Polygon&) const;
  };
  struct FilterByEvenVert
  {
    // size_t count_vert = 0;
    bool operator()(const Polygon&) const;
  };

  struct CountVert
  {
    size_t operator()(const Polygon&) const;
  };
  struct CountMax
  {
    const Polygon& ex_pol;
    size_t count = 0;
    size_t operator()(const Polygon&);
  };
  struct FilterBySame
  {
    const Polygon& ex_pol;
    bool operator()(const Polygon&);
  };
  struct NormalizePoint
  {
    const Point& base;
    Point operator()(const Point&);
  };
  struct NormalizePol
  {
    Polygon operator()(const Polygon&);
  };
  struct Overlay
  {
    const Polygon& in_pol;
    bool operator()(const Polygon&);
  };

}

#endif
