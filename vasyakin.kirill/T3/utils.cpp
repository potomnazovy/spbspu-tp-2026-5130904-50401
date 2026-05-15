#include "utils.hpp"
#include <cmath>

vasyakin::GuardIO::GuardIO(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  width_(s.width()),
  flags_(s.flags()),
  fill_(s.fill())
{}

vasyakin::GuardIO::~GuardIO()
{
  s_.precision(precision_);
  s_.width(width_);
  s_.flags(flags_);
  s_.fill(fill_);
}