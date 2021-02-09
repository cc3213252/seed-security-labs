## 资料

https://seedsecuritylabs.org/Labs_20.04/Files/Environment_Variable_and_SetUID/Environment_Variable_and_SetUID.pdf

## task1 打印环境变量

```bash
printenv PWD
env | grep PWD
export a=1
printenv a
unset a 
printenv a
```
shell关闭后失效  
  
## task2 父进程往子进程传递环境变量

```bash
sudo apt-get update
sudo apt install gcc -y
cd /vagrant/src/env-and-setuid
gcc myprintenv.c
./a.out > file1
```
接下来改程序，注释掉1，放开2，重新编译，保存到file2
```bash
diff file1 file2
```
两个文件完全一样，说明父往子传递env   

## task3 环境变量在execve使用

```bash
gcc -o myenv myenv.c
./myenv
```
修改代码之后再编译执行  
NULL时没有输出任何环境变量，说明没有传递环境变量  
environ时传递了系统的环境变量    

## task4 环境变量在system使用

没有详细步骤，实验目的应该是为了说明system实际执行的是/bin/sh -c command  
不清楚如何能说明  

## task5 set-uid使用

gcc -o foo foo.c
export aaa=3333
./foo 可以看到已经出现了环境变量

## task6 利用system实现软件入侵，该实验较好

```text
#include <stdio.h>
#include <stdlib.h>

int main()
{
system("ls");
return 0;
}
```
gcc -o lsdemo lsdemo.c  
sudo chown root lsdemo  
sudo chmod 4755 lsdemo  

system这个函数实际调用的是/bin/sh

怎么做，才能说明用自己程序代替系统ls？

## task7 LD PRELOAD使用

实验目的：用自己写的sleep代替系统sleep  
        提供了一种替换linux默认动态链接库的方法  
完整步骤：
vi mylib.c  
gcc -fPIC -g -c mylib.c  
gcc -shared -o libmylib.so.1.0.1 mylib.o -lc  
export LD_PRELOAD=./libmylib.so.1.0.1  
vi myprog.c
gcc -o myprog myprog.c  
./myprog  可以看到系统sleep已被替换  

## task8 用system和execve调用外部程序  

由于实验7把系统动态链接库破坏了，导致这个程序编译错误    
只需重启shell即可  

## task9 能力泄露，由于未关闭文件句柄导致的泄露

结果跟上一个一样，动态连接库