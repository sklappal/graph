#include <cassert>
#include <vector>

#include "journey.h"

namespace fasttrack
{

journey::journey(const node_t& from, const node_t& to)
: m_from(from), m_to(to)
{

}

journey::journey(const std::vector<node_t>& route)
: m_from(route[0]), m_to(route[route.size()-1]), m_route(route)
{

}

node_t journey::from() const { return m_from; }

node_t journey::to() const { return m_to; }

bool journey::hasRoute() const { return m_route.size() > 0; }

void journey::setRoute(const std::vector<node_t>& route)
{
  assert(route[0] == m_from);
  assert(route[route.size()-1] == m_to);
  m_route = route;
}

std::vector<node_t> journey::Route() const
{
  return m_route;
}

}
