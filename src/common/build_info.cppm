module;

#include <filesystem>
#include <string>

export module fwd.build_info;


namespace fwd {

export const std::string ProjectVersion = "0.0.1";
export const std::filesystem::path ProjectDirectory = "E:/workspace/forward";

export constexpr int OpenGLCoreVersionMajor = 3;
export constexpr int OpenGLCoreVersionMinor = 3;

} // namespace fwd
