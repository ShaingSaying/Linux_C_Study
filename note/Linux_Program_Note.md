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
```c
int main(int argc, char *argv[])
//argc是程序参数的个数(包括程序名本身)，argv是一个代表参数自身的字符串数组(程序名为第一个元素argv[0])。
```
```c
#include<stdio.h>
int getopt(int argc, char *const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;
//getopt_long
```
## 日志
```c
/usr/adm & /var/log
/var/log/messages
/var/log/mail
/etc/syslog.conf
/etc/syslog-ng/syslog-ng.conf   //检查系统配置
```
```c
#include<syslog.h>
void syslog(int priority, const char *message, arguments...);
//转换控制符%m用于插入与错误变量errno当前值对应的出错消息字符串
void closelog(void);
void openlog(const char *ident, int logopt, int facility);
int setlogmask(int maskpri);
```
# 数据管理
交换空间(swap space)
>按需换页的虚拟内存系统

## 文件锁定
文件段锁定(文件区域锁定)
```c
#include<fcntl.h>
int fcntl(int fildes, int command, ...);
int fcntl(int fildes, int command, struct flock *flock_structure);
```
fcntl对一个打开的文件描述符进行操作，并根据command参数的设置完成不同的任务。提供了3个用于文件锁定的命令选项。
```c
F_GETLK
F_SETLK
F_SETLKW
```
flock(文件锁)结构依赖具体的实现，至少包含以下成员：
```c
short l_type
short l_whence  //取值必须是SEEK_SET(文件头),SEEK_CUR(当前位置),SEEK_END(文件尾)中的一个。l_whence通常设置为SEEK_SET,这时l_start就从文件的开始计算
off_t l_start   //l_whence是l_start的相对偏移位置，l_start是该区域的第一个字节
off_t l_len
pid_t l_pid
```
l_type成员的取值定义在头文件fcntl.h中
```c
F_RDLCK     //共享(或读)锁。许多不同的进程可以拥有文件同一(或者重叠)区域上的共享锁。只要任一进程拥有一把共享锁，那么就没有进程可以再获得该区域上的独占锁。为了获得一把共享锁，文件必须以“读”或“读写”方式打开
F_UNLCK     //解锁，用来清除锁
F_WRLCK     //独占(或写)锁。只有一个进程可以在文件的任一特定区域拥有一把独占锁。一旦一个进程拥有了这样一把锁，任何其他进程都无法在该区域上获得任何类型的锁。为了获得一把独占锁，文件必须以“写”或“读/写”方式打开
```
**F_GETLK命令**
用于获取fildes打开的文件的锁信息。它不会尝试去锁定文件。

调用进程把自己想创建的锁类型信息传递给fcntl，使用F_GETLK命令的fcntl就会返回将会阻止获取锁的任何信息。

进程可能使用F_GETLK调用来查看文件中某个区域的当前锁状态。如果文件已被锁定从而阻止锁请求成功执行，fcntl会用相关信息覆盖flock结构。如果所请求可以成功执行，flock结构将保持不变，如果F_GETLK调用无法获得信息，它将返回-1表明失败。成功就返回非-1值。

**F_SETLK命令**
对fildes指向的文件的某个区域加锁或解锁。flock结构中使用的值:l_type,l_pid。与F_GETLK一样，要加锁的区域由flock结构中的l_start,l_whence和l_len的值定义。

如果锁成功，返回非-1值，失败返回-1。

**F_SETLKW命令**
与F_SETLK相同，但在无法获取锁时，这个调用将等待直到可以为止。一旦开始等待，只有在可以获取锁或收到一个信号时才会返回。


# MySQL
## 连接
1. 初始化一个连接句柄结构
2. 实际进行连接
```c
#include<mysql.h>
MYSQL *mysql_init(MYSQL *);
MYSQL *mysql_real_connect(MYSQL *connection,    //被mysql_init初始化的结构
        const char *server_host,        //可以是主机名也可以是ip地址
        const char *sql_user_name,
        const char *sql_password,
        const char *db_name,
        unsigned int port_number,       //0
        const char *unix_socket_name,   //NULL
        unsigned int flags);
void mysql_close(MYSQL *connection);
```
```c
int mysql_options(MYSQL *connection, enum option_to_set, const char *argument);
/******
1. 在mysql_init和mysql_real_connect之间即可。
2. MYSQL_OPT_CONNECT_TIMEOUT const unsigned int * 连接超时之前的等待秒速
3. MYSQL_OPT_COMPRESS None,使用NULL 网络连接中使用压缩机制
4. MYSQL_INIT_COMMAND const char * 每次建立后发送的命令
5. 成功的调用将返回0。
******/
```
## 错误处理
```c
unsigned int mysql_errno(MYSQL *connection);
char *mysql_error(MYSQL *connection);
```
## 执行
### 不返回数据的语句UPDATE,DELETE,INSERT
```c
my_ulonglong mysql_affected_rows(MYSQL *connection);    //用于检查受影响的行数
```
### 返回数据的语句
```c
MYSQL_RES *mysql_store_result(MYSQL *connection);   //提取所有的数据
my_ulonglong mysql_num_rows(MYSQL_RES *result);     //返回结果集中的行数
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);       //从mysql_store_result的结果中提取一行，放入一个行结构中
void mysql_data_seek(MYSQL_RES *result, myulonglong offset);    //在结果集中跳转，设置被下一个mysql_fetch_row操作的返回的行
MYSQL_ROW_OFFSET mysql_row_tell(MYSQL_RES *result);     //返回一个偏移值，表示结果集中的当前位置
MYSQL_ROW_OFFSET mysql_row_seek(MYSQL_RES *result, MYSQL_ROW_OFFSET offset);        //在结果集中移动当前位置，返回之前位置
void mysql_free_result(MYSQL_RES *result);
MYSQL_RES *mysql_use_result(MYSQL *connection); //逐行提取数据，未提取的数据网络中
unsigned int mysql_field_count(MYSQL *connection);
MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *result);
```


# 开发工具
## make
## makefile
## 后缀和模式规则
## makefile文件和子目录

# 调试
## 预处理&宏
## GDB调试

# 进程与信号
UNIX标准定义进程为：一个其中运行着一个或多个线程的地址空间和这些线程所需要的系统资源。
**启动新进程**
它必须用一个shell来启动程序，使用system函数的效率不高。
```c
#include<stdlib.h>
int system(const char *string);
```
## 替换进程映像exec系列函数
exec系列函数把当前进程替换为一个新进程。可以使用exec函数讲程序的执行从一个程序切换到另一个程序。exec函数比system函数更有效，新的程序启动后，原来的程序不再运行。
```c
#include<stdio.h>
char **environ;
int execl(const char *path, const char *arg0, ..., (char *)0);
int execlp(const char *file, const char *arg0, ..., (char *)0);
int execle(const char *path, const char *arg0, ..., (char *)0, char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
```
## 复制进程映像fork
```c
#include<sys/types.h>
#include<unistd.h>
pid_t fork(void);
pid_t new_pid;
new_pid = fork();
switch(new_pid)
{
        case -1:        //error
                break;
        case 0:         //child
                break;
        default :       //parent
                break;
}
```
**wait等待一个进程**
```c
#include<sys/types.h>
#include<sys/wait.h>
pid_t wait(int *stat_loc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);
/*pid参数如果为-1，waitpid将返回任一子进程信息。*/
```
**僵尸进程**

子进程终止时，与父进程之间的关联还会保持，直到父进程也正常终止或父进程调用wait才结束。代表子进程的表项不会立刻释放，仍然存在于系统中，它的退出码仍然保存，此时它成为一个僵尸进程。

## 信号

信号是unix和linux系统响应某些条件而产生的一个事件。

**处理信号**
```c
#include<stdio.h>
void (*signal(int sig, void (*func)(int)))(int);
```

**发送信号**
```c
#include<sys/types.h>
#include<signal.h>
int kill(pid_t pid, int sig);   //成功0，失败-1

#include<unistd.h>
unsigned int alarm(unsigned int seconds); //定时发送SIGALRM信号

int pause(void);        //把程序挂起直到一个信号出现为止
```

**一个健壮的信号接口**
```c
#include<signal.h>
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);
```
sigaction结构成员
```c
void (*) (int) sa_handler       //函数指针，指向接收到信号sig时将被调用的信号处理函数。可以设置为SIG_IGN和SIG_DFL,分别表示忽略和恢复
sigset_t sa_mask                //信号集,加入到进程的信号屏蔽字段的
int sa_flags                    //
```
**信号集**
```c
#include<signal.h>

int sigaddset(sigset_t *set, int signo);        //增加给定的信号
int sigemptyset(sigset_t *set);         //将信号集初始化为空
int sigfillset(sigset_t *set);          //将信号集初始化为包含所有已定义的信号
int sigdelset(sigset_t *set, int signo);        //删除给定的信号
int sigismember(sigset_t *set, int signo);      //判断一个给定的信号是否是一个信号集的成员
int sigprocmask(int how, const sigset_t *set, sigset_t *oset);
int sigpending(sigset_t *set);
int sigsuspend(const sigset_t *sigmask);
```

# POSIX线程
线程是一个进程内部的一个控制序列。

当进程执行fork调用时，将创建出该进程的一个新副本。这个新进程拥有自己的变量和自己的PID，它的时间调度也是独立的，它的执行几乎完全独立于父进程。

当进程中创建一个新线程时，新的执行线程将拥有自己的栈(因此也有自己的局部变量),但与它的创建者共享全局变量、文件描述符、信号处理函数和当前的目录状态。

**_PEENTRANT**宏定义来告诉编译器我们需要可重入功能。

```c
#include<pthread.h>

int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```
## 同步
## 多线程
# 进程间通信：管道

# 信号量、共享内存和消息队列
## 信号量
## 共享内存
## 消息队列


# 套接字
## 套接字
## 多客户