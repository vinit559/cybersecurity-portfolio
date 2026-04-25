# ticketing-system — small C++ example

This repository contains a tiny C++ program `complexsunnumber.cpp` that demonstrates a `Complex` class and operator overloading.

Quick build & run (macOS / Linux):

```bash
# from the repository root
g++ complexsunnumber.cpp -o complexsunnumber
./complexsunnumber
# expected output:
# 12 + 9i
```

You can also use `clang++`:

```bash
clang++ complexsunnumber.cpp -o complexsunnumber
./complexsunnumber
```

VS Code
-------
- Press Cmd+Shift+B (or Run Build Task) to pick a C/C++ build task.
- The workspace task file `.vscode/tasks.json` was adjusted to remove a stray empty argument which could cause a malformed build command and lead to linker errors like `Undefined symbols for architecture arm64: "_main"`.

If you see that error while using tasks, check `.vscode/tasks.json` and ensure `args` does not contain an empty string at the end of the array.

Notes
-----
- The example is intentionally small. I added the following additional files to the repo:
  - `include/Complex.h` — header with `Complex` and operators (+, -, *, <<).
  - `test_complex.cpp` — a small test harness using `assert` and printing results.
  - `Makefile` — build and run targets (`make`, `make test`).
  - `CMakeLists.txt` — simple CMake configuration for out-of-source builds.
  - A configurable VS Code build task that prompts for compiler selection.

Tell me if you want any of these adjusted (e.g., add GoogleTest, change C++ standard, or prefer clang as default).
 
Quick usage
-----------

Make (default g++):

```bash
make
./complexsunnumber

# run tests
make test
```

CMake (out-of-source):

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./complexsunnumber
```

GoogleTest
----------

The project uses CMake's FetchContent to download GoogleTest when configuring with CMake. To build and run the GoogleTest test suite:

```bash
mkdir -p build && cd build
cmake ..
cmake --build . --target test_complex_gtest
./test_complex_gtest
```

Badges
------

You can add a workflow status badge to this README. Example (replace `OWNER/REPO` with your repository):

```markdown
[![CI](https://github.com/OWNER/REPO/actions/workflows/ci.yml/badge.svg)](https://github.com/OWNER/REPO/actions/workflows/ci.yml)
```

Pre-commit tests
----------------

There's a `scripts/pre-commit.sh` that runs the GoogleTest suite via CMake. To enable it locally, copy the sample hook into your repo's `.git/hooks` and make it executable:

```bash
cp .git/hooks/pre-commit.sample .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

The hook requires CMake to be installed locally. CI (GitHub Actions) will install CMake and run the tests automatically.
CI
--

A GitHub Actions workflow is included at `.github/workflows/ci.yml`. It configures CMake, builds, and runs the tests on push and pull requests.

Vendoring GoogleTest (optional)
-------------------------------

If you want to avoid network downloads during CMake configure, vendor GoogleTest into the repository. We provide a helper script that downloads and places GoogleTest under `third_party/googletest`.

From the repo root:

```bash
./scripts/vendor_gtest.sh release-1.14.0
# then add and commit the vendored files:
git add third_party/googletest
git commit -m "Vendor googletest"
```

After vendoring, CMake will detect the local copy and use it during configure; no network access will be required.

Vendoring & automatic attempt from Makefile
-----------------------------------------

If you run `make test` and CMake is not installed, the Makefile will attempt to run `./scripts/vendor_gtest.sh` to vendor GoogleTest, but CMake is still required to build tests. To vendor without CMake, run:

```bash
./scripts/vendor_gtest.sh release-1.14.0
git add third_party/googletest
git commit -m "Vendor googletest"
``` 
// one of the best cmkae file and directory and that make a file and save it to one of the another one and some of the other file and enter into  same file cmake file named filed and compile the file into that file and said to the best one  and also make //

Docker-based testing
--------------------

If you don't want to install CMake locally, you can use the provided Dockerfile. Build and run tests in Docker with:

```bash
./scripts/docker_test.sh
```

This builds an Ubuntu-based image containing CMake and runs the GoogleTest suite inside the container.

What changed in this branch
--------------------------

- Vendored GoogleTest (branch-only) under `third_party/googletest` so CI and offline builds can use a local copy.
- Added a robust `make test` fallback: if CMake is missing the Makefile will attempt to vendor gtest, and if CMake is still unavailable it will compile and run a small builtin test runner so developers can run tests without CMake.

Creating the PR
---------------

Use this one-click link to open the prepared PR for this branch (review the description and `PR_BODY.md` before creating):

https://github.com/vinit559/cybersecurity-portfolio/pull/new/vendor/googletest
