#ifndef INPUT_POLY_HPP
#define INPUT_POLY_HPP
#include "structs.hpp"
namespace zubarev
{

  struct command
  {
    static std::vector< zubarev::Polygon >* polygons;
    command() = default;
  };
  std::istream& operator>>(std::istream&, command&);
  void input(std::istream& is, std::vector< zubarev::Polygon >& polygons);
}

#endif
