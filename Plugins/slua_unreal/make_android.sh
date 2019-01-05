if [ -z "$ANDROID_NDK" ]; then
    echo "Android NDK not detected'"
    exit 1
fi

mkdir -p build_android_v7a && cd build_android_v7a
cmake -DANDROID_ABI=armeabi-v7a -DCMAKE_TOOLCHAIN_FILE=../cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9 -DANDROID_NATIVE_API_LEVEL=android-9 ..
cd ..

cmake --build build_android_v7a --config Release
mkdir -p Library/Android/armeabi-v7a/
cp build_android_v7a/liblua.a Library/Android/armeabi-v7a/liblua.a

mkdir -p build_android_arm64 && cd build_android_arm64
cmake -DANDROID_ABI=arm64-v8a -DCMAKE_TOOLCHAIN_FILE=../cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=aarch64-linux-android-4.9 -DANDROID_NATIVE_API_LEVEL=android-21 ..
cd ..

cmake --build build_android_arm64 --config Release
mkdir -p Library/Android/armeabi-arm64/
cp build_android_arm64/liblua.a Library/Android/armeabi-arm64/liblua.a

mkdir -p build_android_x86 && cd build_android_x86
cmake -DANDROID_ABI=x86 -DCMAKE_TOOLCHAIN_FILE=../cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=x86-4.9 -DANDROID_NATIVE_API_LEVEL=android-9 ..
cd ..

cmake --build build_android_x86 --config Release
mkdir -p Library/Android/x86/
cp build_android_x86/liblua.a Library/Android/x86/liblua.a