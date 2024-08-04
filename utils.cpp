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

bool is_image_file(const filesystem::path& path) {
    return image_extensions.find(to_lowercase(path.extension().string())) != image_extensions.end();
}