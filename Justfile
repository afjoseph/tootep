clean:
    rm -rf build

build:
    mkdir -p build
    cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Debug
    cmake --build build

test: build
    (cd build && ctest --verbose)
