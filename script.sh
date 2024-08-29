#!/bin/bash

# Define color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

executable_name='terminal-editor'

# Function to build the project
build_project() {
  # check build exists using mkdir -p command
  mkdir -p build
  if [ ! -d "build" ]; then
    echo -e "${RED}Error: Directory build does not exist or could not be created.${NC}"
    exit 1
  fi
  if ! cmake --build build; then
    echo -e "${BLUE}Attempting to clean the build directory.${NC}"

    # Try to clean the build directory
    if ! cmake --build build --target clean; then
      echo -e "${BLUE}Reconfiguring the project.${NC}"

      # Try to reconfigure the project
      if ! cmake -S . -B build; then
        echo -e "${RED}Error: could not reconfigure the project.${NC}"
        exit 1
      else
        echo -e "${BLUE}Rebuilding the project.${NC}"

        # Try to rebuild the project
        if ! cmake --build build; then
          echo -e "${RED}Error: could not rebuild the project.${NC}"
          exit 1
        fi
      fi
    fi
  fi
  echo -e "${GREEN}Successfully built the project.${NC}\n"
}

# Function to run the project
run_project() {
  # Run the executable
  if [ -f "build/$executable_name" ]; then
    echo -e "${YELLOW}\nRunning the executable${NC}"
    ./build/$executable_name
  else
    echo -e "${RED}Error: Executable build/$executable_name does not exist${NC}"
    read -p "Run Build [Y/n]: " run_build
    if [ "$run_build" == "Y" ] || [ "$run_build" == "y" ] || [ "$run_build" == "" ]; then
      build_project
      if [ -f "build/$executable_name" ]; then
        echo -e "${YELLOW}\nRunning the executable${NC}"
        ./build/$executable_name
      else
        echo -e "${RED}Error: Executable build/$executable_name does not exist${NC}"
        exit 1
      fi
    fi
  fi
}

# Parse command line arguments
run_after_build=false
build_before_run=false
command=""

for arg in "$@"; do
  case $arg in
    build)
      command="build"
      shift
      ;;
    run)
      command="run"
      shift
      ;;
    --run)
      run_after_build=true
      shift
      ;;
    --build)
      build_before_run=true
      shift
      ;;
    *)
      echo -e "${RED}Usage: $0 {build|run} [--run]${NC}"
      exit 1
      ;;
  esac
done

# Check command line argument
case "$command" in
  build)
    build_project
    if [ "$run_after_build" = true ]; then
      run_project
    fi
    ;;
  run)
    if [ "$build_before_run" = true ]; then
      build_project
    fi
    run_project
    ;;
  *)
    echo -e "${RED}Usage: $0 {build|run} [--run]${NC}"
    exit 1
    ;;
esac