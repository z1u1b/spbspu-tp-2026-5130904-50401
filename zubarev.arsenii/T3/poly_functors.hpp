#ifndef POLY_FUNCTORS_HPP
#define POLY_FUNCTORS_HPP
#include "structs.hpp"
namespace zubarev
{
  struct AreaCount
  {
    double operator()(const Polygon&);
  };

  struct AreaTriangleCount
  {
    std::vector< Point > points;
    size_t i = 0;
    double operator()(const Point&);
  };
  struct FilterByVert
  {
    size_t count_vert = 0;
    bool operator()(const Polygon&);
  };

}

#endif
