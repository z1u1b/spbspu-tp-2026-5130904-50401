#include "input.hpp"
#include "commands.hpp"
#include "poly_functors.hpp"
#include <map>
#include <iterator>
#include <limits>
#include <algorithm>
#include <sstream>
namespace zubarev
{
  std::vector< zubarev::Polygon >* zubarev::command::polygons = nullptr;
  std::istream& operator>>(std::istream& is, command&)
  {
    using cmd_t = void (*)(std::istream&, std::ostream&, const std::vector< zubarev::Polygon >&);

    static std::map< std::string, cmd_t > commands;
    commands["AREA"] = &zubarev::area;
    commands["MAX"] = &zubarev::max;
    commands["MIN"] = &zubarev::min;
    commands["COUNT"] = &zubarev::count;
    commands["MAXSEQ"] = &zubarev::maxseq;
    commands["SAME"] = &zubarev::same;

    std::string cmd;
    is >> cmd;
    if (!is) {
      return is;
    }
    std::string rest_of_line;
    std::getline(is, rest_of_line);
    std::stringstream ss(rest_of_line);
    try {
      commands.at(cmd)(ss, std::cout, *command::polygons);
      std::string extra;
      if (ss >> extra) {
        throw std::runtime_error("<INVALID COMMAND>");
      }
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      // auto toignore = std::numeric_limits< std::streamsize >::max();
      // std::cin.ignore(toignore, '\n');
    }
    return is;
  }

  // void input(std::istream& is, std::vector< Polygon >& all_polygons)
  // {
  //   std::vector< Polygon > temp_polygons((std::istream_iterator< Polygon >(is)), std::istream_iterator< Polygon >());
  //   std::copy_if(temp_polygons.begin(), temp_polygons.end(), std::back_inserter(all_polygons), IsPolygon{});
  // }

  void input(std::istream& is, std::vector< zubarev::Polygon >& all_polygons)
  {
    std::string line;

    if (!std::getline(is, line)) {
      return;
    }

    std::stringstream ss(line);
    Polygon p;

    std::string extra;
    if (ss >> p && !(ss >> extra)) {
      if (IsPolygon{}(p)) {
        all_polygons.push_back(p);
      }
    }
    input(is, all_polygons);
  }
}
