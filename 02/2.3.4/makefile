CC = gcc
CFLAGS = -Iadd -Isub -O2
OBJS = add/add_int.o add/add_float.o sub/sub_int.o sub/sub_float.o main.o
TARGET = cacu
RM = rm -f
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
$(OBJS):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	-$(RM) $(TARGET) $(OBJS)
## 此处的 - 表示失败时不报错。即 删除不存在的文件不报错（假设没有main.o）
### $@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。

## makefile中使用变量