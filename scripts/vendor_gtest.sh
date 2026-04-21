#!/usr/bin/env bash
# Download and extract GoogleTest into third_party/googletest
# Usage: ./scripts/vendor_gtest.sh [version]
# Example: ./scripts/vendor_gtest.sh release-1.14.0


#!/usr/bin/env bash
# Download and extract GoogleTest into third_party/googletest
# Usage: ./scripts/vendor_gtest.sh [version]
# Example: ./scripts/vendor_gtest.sh release-1.14.0

set -euo pipefail

usage() {
  cat <<EOF
Usage: $0 [version]
Download and vendor GoogleTest under third_party/googletest.
version: Git tag name (default: release-1.14.0)
Examples:
  $0 release-1.14.0
EOF
}

if [[ ${1:-} == "-h" || ${1:-} == "--help" ]]; then
  usage
  exit 0
fi

VERSION=${1:-release-1.14.0}
GTEST_DIR="$(pwd)/third_party/googletest"
ZIP_NAME="googletest-${VERSION}.zip"
URL="https://github.com/google/googletest/archive/refs/tags/${VERSION}.zip"

echo "Vendoring GoogleTest ${VERSION} into ${GTEST_DIR}"

mkdir -p third_party

tmpdir=$(mktemp -d)
cd "$tmpdir"

downloaded=false
if command -v curl >/dev/null 2>&1; then
  echo "Downloading ${URL} with curl..."
  curl -L -f -s -o "$ZIP_NAME" "$URL" && downloaded=true || downloaded=false
fi

if ! $downloaded && command -v wget >/dev/null 2>&1; then
  echo "Downloading ${URL} with wget..."
  wget -q -O "$ZIP_NAME" "$URL" && downloaded=true || downloaded=false
fi

if ! $downloaded; then
  echo "Error: failed to download ${URL}. Please ensure network access or download manually."
  exit 1
fi

extracted=false
if command -v unzip >/dev/null 2>&1; then
  unzip -q "$ZIP_NAME" && extracted=true || extracted=false
fi

if ! $extracted; then
  # try python unzip fallback
  if command -v python3 >/dev/null 2>&1; then
    python3 - <<PY
import sys, zipfile
zf=zipfile.ZipFile(sys.argv[1])
zf.extractall()
PY "$ZIP_NAME" && extracted=true || extracted=false
  fi
fi

if ! $extracted; then
  echo "Error: failed to extract $ZIP_NAME. Please install 'unzip' or ensure Python3 is available.";
  cd - >/dev/null
  rm -rf "$tmpdir"
  exit 1
fi

# find the first directory created by extraction
extracted_dir=""
for d in */; do
  if [[ -d "$d" ]]; then
    extracted_dir=${d%/}
    break
  fi
done

if [[ -z "$extracted_dir" ]]; then
  echo "Error: couldn't find extracted folder.";
  cd - >/dev/null
  rm -rf "$tmpdir"
  exit 1
fi

# Move to third_party/googletest
rm -rf "$GTEST_DIR"
mkdir -p "${GTEST_DIR}"
mv "$extracted_dir"/* "${GTEST_DIR}"

# Clean up
cd - >/dev/null
rm -rf "$tmpdir"

echo "GoogleTest vendored into ${GTEST_DIR}."

echo "Remember to add and commit 'third_party/googletest' to your repository to avoid network downloads during CMake configure."

exit 0
