PROJ_NAME := hexmapper
CC := clang++
DEBUG_FLAGS := -g -Wall -O0
RELEASE_FLAGS := -O2
PROJ_BIN := bin/$(PROJ_NAME)
PROJ_SRC := src/$(PROJ_NAME)
DBG_BIN := $(PROJ_BIN)/debug

.PHONY: run
run: debug
	cd $(DBG_BIN) && ./$(PROJ_NAME)

.PHONY: clean
clean:
	rm -rf $(PROJ_BIN)

.PHONY: purge
purge: clean
	rm -rf src/ext/
	rm -rf bin/ext/
	rm -rf imgui.ini

.PHONY: debug
debug: external
	mkdir -p bin/$(PROJ_NAME)/debug/
	$(CC) $(DEBUG_FLAGS) -std=c++17 -c \
		-I$(PROJ_SRC)/include \
		-Isrc/ext/raylib/src \
		-Isrc/ext/imgui \
		-Isrc/ext/rlImGui \
		src/$(PROJ_NAME)/src/unity.cpp \
		-o $(DBG_BIN)/$(PROJ_NAME).o
	$(CC) \
		bin/debug/$(PROJ_NAME).o \
		bin/ext/imgui_all.a \
		bin/ext/rlImGui.o \
		-Lbin/ext -lraylib -lpthread -ldl \
		-o $(DBG_BIN)/$(PROJ_NAME)
	cp -rv src/resources $(DBG_BIN)/

.PHONY: external
external: bin/ext/rlImGui.o bin/ext/libraylib.a bin/ext/imgui_all.a

bin/ext/rlImGui.o: bin/ext/libraylib.a bin/ext/imgui_all.a
	echo "Compiling rlImGui"
	mkdir -p bin/ext/rlImGui
	if [ ! -d "src/ext/rlImGui" ]; then \
		git clone https://github.com/raylib-extras/rlImGui src/ext/rlImGui; \
	fi
	mkdir -p src/ext/rlImGui/build
	cd src/ext/rlImGui/build && $(CC) $(RELEASE_FLAGS) -c \
		-I../../raylib/src \
		-I../../imgui \
		../rlImGui.cpp
	mv src/ext/rlImGui/build/rlImGui.o bin/ext/

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

bin/ext/imgui_all.a:
	echo "Compiling ImGui"
	mkdir -p src/ext/
	mkdir -p bin/ext/
	if [ ! -d "src/ext/imgui" ]; then \
		git clone --branch "v1.90.1" https://github.com/ocornut/imgui src/ext/imgui; \
	fi
	mkdir -p src/ext/imgui/build
	cd src/ext/imgui/build && $(CC) $(RELEASE_FLAGS) -c \
		-Isrc/ext/imgui \
		../imgui.cpp \
		../imgui_tables.cpp \
		../imgui_widgets.cpp \
		../imgui_demo.cpp \
		../imgui_draw.cpp
	cd src/ext/imgui/build && \
		ar rcs imgui_all.a *.o
	mv src/ext/imgui/build/imgui_all.a bin/ext/imgui_all.a
