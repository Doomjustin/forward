export module fwd.log:LogLevel;


namespace fwd {

export
enum class LogLevel {
    Off,
    Fatal,
    Error,
    Warning,
    Debug,
    Info,
    Trace
};

} // namespace fwd