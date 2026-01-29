export LIBS_DIR="/opt/homebrew/lib"
export LIBS="-lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_color"
export CFLAGS="-fdiagnostics-color=always"
export SRC="src/*.cpp"
#    \
#            src/**/*.cpp"
export INCLUDE="-Iinclude -Ideps"

/usr/bin/g++ -g ${SRC} ${INCLUDE} -L${LIBS_DIR} ${LIBS}
install_name_tool -add_rpath ${LIBS_DIR} a.out