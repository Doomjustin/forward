#ifndef FORWARD_NONCOPYABLE_H
#define FORWARD_NONCOPYABLE_H

namespace fwd {

class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&&) noexcept = default;
    NonCopyable& operator=(NonCopyable&&) noexcept = default;

    ~NonCopyable() = default;

protected:
    NonCopyable() = default;
};

} // namespace fwd

#endif // FORWARD_NONCOPYABLE_H