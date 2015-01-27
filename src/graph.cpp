#include <algorithm>
#include <cassert>
#include <limits>
#include <sstream>

#include "graph.h"

namespace fasttrack
{

graph::graph(const std::vector<edge>& edges)
{
  
  node_t max = std::numeric_limits<node_t>::min();

  for(auto& e : edges)
  {
    max = std::max(e.from(), max);
    max = std::max(e.to(), max);
  }
  
  m_nodes.resize(max + 1);

  for (auto& e : edges)
  {
    add(e);
  }
}

int graph::nodecount() const { return m_nodes.size(); }

const std::vector<graph_edge>& graph::neighbors(const node_t& node) const
{
  assert(node < nodecount());
  return m_nodes[node];
}

std::string graph::str() const
{
  std::stringstream ss;
  for (size_t i = 0; i < m_nodes.size(); i++)
  {
      auto& edges = m_nodes[i];
      for (auto& e : edges)
      {
        ss << "from: " << i << ", to: " << e.to() << ", weight: " << e.weight() << std::endl;
      }
  }

  return ss.str();
  
}

void graph::add(const edge& edge)
{
  assert(edge.from() < nodecount());
  assert(edge.to() < nodecount());
 
  m_nodes[edge.from()].push_back(graph_edge(edge.to(), edge.weight()));
}

graph_edge::graph_edge(node_t to, short weight)
: m_to(to), m_weight(weight)
{

}

node_t graph_edge::to() const { return m_to; }

short graph_edge::weight() const {return m_weight; }

edge::edge(node_t from, node_t to, int weight)
: m_from(from), m_to(to), m_weight(weight)
{

}

node_t edge::from() const { return m_from; }

node_t edge::to() const { return m_to; }

int edge::weight() const { return m_weight; }

}
