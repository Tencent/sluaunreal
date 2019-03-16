mkdir -p build_linux && cd build_linux
cmake ..
cd ..

cmake --build build_linux --config Release
mkdir -p Library/Linux
cp build_linux/liblua.a Library/Linux/liblua.a 
