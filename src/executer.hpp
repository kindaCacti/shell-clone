#pragma once

#include <memory>

#include "parse_nodes.hpp"

class Executer {
  public:
    int execute_parsed(std::shared_ptr<Parse_Nodes::Root>);
};

int Executer::execute_parsed(std::shared_ptr<Parse_Nodes::Root> root) {
    return 0;
}