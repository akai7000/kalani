#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <fstream>
#include <optional>

class PictureDatabase
{
public:
    explicit PictureDatabase(const std::filesystem::path& dbPath = "pictures.db");
    ~PictureDatabase();

    void setRating(const std::filesystem::path& imagePath, int rating);
    std::optional<int> getRating(const std::filesystem::path& imagePath) const;
    void save();
    void load();

private:
    struct Entry
    {
        uint64_t pathHash;
        int32_t rating;
    };

    std::filesystem::path m_dbPath;
    std::unordered_map<uint64_t, int32_t> m_ratings;
    bool m_dirty;

    uint64_t hashPath(const std::filesystem::path& path) const;
};