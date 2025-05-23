#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "commands.hpp"
#include "parse_nodes.hpp"
#include "parser_sup.hpp"

class Parser {
  public:
    Parser();
    std::shared_ptr<Parse_Nodes::Root> parse_string(std::string);

  private:
    Command_Manager command_manager;

    bool add_to_root(std::shared_ptr<Parse_Nodes::Root>, std::string &value);
};

Parser::Parser() {
    command_manager = Command_Manager();
    command_manager.load_commands();
}

std::shared_ptr<Parse_Nodes::Root> Parser::parse_string(std::string input) {
    std::string buffer;
    std::shared_ptr<Parse_Nodes::Root> root =
        std::shared_ptr<Parse_Nodes::Root>(new Parse_Nodes::Root);
    root->command_id = -1;

    bool inside_quotes = false; // quote is 34 in dec
    bool is_command = true;
    input.push_back(' ');
    for (auto c : input) {
        if ((int)c == '"'){
            inside_quotes ^= 1;
            continue;
        }
        if (c == ' ' and !inside_quotes) {
            if (add_to_root(root, buffer)) {
                return nullptr;
            }
            buffer.clear();
        }
        buffer.push_back(c);
    }

    return root;
}

bool Parser::add_to_root(std::shared_ptr<Parse_Nodes::Root> root,
                         std::string &value) {
    if (value.size() == 0) {
        return false;
    }

    if (root->command_id == -1) {
        int id = command_manager.get_id_for(value);
        if (id < 0) {
            std::cerr << "No such command exists\r\n" << std::endl;
            return 1;
        }

        root->command_id = id;
    } else {
        if (value[0] == '-') {
            root->input.push_back(Parse_Nodes::Flag{.flag_type = value});
        } else {
            root->input.push_back(Parse_Nodes::Value{.value = value});
        }
    }
    return 0;
}