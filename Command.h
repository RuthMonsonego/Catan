#pragma once

#include <iostream>
#include <vector>
#include "CommandType.h"

class Command {
public:
    CommandType commandType;

    Command(CommandType _type);

    std::vector<std::string> arguments;
    std::vector<std::vector<std::string>> data;

    static CommandType name_to_enum(const std::string& name);
};
