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

vasyakin::Triangle vasyakin::make_triangle(const std::vector< Point >& pts, size_t i)
{
  return Triangle{pts[0], pts[i], pts[i + 1]};
}

double vasyakin::triangleArea(Triangle tr)
{
  double value1 = static_cast< double >(tr.a.x) * (tr.b.y - tr.c.y);
  double value2 = static_cast< double >(tr.b.x) * (tr.c.y - tr.a.y);
  double value3 = static_cast< double >(tr.c.x) * (tr.a.y - tr.b.y);

  return 0.5 * std::fabs(value1 + value2 + value3);
}

double vasyakin::getArea(const Polygon& poly)
{
  if (poly.points.size() < 3)
  {
    throw std::invalid_argument("poly size must be >= 3");
  }

  std::vector< size_t > ind(poly.points.size() - 2);
  std::iota(ind.begin(), ind.end(), 1);

  std::vector< Triangle > tr(ind.size());
  std::transform(ind.begin(), ind.end(), tr.begin(),
    std::bind(make_triangle, std::cref(poly.points), std::placeholders::_1));

  std::vector< double > areas(tr.size());
  std::transform(tr.begin(), tr.end(), areas.begin(), triangleArea);

  return std::accumulate(areas.begin(), areas.end(), 0.0);
}
