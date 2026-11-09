#pragma once
#include <string>

namespace landrop {

// Must be called once before any socket use (WSAStartup on Windows, no-op on Linux).
void netInit();

std::string hostName();
std::string platformName();

} // namespace landrop
