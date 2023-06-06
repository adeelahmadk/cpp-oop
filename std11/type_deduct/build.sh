#!/bin/bash

CWD=$(dirname `realpath $BASH_SOURCE`)
echo "CWD: $CWD"
ENV=".env.sh"
while [[ ! -f "$ENV" ]]; do
  ENV="../$ENV"
done

[[ -z "$ENV" ]] && { echo "not in the repo dir!" >&2; exit 1; }
echo "env file: $(realpath $ENV)"
echo "env path: $(dirname `realpath $ENV`)"
source "$ENV"
echo "project root: $PROJECT_ROOT"
BUILD_DIR="$PROJECT_ROOT/build/cpp11"
# while [[ ! -d "$BUILD_DIR" ]]; do
#   BUILD_DIR="../$BUILD_DIR"
# done

BUILD_CPP11="$(realpath $BUILD_DIR)"
echo "CPP11 build: $BUILD_CPP11"
echo "CPP compiler: $CXX"
