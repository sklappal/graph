#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include "graph.h"

namespace fasttrack { namespace djikstra
{

  std::vector<node_t> findRoute(const graph& graph, const node_t& from, const node_t& to);
}}
#endif
