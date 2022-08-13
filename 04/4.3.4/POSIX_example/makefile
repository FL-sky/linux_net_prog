# CFLAGS = -Iadd -Isub -O2
# VPATH=add:sub
# OBJS = add_int.o add_float.o sub_int.o sub_float.o main.o
# TARGET = cacu
# $(TARGET):$(OBJS)
# 	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
# clean:
# 	-$(RM) $(TARGET) 
# 	-$(RM) $(OBJS)

# ##自动推导规则

CFLAGS += -lrt -lpthread
OBJS = send.o
TARGET = send
$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)
clean:
	-$(RM) $(TARGET) 
	-$(RM) $(OBJS)

##自动推导规则