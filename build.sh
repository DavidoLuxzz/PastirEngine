export LIBS_DIR="/opt/homebrew/lib"
export LIBS="-lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_color"

export LIBS_DIR2="/usr/local/lib/FMOD"
export LIBS2="-lfmod"

export CFLAGS="-fdiagnostics-color=always -std=c++20"
export SRC="src/*.cpp src/**/*.cpp"
#    \
#            src/**/*.cpp"
export INCLUDE="-Iinclude -Ideps"

/usr/bin/g++ ${CFLAGS} -g game/*.cpp ${SRC} ${INCLUDE} -L${LIBS_DIR} ${LIBS} -L${LIBS_DIR2} ${LIBS2}
install_name_tool -add_rpath ${LIBS_DIR} -add_rpath ${LIBS_DIR2} a.out