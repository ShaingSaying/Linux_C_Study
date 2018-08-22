# 简介

```c
/bin    //二进制文件目录，用于存放启动系统程序的标准路径
/usr/bin    //用户二进制文件路径，用于存放用户使用的标准程序
/usr/local  //本地二进制文件目录，用于存放软件安装程序
```

对于c语言来说，头文件几乎总是位于/usr/include目录及其子目录中。

标准系统库文件一般存储在/lib和/usr/lib目录中。

终极命令
```c
$ man
$ info
```

# shell程序设计

shell是一个作为用户与linux系统间的接口的程序，它允许用户向操作系统输入需要执行的命令。

```c
/bin/bash --version //bash作为/bin/sh的标准shell
```
## 管道和重定向
>文件描述符0 标准输入，文件描述符1 标准输出，文件描述符2 错误输出。

'>' 输出 '<' 输入
```c
ps >> lsoutput.txt  //'>>'操作符将输出内容**附加**到后边
kill -HUP 3321 >killout.txt 2>killerr.txt   //2>
kill -1 3321 > killouterr.txt 2>&1
kill -1 3321 > /dev/null 2>&1 //回收站-->"/dev/null"

more < killout.txt
```

'|'管道
```c
// sort排序，uniq出去名字相同的进程，grep -v sh删除名为sh的进程
ps -xo comm | sort | uniq | grep -v sh | more
```
## shell语法
### 变量
在变量名前加一个"$"符号来访问它的内容。

检查变量内容的一个简单方式：变量名前加一个"$"符号，再用echo命令将它的内容输出到终端上。

read命令将用户的输入赋值给一个变量。
```c
$ read salutation
hey..
$ echo salutation
hey..
```
#### 使用引号
$变量表达式放在双引号中，程序执行到这一行时就会把变量替换为它的值，如果放在单引号中，就不会发生替换现象。字符串通常放在双引号中，以防止变量被空白符分开，同时有允许$扩展。

#### 环境变量
```c
$HOME   //当前用户的家目录
$PATH   //以冒号分隔的用来搜索命令的目录列表
$0      //shell脚本名字
$#      //传递给脚本的参数个数
$$      //shell脚本的进程号，脚本程序通常用它来生存一个唯一的临时文件，如/tmp/tmpfile_$$
```
#### 参数变量
```c
$1,$2,...
$*  
$@  
```
### 条件
### 控制结构
### 函数
### 命令
### 命令的执行
### here文档
### 调试脚本程序

# 文件操作
```c
/dev/console    //系统控制台
/dev/tty        //控制终端
/dev/null   
```
## 底层文件访问
```c
#include<unistd.h>
size_t write(int fildes, const void *buf, size_t nbytes);   //把缓冲区buf前nbytes个字节写入与文件描述符fildes关联的文件中。
size_t read(int fildes, void *buf, size_t nbytes);  //从文件描述符fildes相关的文件里读入nbytes个字节数据，存放到buf中。
int close(int fildes);
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);

off_t lseek(int fildes, off_t offset, int whence);  //对文件描述符fildes的读写指针进行设置。
int fstat(int fildes, struct stat *buf);    //返回与打开文件描述符相关的文件的状态信息，写入buf结构
int stat(const char *path, struct stat *buf);   //当文件是一个符号链接时，返回该符号链接指向的文件的信息。
int lstat(const char *path, struct stat *buf);  //当文件是一个符号链接时，返回该符号链接本身的信息。

int dup(int fildes);        //赋值文件描述符fildes，返回一个新文件描述符
int dup2(int fildes, int fildes2);  //通过明确指定木办法描述符来把一个文件描述符复制为另外一个
```
## 标准I/O
```c
//stdin,stdout,stderr
#include<stdio.h>
FILE *fopen(const char *filename, const char *mode);
size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);  //数据从文件流stream读到由ptr指向的数据缓冲区里。size参数指定每个数据记录的长度，计数器nitems给出要传输的记录个数
size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream);
int fclose(FILE *stream);
int fflush(FILE *stream); //把文件流里的所有未写出数据立刻写出。fclose函数隐含执行了一次flush操作，所以不必再调用fclose之前调用fflush

int fseek(FILE *stream, long int offset, int whence); //文件流里为下一次读写操作指定位置

int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar();      //从标准输入里读取下一个字符

int fputc(int c, FILE *stream);
int putc(int c,FILE *stream);   //但它可能被实现为一个宏
int putchar(int c);

/******
fgets把读到的字符写到s指向的字符串里，直到出现下面某种情况：遇到换行符，已经传输了n-1个字符，或者到达文件尾。
会把遇到的换行符也传递到接收字符串里，在加上一个表示结尾的空字节\0。一次调用最多只能传输n-1个字符，因为它必须要把空字节加上以结束字符串。
******/
char *fgets(char *s, int n, FILE *stream);
char *gets(char *s);    //它从标准输入读取数据并丢去遇到的换行符。它在接收字符串的尾部加上一个null字节。
```
## 格式化输入输出
```c
int printf(const char *format, ...);    //输出送到标准输出
int sprintf(char *s, const char *format, ...);  //把输出和一个结尾空字符写到作为参数传递过来的字符串2里
int fprintf(FILE *stream, const char *format, ...); //把输出送到一个指定的文件流。

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *s, const char *format, ...);

/****
fgetpos: 获取文件流的当前位置。
fsetpos: 设置文件流的当前位置
ftell:  返回文件流当前位置的偏移
rewind: 重置文件流里的读写位置
freopen: 重新使用一个文件流
setvbuf: 设置文件流的缓冲机制
remove: 相当于unlink函数，如果参数path是一个目录，相当于rmdir函数
****/

#include<errno.h>
extern int errno;
int ferror(FILE *stream);
int feof(FILE *stream);
void clearerr(FILE *stream);

int fileno(FILE *stream);
FILE *fdopen(int fildes,const char *mode);
```
## 文件和目录维护
```c
#include<sys/stat.h>
#include<unistd.h>
int chmod(const char *path, mode_t mode);   //改变文件目录的访问权限
int chown(const char *path, uid_t owner, gid_t group);

int unlink(const char *path);
int link(const char *path1,const char *path2);
int symlink(const char *path1, const char *path2);

int mkdir(const char *path, mode_t mode);
int rmidr(const char *path);    //删除空目录

char *getcwd(char *buf, size_t size);   //获取当前目录的名字
int chdir(const char *path);    
```
## 扫描目录
```c
#include<sys/types.h>
#include<dirent.h>

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
long int telldir(DIR *dirp);
void seekdir(DIR *dirp, long int loc);
int closedir(DIR *dirp);
```
## 错误处理
```c
#include<string.h>
#include<stdio.h>
char *strerror(int errnum);
void perror(const char *s);
```
## /proc文件系统
```c
cat /proc/cpuinfo   //查看cpu的详细信息
cat /proc/meminfo   //内存使用情况
cat /proc/version   //内核版本信息
cat /proc/sys/fs/file-max   //同时打开的文件总数
```
## fcntl和mmap
```c
int fcntl(int fildes, int cmd);     //对底层文件描述符提供更多的操作方法
int fcntl(int fildes, int cmd, long arg);       
```
**mmap**(内存映射)函数的作用是建立一段可以被两个或更多个程序读写的内存。一个程序对它所做出的修改可以被其他程序看见。该函数创建一个指向一段内存区域的指针，该内存区域与可以通过一个打开的文件描述符访问的文件的内容相关联。
```c
#include<sys/mman.h>
void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);

int msync(void *addr, size_t len, int flags);   //把在该内存段的某个部分或整段中的修改写回到被映射的文件中

int munmap(void *addr, size_t len);     //释放内存段
```
# Linux环境
# 数据管理
# MySQL
# 开发工具
# 调试
# 进程与信号
# POSIX线程
# 进程间通信：管道
# 信号量、共享内存和消息队列
# 套接字