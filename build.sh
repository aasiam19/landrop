#!/usr/bin/env bash
set -euo pipefail

repo_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
build_dir="${BUILD_DIR:-$repo_dir/build}"

cmake -S "$repo_dir" -B "$build_dir"
cmake --build "$build_dir" --parallel
