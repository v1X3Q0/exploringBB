obj-m+=ebbchar.o

BUILD_PATH=/home/mariomain/Projects/linux-2.6.36.4/build-out/linst/lib/modules/2.6.36.4/build/
OG_BUILD_PATH=/lib/modules/$(shell uname -r)/build/

all:
	make -C $(BUILD_PATH) M=$(PWD) modules
	$(TARGET)gcc testebbchar.c ebbHelper.c -o test --static -g
	$(TARGET)gcc dumpText.c ebbHelper.c -o dumpText --static -g
clean:
	make -C $(BUILD_PATH) M=$(PWD) clean
	rm test
	rm dumpText
