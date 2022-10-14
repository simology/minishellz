#include "minishell.h"
void demo(char **envp){

char *args[2];
args[0] = "/bin/ls";
args[1] = "-l";

char *argss[2];
argss[0] = "/usr/bin/wc";
argss[1] = "-l";
pid_t pid;
int fd[2];

pipe(fd);
pid = fork();

if(pid==0)
{
    dup2(fd[1], STDOUT_FILENO);

    if (execve(args[0], args, envp))
      printf("error exec pipe 1.\n");
    exit(1);
}
else
{ 
    pid=fork();

    if(pid==0)
    {
        dup2(fd[0], STDIN_FILENO);

        if (execve(argss[0], argss, envp))
            printf("error exec pipe 2.\n");
        exit(1);
    }
    else
    {
        int status;
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, &status, 0);
    }
}

}


int main(int argc, char **argv, char **envp)
{
(void)argc;
(void)argv;
  demo(envp);
}