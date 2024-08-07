#pragma once
#include <string>
#include <filesystem>

using namespace std;

string to_lowercase(const string& str);

bool is_image_file(const filesystem::path& path);

string to_lower(string s);
