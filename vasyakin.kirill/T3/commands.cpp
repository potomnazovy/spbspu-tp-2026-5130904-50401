#include "commands.hpp"
#include <string>
#include <stdexcept>

void vasyakin::area(std::istream& in, std::ostream& out, std::vector< Polygon >& poly)
{
  std::string str;
  if (!(in >> str))
  {
    throw std::runtime_error("Missing str");
  }

  std::vector< Polygon > yapoly;

  if (str == "MEAN")
  {
    if (poly.empty())
    {
      throw std::runtime_error("No polygons for mean");
    }

    std::vector< double > areas(poly.size());
    std::transform(poly.begin(), poly.end(), areas.begin(), getArea);
    double total = std::accumulate(areas.begin(), areas.end(), 0.0);

    out << std::fixed << std::setprecision(1) << total / poly.size() << '\n';
  }
  else
  {
    if (str == "EVEN")
    {
      std::copy_if(poly.begin(), poly.end(), std::back_inserter(yapoly), has_even_vertices);
    }
    else if (str == "ODD")
    {
      std::copy_if(poly.begin(), poly.end(), std::back_inserter(yapoly), has_odd_vertices);
    }
    else
    {
      size_t n = std::stoul(str);
      auto pred = std::bind(has_n_vertices, std::placeholders::_1, n);
      std::copy_if(poly.begin(), poly.end(), std::back_inserter(yapoly), pred);
    }
  }

  std::vector< double > areas(yapoly.size());
  std::transform(yapoly.begin(), yapoly.end(), areas.begin(), getArea);
  double total = std::accumulate(areas.begin(), areas.end(), 0.0);

  out << std::fixed << std::setprecision(1) << total << '\n';
}

void count(std::istream& in, std::ostream& out, std::vector< vasyakin::Polygon >& poly)
{
  std::string str;
  if (!(in >> str))
  {
    throw std::runtime_error("Missing str");
  }

  size_t result = 0;

  if (str == "EVEN")
  {
    result = std::count_if(poly.begin(), poly.end(), vasyakin::has_even_vertices);
  }
  else if (str == "ODD")
  {
    result = std::count_if(poly.begin(), poly.end(), vasyakin::has_odd_vertices);
  }
  else
  {
    auto n = std::stoul(str);
    auto pred = std::bind(vasyakin::has_n_vertices, std::placeholders::_1, n);
    result = std::count_if(poly.begin(), poly.end(), pred);
  }

  out << result << '\n';
}

void max(std::istream& in, std::ostream& out, std::vector< vasyakin::Polygon >& poly)
{
  std::string str;
  if (!(in >> str))
  {
    throw std::runtime_error("Missing str");
  }

  if (poly.empty())
  {
    throw std::runtime_error("No polygons for MAX");
  }

  if (str == "AREA")
  {
    auto it = std::max_element(poly.begin(), poly.end(), vasyakin::area_less);
    out << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
  }
  else if (str == "VERTEXES")
  {
    auto it = std::max_element(poly.begin(), poly.end(), vasyakin::vertices_less);
    out << it->points.size() << '\n';
  }

  throw std::invalid_argument("No command available");
}

void min(std::istream& in, std::ostream& out, std::vector< vasyakin::Polygon >& poly)
{
  std::string str;
  if (!(in >> str))
  {
    throw std::runtime_error("Missing str");
  }

  if (poly.empty())
  {
    throw std::runtime_error("No polygons for MIN");
  }

  if (str == "AREA")
  {
    auto it = std::min_element(poly.begin(), poly.end(), vasyakin::area_less);
    out << std::fixed << std::setprecision(1) << getArea(*it) << '\n';
  }
  else if (str == "VERTEXES")
  {
    auto it = std::min_element(poly.begin(), poly.end(), vasyakin::vertices_less);
    out << it->points.size() << '\n';
  }

  throw std::invalid_argument("No command available");
}

void rects(std::istream& in, std::ostream& out, std::vector< vasyakin::Polygon >& poly)
{
  auto result = std::count_if(poly.begin(), poly.end(), vasyakin::is_rect);
  out << result << '\n';
}

void perms(std::istream& in, std::ostream& out, std::vector< vasyakin::Polygon >& poly)
{
  vasyakin::Polygon ref;
  if (!(in >> ref))
  {
    throw std::invalid_argument("Invalid polygon format");
  }

  auto pred = std::bind(vasyakin::is_permutation_of, std::placeholders::_1, std::cref(ref));
  auto result = std::count_if(poly.begin(), poly.end(), pred);
  out << result << '\n';
}
