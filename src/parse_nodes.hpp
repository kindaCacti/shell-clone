#pragma once

#include <string>
#include <variant>
#include <vector>

#include "commands.hpp"

namespace Parse_Nodes {
struct Flag {
    std::string flag_type;
    std::string value;
};
struct Value {
    std::string value;
};
struct Root {
    int command_id;
    std::vector<std::variant<Flag, Value>> input;
};
}; // namespace Parse_Nodes