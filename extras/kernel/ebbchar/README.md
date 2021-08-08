
`export KERNEL_ARCH=arm`
`export TARGET=/home/mariomain/Downloads/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-`
`make ARCH=$KERNEL_ARCH CROSS_COMPILE=$TARGET`

# FOR ANDROID
`make ARCH=$KERNEL_ARCH CROSS_COMPILE=$TARGET CROSS_COMPILE_ARM32=$TARGET32`
`export TARGET2=$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android30-clang`

