mkdir -p build_osx && cd build_osx
cmake -GXcode ..
cd ..

cmake --build build_osx --config Release
mkdir -p Library/Mac
cp build_osx/Release/liblua.a Library/Mac/liblua.a 