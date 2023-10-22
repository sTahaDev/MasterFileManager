APP_NAME = openglApp
BUILD_DIR = ./bin
CPP_FILES = ./src/*.cpp

APP_DEFINES:=
APP_INCLUDES := -I./include -I./include/imgui -I./include/imgui/backends -framework Opengl -framework Cocoa -framework IOKit -lc++
APP_LINKERS := -L./lib -lglfw3

build: 
	clang -std=c++17 $(CPP_FILES) ./include/imgui/*.cpp ./include/imgui/backends/imgui_impl_glfw.cpp ./include/imgui/backends/imgui_impl_opengl3.cpp -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES) $(APP_LINKERS)
	./bin/$(APP_NAME)