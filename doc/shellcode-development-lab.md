## 资料

https://seedsecuritylabs.org/Labs_20.04/Files/Shellcode/Shellcode.pdf

## 步骤

sudo apt install nasm  

编译32位.o文件：
cd /vagrant/Labsetup/  
nasm -f elf32 mysh.s -o mysh.o  
 
链接成32位二进制可执行文件：  
ld -m elf_i386 mysh.o -o mysh  

确认mysh是否执行：
```bash
echo $$
1121
./mysh
echo $$
1391
```

用intel模式得到机器码：  
objdump -Mintel --disassemble mysh.o  

也可以用如下命令打印完整二进制内容：  
xxd -p -c 20 mysh.o  

拷贝机器码到convert.py  
打印恶意代码：./convert.py  