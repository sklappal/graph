#ifndef PARSER_H
#define PARSER_H

#include <vector>

namespace fasttrack { 

class graph;
class journey;

namespace parser
{
  graph parseGraph(const char* filename);

  std::vector<journey> parseJourneys(const char* filename);
}
}
#endif
