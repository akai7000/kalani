#include <sstream>
#include <string>
#include "constants.h"
#include "utils.h"

std::string to_lowercase(const std::string& str) {
    std::stringstream ss(str);

    for (auto x : str) {
        ss << (char)tolower(x);
    }

    return ss.str();
}

std::string to_lower(std::string s) {
    for (char& c : s)
        c = tolower(c);
    return s;
}

bool is_image_file(const filesystem::path& path) {
    return image_extensions.find(to_lower(path.extension().string())) != image_extensions.end();
}