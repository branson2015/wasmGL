#emcc src/render.cpp src/glad.c -lglfw3 -lGL -lX11 -lpthread -ldl -I include -s USE_GLFW=3 -o test.html -Werror

.PHONY: all
all: wasm native

.PHONY: wasm
wasm:
	mkdir -p build-wasm
	cd build-wasm && cmake .. -DCMAKE_TOOLCHAIN_FILE=${EMSDK}/fastcomp/emscripten/cmake/Modules/Platform/Emscripten.cmake -DMODE=wasm
	cd build-wasm && make
	cd build-wasm && python -m SimpleHTTPServer 8080

.PHONY: native
native:
	mkdir -p build-native
	cd build-native && cmake .. -DMODE=native
	cd build-native && make

.PHONY: clean-wasm
clean-wasm:
	cd build-wasm && make clean && rm render.js render.wasm && rm wasm.html

.PHONY: clean-native
clean-native:
	cd build-native && make clean

.PHONY: clean
clean: clean-wasm clean-native
	
	
