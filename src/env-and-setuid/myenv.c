#include <unistd.h>

extern char **environ;

int main()
{
  char *argv[2];

  argv[0] = "/usr/bin/env";
  argv[1] = NULL;

  execve("/usr/bin/env", argv, NULL); // 进程不想传递任何环境变量
 // execve("/usr/bin/env", argv, environ);  // 进程将环境变量传递给environ
  return 0 ;
}

