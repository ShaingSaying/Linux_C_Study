EXE_DIR:=./bin 	#生成可执行函数的地址
INC_DIR:=./include 	#头文件
SRC_DIR:=./src #源文件

OBJECTS:=./src/pool_main.c ./src/pool_thread.c ./src/pool_que.c

$(EXE_DIR)/main:$(OBJECTS) $(INCLUDES)
	gcc -g -o main $(OBJECTS) -I$(INC_DIR) -lpthread #编译命令
