#ifndef JOURNEY_H
#define JOURNEY_H

#include "graph.h"

namespace fasttrack
{

class journey
{

  public:

    journey(const node_t& from, const node_t& to);

    journey(const std::vector<node_t>& journey);

    node_t from() const;

    node_t to() const;

    bool hasRoute() const;

    void setRoute(const std::vector<node_t>& route);

    std::vector<node_t> Route() const;

  private:

    node_t m_from;

    node_t m_to;

    std::vector<node_t> m_route;
};

}
#endif
