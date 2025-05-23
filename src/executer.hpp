#pragma once

#include <memory>
#include <iostream>

#include "parse_nodes.hpp"
#include "commands.hpp"
#include "global_defines.hpp"

class Executer {
  public:
    int execute_parsed(std::shared_ptr<Parse_Nodes::Root>);
    int execute_builtin(std::shared_ptr<Parse_Nodes::Root>);
};

int Executer::execute_parsed(std::shared_ptr<Parse_Nodes::Root> root) {
    if(root < MIN_LOADED_COMMAND_ID){
        return execute_builtin(root);
    }
    return 0;
}

int execute_builtin(std::shared_ptr<Parse_Nodes::Root> root){
    switch(root->command_id){
        case CD_COMMAND:
            parse_cd_string(root->value)

    }
    std::cerr<<"No such command exists \r\n";
    return 1;
}