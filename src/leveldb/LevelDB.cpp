#include "LevelDB.h"


namespace fwd::leveldb {

LevelDB::LevelDB(std::filesystem::path dir)
  : dir_{ std::move(dir) }
{
    using namespace std::filesystem;
    Ensures(!exists(dir_) || is_directory(dir_));
}

[[nodiscard]]
std::optional<std::string> LevelDB::get(const std::string_view key) const
{
    return name();
}

void LevelDB::write(const WriteBatch& batch)
{
    auto last_task = push(batch);
    auto ready_to_write = [this, &last_task] ()
                { return last_task->done || last_task == tasks_.begin(); };

    std::unique_lock<std::mutex> locker{ m_ };
    cv_.wait(locker, ready_to_write);

    if (last_task->done) return;


    Task compacted_task{};
    Iterator end_task;
    for (const auto& task: tasks_) {
        compacted_task.batch += task.batch;
        if (compacted_task.batch.size() >= 12345)
            break;
    }
}

} // namespace fwd::leveldb