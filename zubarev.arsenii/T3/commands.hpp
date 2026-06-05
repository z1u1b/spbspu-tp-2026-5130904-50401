#ifndef COMMANDS_POLY_HPP
#define COMMANDS_POLY_HPP
#include "structs.hpp"
#include <vector>
#include <iostream>
namespace zubarev
{
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void min(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void count(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void maxseq(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void same(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);

}

#endif
