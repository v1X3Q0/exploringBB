
```
export KERNEL_ARCH=arm
export TARGET=/home/mariomain/Downloads/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-
make ARCH=$KERNEL_ARCH CROSS_COMPILE=$TARGET
```

# FOR ANDROID
```
export KERNEL_ARCH=arm64
export KERNEL_PATH=$HOME/repos/android-bonito
export TARGET=$KERNEL_PATH/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
export TARGET32=$KERNEL_PATH/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9/bin/arm-linux-androideabi-
export TARGET2=$NDK_PATH/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android30-clang
make ARCH=$KERNEL_ARCH CROSS_COMPILE=$TARGET CROSS_COMPILE_ARM32=$TARGET32 ANDROID=1
```

## potential source patch
also, patch the file source/Makefile in bonito source, the line that does gcc fsanitize, needs
to be zero'd

`scs-flags	:= -fsanitize=shadow-call-stack`
to
`scs-flags	:= `

sample patch has been provided, and can be executed with:

`patch -i newPatch.patch -p0 -d $KERNEL_PATH`