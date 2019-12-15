MAKEFLAGS += --no-print-directory
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

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
cmake-wasm:
	mkdir -p build-wasm
	cd build-wasm && cmake .. -DCMAKE_TOOLCHAIN_FILE=${EMSDK}/fastcomp/emscripten/cmake/Modules/Platform/Emscripten.cmake -DMODE=wasm

#cmake-windows: cmake for windows distro
.PHONY: cmake-windows
cmake-windows:
	mkdir -p build-native
	cmd.exe /c "cd /d $(shell wslpath -w $(mkfile_dir))/build-native && cmake .. -G "MinGW Makefiles" -DMODE=native"

#cmake-native: cmake for native distro
.PHONY: cmake-native
cmake-native:
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

#windows: make windows
.PHONY: windows
windows: 
	cmd.exe /c "cd /d $(shell wslpath -w $(mkfile_dir))/build-native && mingw32-make"


#clean: clean all
.PHONY: clean
clean: clean-wasm clean-native

#clean-wasm: clean wasm
.PHONY: clean-wasm
clean-wasm:
	rm -r build-wasm

#clean-native: clean native
.PHONY: clean-native
clean-native:
	rm -r build-native