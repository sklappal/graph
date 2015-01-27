#ifndef PRINTER_H
#define PRINTER_H

#include <sstream>

#include "printer.h"
#include "journey.h"

namespace fasttrack 
{ 
namespace printer 
{

namespace {
  std::string toJson(const journey& journey);
}

std::string toJson(const std::vector<journey>& journeys)
{
  std::stringstream ss;
  ss << "[" << std::endl;
  for(size_t i = 0; i < journeys.size(); i++)
  {
    ss << toJson(journeys[i]);
    if (i != journeys.size() - 1 )
    {
      ss << ",";
    }
    ss << std::endl;
  }
  ss << "]" << std::endl;
  return ss.str();
}

namespace {

std::string toJson(const journey& journey)
{
  std::stringstream ss;
  ss << "  { \"from\": ";
  ss << journey.from();
  ss << ", \"to\": ";
  ss << journey.to();
  if (journey.hasRoute())
  {
    ss << ", \"route\": [";
    auto route = journey.Route();
    for (size_t i = 0; i < route.size(); i++)
    {        
      ss << route[i];
      if (i != route.size() - 1)
      {
        ss << ", ";
      }
    }
    ss << "]";
  }
  ss << " }";
  return ss.str();
}

}
}
}

#endif
