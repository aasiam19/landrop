# Copilot instructions

## Build, test, and lint

Build with CMake and the C++17 compiler:

```sh
cmake -S . -B build
cmake --build build
```

Run the server with `./build/landrop`; it listens on TCP port `45455`. There is currently no configured test suite or lint target, so no single-test command is available.

## Architecture

`cli/main.cpp` is the executable entry point. It creates a TCP listener, accepts one client, and prints received bytes until the peer disconnects. Networking is implemented in the header-only `core/net.hpp` `landrop::Socket` wrapper, which uses POSIX sockets and owns the file descriptor through move-only RAII. Socket errors are surfaced as `std::runtime_error` and reported by `main`.

The CMake target adds `core` as a private include directory because the CLI includes `net.hpp` directly. Keep the executable entry point and reusable networking code separate when extending the project.

## Code conventions

- The project targets C++17 and uses the `landrop` namespace for networking code.
- `Socket` is non-copyable and movable; transfer ownership rather than duplicating descriptors.
- Socket operations report failures with exceptions; the CLI handles them at the application boundary and writes errors to standard error.
- This implementation depends on POSIX networking headers and APIs.
