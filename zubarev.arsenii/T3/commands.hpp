#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "structs.hpp"
namespace zubarev
{
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void min(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void count(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void maxseq(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
}

#endif
