#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

namespace fasttrack 
{

class edge;
class graph_edge;

typedef int node_t;

class graph
{
  public:

    graph(const std::vector<edge>& edges);

    std::string str() const;

    int nodecount() const;

    const std::vector<graph_edge>& neighbors(const node_t& node) const;

  private:
    
    void add(const edge& edge);

    std::vector< std::vector<graph_edge> > m_nodes;

};

class graph_edge
{
  public:
 
    graph_edge(node_t to, short weight);
  
    node_t to() const;

    short weight() const;

  private:

    node_t m_to;

    short m_weight;

};

class edge
{
  public:

    edge(node_t from, node_t to, int weight);

    node_t from() const;

    node_t to() const;

    int weight() const;

  private:
    
    node_t m_from;

    node_t m_to;

    int m_weight;
};
}
#endif
