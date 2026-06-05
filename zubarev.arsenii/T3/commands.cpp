#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <string>
#include <cctype>

#include "poly_functors.hpp"

namespace zubarev
{
  double areaSum(const std::vector< Polygon >& polys)
  {
    std::vector< double > areas;
    std::transform(polys.begin(), polys.end(), std::back_inserter(areas), AreaCount{});
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }
  void area(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons)
  {

    std::string parameter = "";
    is >> parameter;
    if (!is) {
      if (is.eof()) {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      } else {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }

    if (isdigit(parameter[0])) {
      size_t vert = std::stoull(parameter);
      if (vert < 3) {
        throw std::runtime_error("<INVALID COMMAND>");
      }
      std::vector< Polygon > tmp;
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(tmp), FilterByCountVert{vert});

      os << std::fixed << std::setprecision(1) << areaSum(tmp) << '\n';
    } else if (parameter == "EVEN") {
      std::vector< Polygon > tmp;
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(tmp), FilterByEvenVert{});

      os << std::fixed << std::setprecision(1) << areaSum(tmp) << '\n';

    } else if (parameter == "ODD") {
      std::vector< Polygon > tmp;
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(tmp), FilterByOddVert{});

      os << std::fixed << std::setprecision(1) << areaSum(tmp) << '\n';

    } else if (parameter == "MEAN") {
      if (polygons.size() < 1) {
        throw std::runtime_error("<INVALID COMMAND>");
      }

      os << std::fixed << std::setprecision(1) << areaSum(polygons) / polygons.size() << '\n';

    } else {
      throw std::runtime_error("<INVALID COMMAND>");
    }
  }
  void max(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons)
  {
    if (polygons.size() < 1) {
      throw std::runtime_error("<INVALID COMMAND>");
    }

    std::string parameter = "";
    is >> parameter;
    if (!is) {
      if (is.eof()) {
        is.clear();
        is.setstate(std::ios_base::eofbit);
      } else {
        is.clear();
      }
      throw std::runtime_error("<INVALID COMMAND>");
    }
    if (parameter == "VERTEXES") {
      std::vector< size_t > count_vert;
      std::transform(polygons.begin(), polygons.end(), std::back_inserter(count_vert), CountVert{});
      os << *std::max_element(count_vert.begin(), count_vert.end()) << '\n';
    } else if (parameter == "AREA") {
      std::vector< double > areas;
      std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), AreaCount{});
      os << std::fixed << std::setprecision(1) << *std::max_element(areas.begin(), areas.end()) << '\n';
    }
  }
  // void min(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons)
  // {}
  // void count(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons)
  // {}
  // void maxseq(std::istream& is, std::ostream& os, const std::vector< Polygon >& polygons)
  // {}
}
