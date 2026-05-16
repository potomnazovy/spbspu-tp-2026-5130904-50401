#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <numeric>
#include <functional>

namespace vasyakin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct DelimeterIO
  {
    char exp;
  };

  struct Triangle
  {
    Point a, b, c;
  };

  struct GuardIO
  {
    explicit GuardIO(std::basic_ios< char >& s);
    ~GuardIO();
  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios< char >::fmtflags flags_;
    char fill_;
  };

  Triangle make_triangle(const std::vector< Point >& pts, size_t i);
  double triangleArea(Triangle tr);
  double getArea(const Polygon& poly);

  bool has_even_vertices(const vasyakin::Polygon& p);
  bool has_odd_vertices(const vasyakin::Polygon& p);
  bool has_n_vertices(const vasyakin::Polygon& p, size_t n);

  bool area_less(const vasyakin::Polygon& lhs, const vasyakin::Polygon& rhs);
  bool vertices_less(const vasyakin::Polygon& lhs, const vasyakin::Polygon& rhs);

  bool operator==(const vasyakin::Point& a, const vasyakin::Point& b);
  bool is_permutation_of(const vasyakin::Polygon& candidate,
    const vasyakin::Polygon& reference);

  bool is_rect(const vasyakin::Polygon& candidate);
  void readPointsRecursive(std::istream& is,
    std::vector< vasyakin::Point >& points, size_t remaining);

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif
