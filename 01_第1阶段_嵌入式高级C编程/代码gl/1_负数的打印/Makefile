# 1. 使用不同的开发板内核时, 一定要修改KERN_DIR
# 2. KERN_DIR中的内核要事先配置、编译, 为了能编译内核, 要先设置下列环境变量:
# 2.1 ARCH,          比如: export ARCH=arm64
# 2.2 CROSS_COMPILE, 比如: export CROSS_COMPILE=aarch64-linux-gnu-
# 2.3 PATH,          比如: export PATH=$PATH:/home/book/100ask_roc-rk3399-pc/ToolChain-6.3.1/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin 
# 注意: 不同的开发板不同的编译器上述3个环境变量不一定相同,
#       请参考各开发板的高级用户使用手册

# 需要借助Linux内核源码来编译驱动程序,KERN_DIR表示ubuntu里面linux内核源码的目录
#KERN_DIR = /home/book/100ask_imx6ull-sdk/Linux-4.9.88


# 参考内核源码drivers/char/ipmi/Makefile
# 要想把a.c, b.c编译成ab.ko, 可以这样指定:
# ab-y := a.o b.o
# obj-m += ab.o

# 以下是需要编译的驱动程序
# leddrv.c board_demo.c board_A_led.c 编译成 100ask_led.ko
#100ask_led-y := leddrv.o chip_demo_gpio.o board_A_led.o
#obj-m	+= 100ask_led.o

# 以下是需要编译的驱动程序
#obj-m	+= led_drv.o


# 通配符:%.o;以下是需要编译的应用程序
objs = negative_number.o
# 可以使用 objs += lcd/font.o来追加.o文件进工程里面参与编译

CC := gcc
#CC := arm-buildroot-linux-gnueabihf-gcc 

# 可执行程序的名字
ExecutableName := negative_number


# 添加编译编译选项,-Werror表示把原来的编译警告当做错误来处理,
# -Iinclude表示让编译器从头文件路径 include 里面查找头文件
#CFLAGS := -Werror 
CFLAGS += -Wall -w
#CFLAGS += -g
#CFLAGS += -lpthread
#CFLAGS += -pthread
#CFLAGS += -Iinclude

# 编译内核使用的编译选项不能使用 CFLAGS,得改为 EXTRA_CFLAGS
#EXTRA_CFLAGS := -Werror 
#EXTRA_CFLAGS += -Wall -w


# Makefile文件默认只生成第一个目标文件即完成翻译
$(ExecutableName): $(objs)
	@# 进入ubuntu里面linux内核源码的目录,把当前目录里面hello_drv.c文件编译为驱动程序
	@#make -C $(KERN_DIR) M=`pwd` modules 
	@# 编译应用程序
	$(CC) $(CFLAGS) -o $(ExecutableName) $^
	@#$(CC) $(EXTRA_CFLAGS) -o $(ExecutableName) $^

	
# 需要判断是否存在依赖文件
# .a.o.d .b.o.d .c.o.d
# 延时变量objs的值全部值都加上前缀.和后缀.d,即a.o会变成.a.o.d
dep_files := $(patsubst %,.%.d, $(objs)) 
# 判断当前路径是否存在.a.o.d文件,如果存在的话就把文件名.a.o.d赋值给即时变量dep_files
dep_files := $(wildcard $(dep_files))


# 把依赖文件包含进来
ifneq ($(dep_files),)
include $(dep_files)
endif


# $@表示目标,$<表示第一个依赖文件,$^表示所有依赖文件

%.o : %.c
	@# 编译a.c文件生成a.o文件,同时把a.c文件所依赖的全部头文件写入到.a.o.d文件里面:-MD -MF .$@.d
	@# 以后a.c文件有更新或者a.h文件有更新的话,也会重新生成a.o文件
	$(CC) $(CFLAGS) -c -o $@ $< -MD -MF .$@.d
	@#$(CC) $(EXTRA_CFLAGS) -c -o $@ $< -MD -MF .$@.d

clean:
	# 删除可执行文件和所有.o文件
	rm -f $(ExecutableName) 
	rm -f *.o 
	@# 删除当前目录编译的驱动程序
	@#make -C $(KERN_DIR) M=`pwd` modules clean
	@#rm -rf modules.order

distclean:
	# 删除可执行文件和所有.o文件以及.a.o.d文件和.b.o.d文件
	rm -f $(ExecutableName) 
	rm -f $(dep_files) *.o
	@# 删除当前目录编译的驱动程序
	@#make -C $(KERN_DIR) M=`pwd` modules clean
	@#rm -rf modules.order	

# 要把“ clean”这个目标，设置为"假想目标",这样的话就算当前目录下恰好有名为“ clean”的文件,
# 执行"make clean"时那些删除命令肯定可以得到执行	
.PHONY: clean	