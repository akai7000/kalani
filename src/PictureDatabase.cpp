#include "PictureDatabase.h"
#include <iostream>

PictureDatabase::PictureDatabase(const std::filesystem::path& dbPath)
    : m_dbPath(dbPath), m_dirty(false)
{
    load();
}

PictureDatabase::~PictureDatabase()
{
    if (m_dirty)
    {
        save();
    }
}

uint64_t PictureDatabase::hashPath(const std::filesystem::path& path) const
{
    std::string normalized = path.lexically_normal().string();
    std::hash<std::string> hasher;
    return hasher(normalized);
}

void PictureDatabase::setRating(const std::filesystem::path& imagePath, int rating)
{
    uint64_t hash = hashPath(imagePath);
    m_ratings[hash] = static_cast<int32_t>(rating);
    m_dirty = true;
}

std::optional<int> PictureDatabase::getRating(const std::filesystem::path& imagePath) const
{
    uint64_t hash = hashPath(imagePath);
    auto it = m_ratings.find(hash);
    if (it != m_ratings.end())
    {
        return it->second;
    }
    return std::nullopt;
}

void PictureDatabase::save()
{
    try
    {
        std::ofstream ofs(m_dbPath, std::ios::binary | std::ios::trunc);
        if (!ofs)
        {
            std::cerr << "Failed to open database for writing: " << m_dbPath << "\n";
            return;
        }

        uint32_t count = static_cast<uint32_t>(m_ratings.size());
        ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));

        for (const auto& [hash, rating] : m_ratings)
        {
            Entry entry{ hash, rating };
            ofs.write(reinterpret_cast<const char*>(&entry), sizeof(entry));
        }

        m_dirty = false;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error saving database: " << e.what() << "\n";
    }
}

void PictureDatabase::load()
{
    if (!std::filesystem::exists(m_dbPath))
    {
        return;
    }

    try
    {
        std::ifstream ifs(m_dbPath, std::ios::binary);
        if (!ifs)
        {
            std::cerr << "Failed to open database for reading: " << m_dbPath << "\n";
            return;
        }

        uint32_t count = 0;
        ifs.read(reinterpret_cast<char*>(&count), sizeof(count));

        m_ratings.clear();
        m_ratings.reserve(count);

        for (uint32_t i = 0; i < count; ++i)
        {
            Entry entry;
            ifs.read(reinterpret_cast<char*>(&entry), sizeof(entry));
            m_ratings[entry.pathHash] = entry.rating;
        }

        m_dirty = false;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error loading database: " << e.what() << "\n";
    }
}