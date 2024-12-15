module;

#include <filesystem>
#include <string>

export module fwd.leveldb:LevelDB;

import :WriteBatch;


namespace fwd::leveldb {

class LevelDB {
public:
    explicit LevelDB(std::filesystem::path dir)
      : dir_{ std::move(dir) }
    {}

    [[nodiscard]]
    std::optional<std::string> get(const std::string_view key) const
    {
        return {};
    }

    void put(const std::string_view key, const std::string_view value)
    {
        WriteBatch batch{};
        batch.put(key, value);
        write(batch);
    }

    void remove(const std::string_view key)
    {
        WriteBatch batch{};
        batch.remove(key);
        write(batch);
    }

    void write(const WriteBatch& batch)
    {
        // TODO:
    }

    [[nodiscard]]
    std::string name() const noexcept
    {
        return dir_.stem().string();
    }

private:
    std::filesystem::path dir_;
};

} // namespace fwd::leveldb