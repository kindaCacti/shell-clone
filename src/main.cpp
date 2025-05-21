#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include "executer.hpp"
#include "global_defines.hpp"
#include "parse_nodes.hpp"
#include "parser.hpp"

void print_query() {
    std::cout << std::filesystem::current_path().generic_string() << "$ ";
}

std::string read_query() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

int main(int argc, char *argv[]) {
    Parser parser = Parser();
    Executer executer = Executer();

    std::cout << WELCOME_MESSAGE << std::endl;

    while (true) {
        print_query();
        std::string value = read_query();
        std::shared_ptr<Parse_Nodes::Root> root = parser.parse_string(value);

        if (root == nullptr) {
            continue;
        }

        int return_value = executer.execute_parsed(root);

        if (return_value != 0) {
            std::cout << "error code: " << return_value << std::endl;
        }
    }
    return 0;
}