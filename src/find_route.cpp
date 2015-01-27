#include <iostream>
#include "djikstra.h"
#include "journey.h"
#include "parser.h"
#include "printer.h"

using namespace fasttrack;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "Please provide the graph and journey files as input." << std::endl;
    throw std::exception();
  }

  auto graph = parser::parseGraph(argv[1]);
  auto journeys = parser::parseJourneys(argv[2]);

  for (auto& journey : journeys)
  { 
    if (!journey.hasRoute())
    {
      auto path = djikstra::findRoute(graph, journey.from(), journey.to());
      journey.setRoute(path);
    }
  }

  std::cout << printer::toJson(journeys);

  return 0;
}
