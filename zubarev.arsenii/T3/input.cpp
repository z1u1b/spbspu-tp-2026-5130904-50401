#include "input.hpp"
#include "commands.hpp"
#include "poly_functors.hpp"
#include <map>
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
    commands["INFRAME"] = &zubarev::same;

    std::string cmd;
    is >> cmd;
    if (!is) {
      return is;
    }

    try {
      commands.at(cmd)(is, std::cout, *command::polygons);
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      auto toignore = std::numeric_limits< std::streamsize >::max();
      std::cin.ignore(toignore, '\n');
    }
    return is;
  }

  void input(std::istream& is, std::vector< Polygon >& all_polygons)
  {
    std::vector< Polygon > temp_polygons((std::istream_iterator< Polygon >(is)), std::istream_iterator< Polygon >());
    std::copy_if(temp_polygons.begin(), temp_polygons.end(), std::back_inserter(all_polygons), FilterByCountVert{3});
  }
}
