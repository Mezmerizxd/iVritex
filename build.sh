#!/bin/bash

build=$1
FILE=iVritex.sln

function BuildSource {
  echo "Compiling source..."
  eval "MSBuild.exe $FILE /property:Configuration=$conf"
}

function Premake5 {
  eval "./vendor/premake/premake5.exe vs2019"
  echo "Premake finished."
  BuildSource
}

function VerifyProjectFiles {
  echo "Verifying project files..."
  if [[ -f "$FILE" ]]; then
    echo "Project files found." 
    BuildSource
  else
    echo "Missing project files. Running premake5..."
    Premake5
  fi
}

if [[ $build == "debug" ]]; then
    conf="Debug"
    echo "Building..."
    VerifyProjectFiles
    echo "Debug build complete."
elif [[ $build == "release" ]]; then
    conf="Release"
    echo "Building..."
    VerifyProjectFiles
    echo "Release build complete."
else
    echo "Invalid argument."
fi
