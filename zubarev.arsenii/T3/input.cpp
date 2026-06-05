#include "input.hpp"
#include "commands.hpp"
#include <map>
namespace zubarev
{
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
  void input(std::istream& is, std::vector< zubarev::Polygon >& polygons)
  {}
}
