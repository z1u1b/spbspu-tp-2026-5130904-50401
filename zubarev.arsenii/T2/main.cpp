#include "my_input.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  using T = zubarev::DataStruct;
  std::vector< T > data;

  using iit_t = std::istream_iterator< T >;

  iit_t it(std::cin);
  std::copy(it, iit_t{}, std::back_inserter(data));
  std::sort(data.begin(), data.end());

  using oit_t = std::ostream_iterator< T >;
  std::copy(data.begin(), data.end(), oit_t{std::cout, "\n"});
}
