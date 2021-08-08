obj-m+=ebbchar.o

BUILD_PATH=/home/mariomain/repos/android-bonito-r10/out/android-msm-pixel-4.9/private/msm-google/
OG_BUILD_PATH=/lib/modules/$(shell uname -r)/build/

ifeq ($(TARGET2),"")
	TARGET2 := $(TARGET)gcc
endif

all:
	make -C $(BUILD_PATH) M=$(PWD) modules
	$(TARGET2) testebbchar.c ebbHelper.c -o test --static -g
	$(TARGET2) dumpText.c ebbHelper.c -o dumpText --static -g
clean:
	make -C $(BUILD_PATH) M=$(PWD) clean
	rm test
	rm dumpText
