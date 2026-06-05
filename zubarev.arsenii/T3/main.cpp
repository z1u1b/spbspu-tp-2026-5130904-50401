#include <iostream>
#include "input.hpp"
#include <fstream>
#include <iterator>
#include <algorithm>
#include "poly_functors.hpp"
int main(int argc, char** argv)
{
  if (argc != 2) {
    return 1;
  }
  std::fstream file;
  std::ifstream f(argv[1]);
  if (!f.is_open()) {
    return 1;
  }

  std::vector< zubarev::Polygon > polygons;
  input(f, polygons);

  zubarev::command::polygons = &polygons;

  static_cast< void >(std::find_if(std::istream_iterator< zubarev::command >(std::cin),
                                   std::istream_iterator< zubarev::command >(),
                                   zubarev::False{}));
}
