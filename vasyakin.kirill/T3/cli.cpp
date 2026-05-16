#include <map>
#include <limits>
#include "commands.hpp"
#include "cli.hpp"

void readData(std::istream& in, std::vector< vasyakin::Polygon >& all_polygons)
{
  if (in.eof())
  {
    return;
  }
  
  vasyakin::Polygon p;
  if (in >> p)
  {
    all_polygons.push_back(p);
    vasyakin::readData(in, all_polygons);
    return;
  }
  
  if (in.eof())
  {
    return;
  }

  in.clear();
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  vasyakin::readData(in, all_polygons);
}

std::vector< vasyakin::Polygon >* vasyakin::command::all_polygons = nullptr;

std::istream& operator>>(std::istream& in, vasyakin::command&)
{
  std::string name_command;
  in >> name_command;
  if (!in)
  {
    return in;
  }

  static std::map< std::string, void (*)(std::istream&, std::ostream&,
    std::vector< vasyakin::Polygon >&) > commands;

  commands["AREA"] = vasyakin::area;
  commands["MAX"] = vasyakin::max;
  commands["MIN"] = vasyakin::min;
  commands["COUNT"] = vasyakin::count;
  commands["PERMS"] = vasyakin::perms;
  commands["RECTS"] = vasyakin::rects;
  try
  {
    commands.at(name_command)(in, std::cout, *vasyakin::command::all_polygons);
  }
  catch (...)
  {
    std::cout << "<INVALID COMMAND>" << '\n';
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return in;
}
