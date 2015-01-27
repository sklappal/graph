#include <algorithm>
#include <cassert>
#include <limits>
#include <list>

#include "graph.h"
#include "djikstra.h"

namespace fasttrack { namespace djikstra
{

namespace
{
  node_t pop_min(std::list<node_t>& workingset, const std::vector<short>& values)
  {
    assert(values.size() > 0);
    auto min = std::numeric_limits<short>::max();
    auto min_index = workingset.end();
    for (auto it = workingset.begin(); it != workingset.end(); ++it)
    {
      auto node = *it;
      if (values[node] < min)
      {
        min = values[node];
        min_index = it;
      }
    }
    auto val = *min_index;
    workingset.erase(min_index);
    return val;
  }
}
  std::vector<node_t> findRoute(const graph& graph, const node_t& from, const node_t& to)
  {
    std::vector<short> distances(graph.nodecount());
    std::vector<node_t> predecessors(graph.nodecount());

    distances[from] = 0;
    predecessors[from] = -1;

    std::list<node_t> workingset;

    for (node_t node = 0; node < graph.nodecount(); node++)
    {
      if (node != from)
      {
        distances[node] = std::numeric_limits<short>::max();
        predecessors[node] = -1;
      }
      workingset.push_back(node);
    }
  
    while (workingset.size() > 0)
    {
      auto u = pop_min(workingset, distances);
      for (auto& neighbor : graph.neighbors(u))
      {
        auto dist = distances[u] + neighbor.weight();
        if (dist < distances[neighbor.to()])
        {
          distances[neighbor.to()] = dist;
          predecessors[neighbor.to()] = u;
        }
      }
      if (u == to)
      {
        break;
      }
    }

    std::vector<node_t> ret;
    auto cur = to;
    while (cur != from)
    {
      ret.push_back(cur);
      cur = predecessors[cur];
      assert(cur != -1);
    }
    ret.push_back(from);
    std::reverse(ret.begin(), ret.end());
    return ret;
  }
}
}
