uhh="build/"
project_name="${PWD##*/}"
PROJ_PATH="${uhh}${project_name}"
cmake --build build && ./$PROJ_PATH
