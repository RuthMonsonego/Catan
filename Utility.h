#pragma once

#include <string>
#include <vector>
#include <fstream>

extern const char* whitespace_chars;

void strip(std::string& s);
std::vector<std::string> split(std::string s);
void read_lines(const std::string& file, std::vector<std::string>& lines);
