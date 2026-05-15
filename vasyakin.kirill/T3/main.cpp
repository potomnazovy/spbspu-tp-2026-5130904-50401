#include <iostream>
#include <unordered_map>
#include <fstream>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Too much" << '\n';
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  std::vector< vasyakin::Polygon > poly;
  vasyakin::Polygon temp;

  while (file)
  {
    if (file >> temp)
    {
      poly.push_back(temp);
    }
    else
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

  using cmd_t = void(*)(std::istream&, std::ostream&, std::vector< vasyakin::Polygon >&);
  std::unordered_map< std::string, cmd_t > cmds;

  cmds["AREA"] = vasyakin::area;
  cmds["COUNT"] = vasyakin::count;
  cmds["MAX"] = vasyakin::max;
  cmds["MIN"] = vasyakin::min;
  cmds["RECTS"] = vasyakin::rects;
  cmds["PERMS"] = vasyakin::perms;

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout, poly);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
