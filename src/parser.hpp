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

    void add_to_root(std::shared_ptr<Parse_Nodes::Root>, std::string &value);
};

Parser::Parser() {
    for (std::string &command : commands) {
        command_manager.add_command(command);
    }
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
        if ((int)c == '"')
            inside_quotes ^= 1;
        if (c == ' ' and !inside_quotes) {
            add_to_root(root, buffer);
            buffer.clear();
        }
        buffer.push_back(c);
    }

    return root;
}

void Parser::add_to_root(std::shared_ptr<Parse_Nodes::Root> root,
                         std::string &value) {
    if (value.size() == 0) {
        return;
    }

    if (root->command_id == -1) {
        int id = command_manager.get_id_for(value);
        if (id < 0) {
            std::cerr << "No such command exists\r\n" << std::endl;
            exit(EXIT_FAILURE);
        }

        root->command_id = id;
    } else {
        if (value[0] == '-') {
            root->input.push_back(Parse_Nodes::Flag{.flag_type = value});
        } else {
            root->input.push_back(Parse_Nodes::Value{.value = value});
        }
    }
}