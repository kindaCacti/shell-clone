#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <unistd.h> 
#include <stdio.h> 

#include "parser_sup.hpp"
#include "global_defines.hpp"

std::vector<std::string> commands = {"cd"};

class Command_Manager {
  public:
    Command_Manager();
    int get_id_for(std::string &);
    void add_command(std::string &);
    void load_commands();

  private:
    int last_id;
    std::unordered_map<std::string, int> rev;
};

Command_Manager::Command_Manager() {
    last_id = MIN_LOADED_COMMAND_ID;
    rev.clear();
}

void Command_Manager::add_command(std::string &command_name) {
    rev[command_name] = last_id;
    last_id++;
}

void Command_Manager::load_commands() {
    last_id = MIN_LOADED_COMMAND_ID;
    for(std::string& command : commands){
        rev[command] = it;
        last_id++;
    }
}

int Command_Manager::get_id_for(std::string &value) {
    auto it = rev.find(value);
    if (it == rev.end())
        return -1;
    return it->second;
}

int change_directory(std::string where_to){
    if(where_to.size() == 0) return 0;
    if(where_to.size() == 1 and where_to.back() == '.') return 0;
    if(where_to.size() == 2 and where_to == ".."){
        std::filesystem::current_path(std::filesystem::current_path().parent_path());
        return 0;
    }

    return 1;
}

int parse_cd_string(std::string cd_string){
    auto original_path = std::filesystem::current_path();
    std::string buffer = "";

    if(cd_string.size() == 0) return 1;

    if(cd_string.back() != '/') cd_string.push_back('/');

    for(char c : cd_string){
        if(c == '/'){
            int ret_val = change_directory(buffer);

            if(ret_val){
                std::filesystem::current_path(original_path);
                return 1;
            }

            buffer.clear();
            continue;
        }

        buffer.push_back(c);
    }

    return 0;
}