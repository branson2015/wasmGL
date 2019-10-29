#Build: cmake and make all
.PHONY: build
build: cmake all



#all: make all
.PHONY: all
all: wasm native

#cmake: cmake all
.PHONY: cmake
cmake: cmake-wasm cmake-native



#cmake-wasm: cmake for wasm distro
.PHONY: cmake-wasm
	mkdir -p build-wasm
	cd build-wasm && cmake .. -DCMAKE_TOOLCHAIN_FILE=${EMSDK}/fastcomp/emscripten/cmake/Modules/Platform/Emscripten.cmake -DMODE=wasm

#cmake-native: cmake for native distro
.PHONY: cmake-native
	mkdir -p build-native
	cd build-native && cmake .. -DMODE=native



#wasm: make wasm
.PHONY: wasm
wasm:
	cd build-wasm && make
	cd build-wasm && python -m SimpleHTTPServer 8080

#native: make native
.PHONY: native
native:
	cd build-native && make



#clean: clean all
.PHONY: clean
clean: clean-wasm clean-native

#clean-wasm: clean wasm
.PHONY: clean-wasm
clean-wasm:
	cd build-wasm && make clean && rm render.js render.wasm && rm wasm.html

#clean-native: clean native
.PHONY: clean-native
clean-native:
	cd build-native && make clean