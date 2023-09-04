#!/bin/bash

# Print a tree of the current directory, excluding some directories
tree -I '.PVS-Studio|.vscode|lib|venv|bin|cmake-build-debug'