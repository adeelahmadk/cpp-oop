#!/bin/bash

# CWD=$(dirname `realpath $BASH_SOURCE`)
# echo "CWD: $CWD"
echo "From: $PWD"
CURR_DIRNAME="${PWD##*/}"
ENV=".env.sh"
while [[ ! -f "$ENV" ]]; do
  ENV="../$ENV"
done

[[ -z "$ENV" ]] && { echo "not in the repo dir!" >&2; exit 1; }

ENV=$(realpath $ENV)
source "$ENV"

# vars $PROJECT_ROOT, $BUILD_DIR and $CXX defined in env file
BUILD_STD11="$(realpath $BUILD_DIR)/std11"
if [[ ! -d "$BUILD_STD11" ]]; then
  mkdir -p "$BUILD_STD11" || { echo "error creating dir: {$BUILD_STD11}"; exit 1; }
fi
BUILD_OPTS="-std=c++11 -Wall"

echo "building to $CURR_DIRNAME"
# building example code
$CXX $BUILD_OPTS -o $BUILD_STD11/$CURR_DIRNAME main.cxx

[ "$?" -eq 0 ] && {
  printf "%s\n\n" "program built successfully, executing binary..."
  $BUILD_STD11/$CURR_DIRNAME
}
