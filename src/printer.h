#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>

namespace fasttrack { 

class journey;

namespace printer {

  std::string toJson(const std::vector<journey>& journey);

}
}

#endif
