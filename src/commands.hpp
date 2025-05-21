#pragma once
#include "parser_sup.hpp"
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> commands = {"cd"};

class Command_Manager {
  public:
    Command_Manager();
    int get_id_for(std::string &);
    void add_command(std::string &);

  private:
    int last_id;
    std::unordered_map<std::string, int> rev;
};

Command_Manager::Command_Manager() {
    last_id = 0;
    rev.clear();
}

void Command_Manager::add_command(std::string &command_name) {
    rev[command_name] = last_id;
    last_id++;
}

int Command_Manager::get_id_for(std::string &value) {
    auto it = rev.find(value);
    if (it == rev.end())
        return -1;
    return it->second;
}
