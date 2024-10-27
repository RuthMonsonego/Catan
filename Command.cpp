#include "Command.h"

Command::Command(CommandType _type) : commandType(_type) { }

CommandType Command::name_to_enum(const std::string& name) {
    if (name == "Select") return CommandType::SELECT;
    else if (name == "Move") return CommandType::MOVE;
    else if (name == "Work") return CommandType::WORK;
    else if (name == "Deposit") return CommandType::DEPOSIT;
    else if (name == "TakeResources") return CommandType::TAKE_RESOURCES;
    else if (name == "Build") return CommandType::BUILD;
    else if (name == "Manufacture") return CommandType::MANUFACTURE;
    else if (name == "People") return CommandType::PEOPLE;
    else if (name == "Resource") return CommandType::RESOURCE;
    else if (name == "Resources") return CommandType::RESOURCES;
    else if (name == "MakeEmpty") return CommandType::MAKE_EMPTY;
    else if (name == "Rain") return CommandType::RAIN;
    else if (name == "Robber") return CommandType::ROBBER;
    else if (name == "MakeRobber") return CommandType::MAKE_ROBBER;
    else if (name == "World") return CommandType::WORLD;
    else if (name == "Start") return CommandType::START;
    else if (name == "Input") return CommandType::INPUT;
    else if (name == "Asserts") return CommandType::ASSERTS;
    else if (name == "Wait") return CommandType::WAIT;
    else return CommandType::UNKNOWN;
}
