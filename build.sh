export LIBS_DIR="./lib"
export LIBS_ALLEGRO="-lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_color"

export CFLAGS="-fdiagnostics-color=always -std=c++20"
export SRC="src/*.cpp src/**/*.cpp"
#    \
#            src/**/*.cpp"
export INCLUDE="-Iinclude -Ideps"

/usr/bin/g++ ${CFLAGS} -g game/*.cpp ${SRC} ${INCLUDE} -L${LIBS_DIR} ${LIBS_ALLEGRO}
install_name_tool -add_rpath ${LIBS_DIR} a.out