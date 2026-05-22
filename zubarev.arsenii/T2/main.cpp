#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace stud
{
  struct p_t
  {

    int x, y;
  };
  struct IntUll
  {
    unsigned int& u;
  };
  std::ostream& operator<<(std::ostream& os, const IntUll& u)
  {
    os << u.u << "ull";
    return os;
  }

  std::ostream& operator<<(std::ostream& os, p_t p);
  std::istream& operator>>(std::istream& is, p_t& p);

  bool operator<(p_t lhs, p_t rhs);
  struct IOGuard
  {
    explicit IOGuard(std::basic_ios< char >& s):
      s_(s),
      precision_(s.precision()),
      width_(s.width()),
      flags_(s.flags()),
      fill_(s.fill())
    {}
    ~IOGuard()
    {
      s_.precision(precision_);
      s_.width(width_);
      s_.flags(flags_);
      s_.fill(fill_);
    }

  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios< char >::fmtflags flags_;
    char fill_;
  };

}

int main()
{
  using T = stud::p_t;
  std::vector< T > data;

  using iit_t = std::istream_iterator< T >;

  iit_t it(std::cin);
  std::copy(it, iit_t{}, std::back_inserter(data));

  std::sort(data.begin(), data.end());

  using oit_t = std::ostream_iterator< T >;
  std::copy(data.begin(), data.end(), oit_t{std::cout, "\n"});
}

char check(std::istream& is, char expected)
{
  char c = 0;
  is >> c;
  if (c != expected) {
    is.setstate(std::ios_base::failbit);
  }
  return c;
}
struct delimeter_t
{
  char expected;
  char& last;
};
std::istream& operator>>(std::istream& is, delimeter_t del)
{
  del.last = check(is, del.expected);
  return is;
}
std::istream& stud::operator>>(std::istream& is, p_t& p)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  IOGuard g(is);
  using del_t = delimeter_t;
  char last = 0;
  int x = 0, y = 0;
  is >> del_t{'(', last} >> x >> del_t{',', last} >> y >> del_t{')', last};

  if (is) {
    p = p_t{x, y};
  }
  return is;
}

std::ostream& stud::operator<<(std::ostream& os, p_t p)
{
  std::ostream::sentry s(os);
  if (!s) {
    return os;
  }
  return os << "(" << p.x << ", " << p.y << ")";
}

bool stud::operator<(p_t lhs, p_t rhs)
{
  if (lhs.x < rhs.x) {
    return true;
  }
  if (lhs.x == rhs.x) {
    if (lhs.y < rhs.y) {
      return true;
    }
    return false;
  }
  return false;
}
