#include "commands.hpp"
#include "poly_functors.hpp"
#include <iostream>
namespace zubarev
{
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons)
  {

    std::string parameter = "";
    is >> parameter;
    if (!is) {
      if (is.eof()) {
        if (is.eof()) {
          is.clear();
          is.setstate(std::ios_base::eofbit);
        } else {
          is.clear();
        }
        throw std::runtime_error("<INVALID COMMAND>");
      }
    }
    if (isdigit(parameter[0])) {
      size_t vert = std::stoi(parameter);
      std::vector< Polygon > tmp;
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(tmp), FilterByVert{vert});
    } else if (parameter == "EVEN") {

    } else if (parameter == "ODD") {

    } else if (parameter == "MEAN") {

    } else {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }
  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void min(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void count(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
  void maxseq(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons);
} // namespace zubarev
