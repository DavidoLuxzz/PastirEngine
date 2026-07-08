CXX = /usr/bin/g++
CXXFLAGS = -fdiagnostics-color=always -std=c++20 -g
INCLUDES = -Iinclude -Ideps
LIBS_DIR = ./lib
LDFLAGS = -L$(LIBS_DIR)
LDLIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_image -lallegro_color
SRC_DIRS = src game
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' | sort)
OBJS := $(patsubst %.cpp,build/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)
TARGET = a.out

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
	install_name_tool -add_rpath $(LIBS_DIR) $@

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -rf build
	rm -f $(TARGET)
