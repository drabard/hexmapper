PROJ_NAME := hexmapper
CXX := clang++
DEBUG_FLAGS := -g -Wall -O0 -std=c++17
RELEASE_FLAGS := -O2
EXTERNAL := bin/ext/rlImGui.o bin/ext/libraylib.a bin/ext/imgui_all.a

#
# Project binaries.
#

PROJ_BIN_DIR := bin/$(PROJ_NAME)
PROJ_SRC_DIR := src/$(PROJ_NAME)
DBG_BIN_DIR := $(PROJ_BIN_DIR)/debug

.PHONY: debug
debug: $(DBG_BIN_DIR)/$(PROJ_NAME)

$(DBG_BIN_DIR)/$(PROJ_NAME): $(EXTERNAL) src/hexmapper/src/*.cpp src/hexmapper/include/*.h
	mkdir -p $(DBG_BIN_DIR)
	$(CXX) $(DEBUG_FLAGS) \
		-I$(PROJ_SRC_DIR)/include \
		-Isrc/ext/raylib/src \
		-Isrc/ext/imgui \
		-Isrc/ext/rlImGui \
		$(PROJ_SRC_DIR)/src/main.cpp \
		$(PROJ_SRC_DIR)/src/unity.cpp \
		bin/ext/imgui_all.a \
		bin/ext/rlImGui.o \
		-Lbin/ext -lraylib -lpthread -ldl \
		-o $(DBG_BIN_DIR)/$(PROJ_NAME) || exit 1
	cp -rv src/resources $(DBG_BIN_DIR)/

.PHONY: run
run: debug
	cd $(DBG_BIN_DIR) && ./$(PROJ_NAME)

.PHONY: clean
clean:
	rm -rf $(PROJ_BIN_DIR)

.PHONY: purge
purge: clean
	rm -rf src/ext/
	rm -rf bin/ext/
	rm -rf imgui.ini

#
# Tests.
#

TEST_SRC_DIR := $(PROJ_SRC_DIR)/src/test
TEST_BIN_DIR := $(PROJ_BIN_DIR)/test
TEST_SRCS := $(wildcard $(TEST_SRC_DIR)/*.cpp)
TESTS := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_BIN_DIR)/%,$(TEST_SRCS))

.PHONY: test
test: $(TESTS)

$(TESTS): $(TEST_BIN_DIR)/%: $(TEST_SRC_DIR)/%.cpp debug | $(TEST_BIN_DIR)
	@echo "Running test:" $*
	@$(CXX) $(DEBUG_FLAGS) \
		-I$(PROJ_SRC_DIR)/include \
		-Isrc/ext/raylib/src \
		-Isrc/ext/imgui \
		-Isrc/ext/rlImGui \
		$(PROJ_SRC_DIR)/src/unity.cpp \
		bin/ext/imgui_all.a \
		bin/ext/rlImGui.o \
		$< \
		-Lbin/ext -lraylib -lpthread -ldl \
		-o $@
	@$@
	@echo

$(TEST_BIN_DIR):
	@mkdir -p $(TEST_BIN_DIR)

#
# External dependencies.
#

# rlImGui
bin/ext/rlImGui.o: bin/ext/libraylib.a bin/ext/imgui_all.a
	echo "Compiling rlImGui"
	mkdir -p bin/ext/rlImGui
	if [ ! -d "src/ext/rlImGui" ]; then \
		git clone https://github.com/raylib-extras/rlImGui src/ext/rlImGui; \
	fi
	mkdir -p src/ext/rlImGui/build
	cd src/ext/rlImGui/build && $(CXX) $(RELEASE_FLAGS) -c \
		-I../../raylib/src \
		-I../../imgui \
		../rlImGui.cpp
	mv src/ext/rlImGui/build/rlImGui.o bin/ext/

# raylib
bin/ext/libraylib.a:
	echo "Compiling Raylib"
	mkdir -p src/ext/
	mkdir -p bin/ext/
	if [ ! -d "src/ext/raylib" ]; then \
		git clone --branch "5.0" https://github.com/raysan5/raylib.git src/ext/raylib; \
	fi
	cd src/ext/raylib/src && \
		$(MAKE) clean && \
		$(MAKE) PLATFORM=PLATFORM_DESKTOP && \
		cp libraylib.a ../../../../bin/ext

# imgui
bin/ext/imgui_all.a:
	echo "Compiling ImGui"
	mkdir -p src/ext/
	mkdir -p bin/ext/
	if [ ! -d "src/ext/imgui" ]; then \
		git clone --branch "v1.90.1" https://github.com/ocornut/imgui src/ext/imgui; \
	fi
	mkdir -p src/ext/imgui/build
	cd src/ext/imgui/build && $(CXX) $(RELEASE_FLAGS) -c \
		-Isrc/ext/imgui \
		../imgui.cpp \
		../imgui_tables.cpp \
		../imgui_widgets.cpp \
		../imgui_demo.cpp \
		../imgui_draw.cpp
	cd src/ext/imgui/build && \
		ar rcs imgui_all.a *.o
	mv src/ext/imgui/build/imgui_all.a bin/ext/imgui_all.a
