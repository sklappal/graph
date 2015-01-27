#include <cassert>
#include <fstream>
#include <limits>
#include <vector>
#include <iostream>

#include "parser.h"
#include "graph.h"
#include "journey.h"

namespace fasttrack 
{ 
namespace parser
{

namespace
{
  bool parseInt(const std::string& line, const std::string& tag, int& value);
  bool isNumeric(const char c);
  size_t findIntegerLength(const std::string& line, const size_t start);
  int integerSubstr(const std::string& line, const size_t start);
  bool parseList(const std::string& line, const std::string& tag, std::vector<node_t>& values);
}

using namespace fasttrack;

graph parseGraph(const char* filename)
{
  std::ifstream file(filename);
  if (!file.good())
  {
    std::cout << "Could not read file '" << filename << "'." << std::endl;
    throw std::exception();
  }

  std::vector<fasttrack::edge> edges;
  std::string line;
  int numlines = 0;
  while (std::getline(file, line))
  {
    numlines++;
    int from, to, weight;
    auto found = parseInt(line, "from", from);
    found = found && parseInt(line, "to", to);
    found = found && parseInt(line, "weight", weight);

    if (!found)
    {
      continue;
    }

    assert(weight < std::numeric_limits<short>::max());

    edges.push_back(edge((node_t) from, (node_t) to, (short) weight));
  }

  assert(numlines == edges.size() + 2);

  return graph(edges);
}

std::vector<journey> parseJourneys(const char* filename)
{
  std::ifstream file(filename);
  if (!file.good())
  {
    std::cout << "Could not read file '" << filename << "'." << std::endl;
    throw std::exception();
  }

  std::vector<journey> journeys;
  std::string line;
  int numlines = 0;
  while (std::getline(file, line))
  {
    numlines++;
    int from, to;
    auto found = parseInt(line, "from", from);
    found = found && parseInt(line, "to", to);
    if (!found)
    {
      continue;
    }

    std::vector<node_t> route;
    found = parseList(line, "route", route);

    if (found)
    {
      journeys.push_back(journey(route));
    }
    else
    {
      journeys.push_back(journey(from, to));
    }
  }

  assert(numlines == journeys.size() + 2);

  return journeys;
}

namespace
{

bool parseInt(const std::string& line, const std::string& tag, int& value)
{
  value = -1;
  auto start = line.find(tag);
  if (start == std::string::npos)
  {
    return false;
  }
  // json element is of the form "tag": <num>

  auto numStart = start + tag.size() + 3;
  value = integerSubstr(line, numStart); 
  return true;
}

size_t findIntegerLength(const std::string& line, const size_t start)
{
  auto cur = line[start];
  assert(isNumeric(cur));
  size_t len = 0;
  while (isNumeric(cur))
  {
    len++;
    cur = line[start + len];
  }
  return len;
}

bool isNumeric(const char c)
{
  return c >= '0' && c <= '9';
}

int integerSubstr(const std::string& line, const size_t start)
{
  auto len = findIntegerLength(line, start);
  return std::stoi(line.substr(start, len));
}

bool parseList(const std::string& line, const std::string& tag, std::vector<node_t>& list)
{
  list.clear();
  auto start = line.find(tag);
  if (start == std::string::npos)
  {
    return false;
  }

  auto listStart = line.find("[", start);
  auto listEnd = line.find("]", listStart);
  assert(listStart != std::string::npos);
  auto numStart = listStart + 1;
  
  while(numStart < listEnd)
  { 
    list.push_back((node_t) integerSubstr(line, numStart));
    auto len = findIntegerLength(line, numStart);
    numStart = numStart + len + 2;
  }

  return true;  
}
}
}
}
