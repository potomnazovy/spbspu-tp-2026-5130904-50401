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

bool has_even_vertices(const vasyakin::Polygon& p)
{
  if (p.points.size() % 2 == 0)
  {
    return true;
  }
  return false;
}

bool has_odd_vertices(const vasyakin::Polygon& p)
{
  if (p.points.size() % 2 != 0)
  {
    return true;
  }
  return false;
}

bool has_n_vertices(const vasyakin::Polygon& p, size_t n)
{
  if (p.points.size() == n)
  {
    return true;
  }
  return false;
}

bool area_less(const vasyakin::Polygon& lhs, const vasyakin::Polygon& rhs)
{
  return vasyakin::getArea(lhs) < vasyakin::getArea(rhs);
}

bool vertices_less(const vasyakin::Polygon& lhs, const vasyakin::Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool operator==(const vasyakin::Point& a, const vasyakin::Point& b)
{
  return a.x == b.x && a.y == b.y;
}

bool is_permutation_of(const vasyakin::Polygon& candidate, const vasyakin::Polygon& reference)
{
  if (candidate.points.size() != reference.points.size())
  {
    return false;
  }

  return std::is_permutation(candidate.points.begin(), candidate.points.end(), reference.points.begin());
}

bool is_rect(const vasyakin::Polygon& candidate)
{
  if (candidate.points.size() != 4)
  {
    return false;
  }

  const auto& pts = candidate.points;

  long long x01 = pts[1].x - pts[0].x;
  long long y01 = pts[1].y - pts[0].y;

  long long x12 = pts[2].x - pts[1].x;
  long long y12 = pts[2].y - pts[1].y;

  long long x23 = pts[3].x - pts[2].x;
  long long y23 = pts[3].y - pts[2].y;

  long long x30 = pts[0].x - pts[3].x;
  long long y30 = pts[0].y - pts[3].y;

  return (x01 * x12 + y01 * y12 == 0) &&
    (x12 * x23 + y12 * y23 == 0) &&
    (x23 * x30 + y23 * y30 == 0) &&
    (x30 * x01 + y30 * y01 == 0);
}
