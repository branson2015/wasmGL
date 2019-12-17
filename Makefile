MAKEFLAGS += --no-print-directory
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

#Build: cmake and make all
.PHONY: build
build: cmake all

#all: make all
.PHONY: all
all: wasm windows

#cmake: cmake all
.PHONY: cmake
cmake: cmake-wasm cmake-windows

#cmake-wasm: cmake for wasm distro
.PHONY: cmake-wasm
cmake-wasm:
	mkdir -p build-wasm
	cd build-wasm && cmake .. -DCMAKE_TOOLCHAIN_FILE=${EMSDK}/fastcomp/emscripten/cmake/Modules/Platform/Emscripten.cmake -DMODE=wasm

#cmake-windows: cmake for windows distro
.PHONY: cmake-windows
cmake-windows:
	mkdir -p build-windows
	cmd.exe /c "cd /d $(shell wslpath -w $(mkfile_dir))/build-windows && cmake .. -G "MinGW Makefiles" -DMODE=native"

#cmake-linux: cmake for linux distro
.PHONY: cmake-linux
cmake-linux:
	mkdir -p build-linux
	cd build-linux && cmake .. -DMODE=native

#wasm: make wasm
.PHONY: wasm
wasm:
	cd build-wasm && make
	cd build-wasm && python -m SimpleHTTPServer 8080

#linux: make linux
.PHONY: linux
linux:
	cd build-linux && make

#windows: make windows
.PHONY: windows
windows: 
	cmd.exe /c "cd /d $(shell wslpath -w $(mkfile_dir))/build-windows && mingw32-make"

#clean: clean all
.PHONY: clean
clean: clean-wasm clean-linux clean-windows

#clean-wasm: clean wasm
.PHONY: clean-wasm
clean-wasm:
	rm -rf build-wasm

#clean-linux: clean linux
.PHONY: clean-linux
clean-linux:
	rm -rf build-linux

#clean-windows: clean windows
.PHONY: clean-windows
clean-windows:
	rm -rf build-windows