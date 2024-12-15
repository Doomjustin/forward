export module fwd.log:Level;


namespace fwd::log {

export
enum class Level {
    Off,
    Fatal,
    Error,
    Warning,
    Debug,
    Info,
    Trace
};

} // namespace fwd::log