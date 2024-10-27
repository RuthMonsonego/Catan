#include "Input.h"
#include "Utility.h"
#include "World.h"
#include "CommandType.h"
#include <iostream>
#include <memory>
using namespace std;

string Input::next_line()
{
    string line = "";
    getline(cin, line);
    return line;
}

Input::Input() {
    world.reset(new Command(CommandType::WORLD));
}

vector<vector<string>> Input::parse_and_store() {
    auto line = next_line();
    vector<shared_ptr<Command>>* command_list = &start;
    bool parsing_world = false;
    bool asserts_reached = false;
    vector<vector<string>> world_data;

    while (!line.empty()) {
        strip(line);
        if (line.rfind("+", 0) == 0) {
            string name = line.substr(1);
            parsing_world = false;
            Command* cc;
            CommandType c = cc->name_to_enum(name);
            if (c == CommandType::WORLD) {
                parsing_world = true;
            }
            else if (c == CommandType::START) {
                command_list = &start;
            }
            else if (c == CommandType::INPUT) {
                command_list = &steps;
            }
            else if (c == CommandType::ASSERTS) {
                asserts_reached = true;
            }
            else {
                throw runtime_error("Unknown Input Command found: " + name);
            }
        }
        else {
            if (asserts_reached) {
                asserts.push_back(line);
            }
            else if (parsing_world) {
                vector<string> row = split(line);
                world_data.push_back(row);
            }
            else {
                auto command = parse_command(line);
                command_list->push_back(command);
            }
        }
        line = next_line();
    }
    return world_data;
}

shared_ptr<Command> Input::parse_command(string line)
{
    auto strings = split(line);
    CommandType c = Command::name_to_enum(strings[0]);
    shared_ptr<Command> command(new Command(c));
    command.get()->arguments.insert(
        command.get()->arguments.end(), strings.begin() + 1, strings.end()
    );
    return command;
}