#include "minishell.h"

void pipe_execute(t_config *config, char **envp){
    char *args[3];
    args[0] = "/bin/ls";
    args[1] = "-l";
    args[2] = NULL;

    char *argss[3];
    argss[0] = "/usr/bin/wc";
    argss[1] = "-l";
    argss[2] = NULL;
    int     ch[2];
    pid_t   child1;
    pid_t   child2;
    pipe(ch);
    child1 = fork();
    if (child1 == 0)
    {
        //* Child   1
        close(ch[0]);
        config->stdout_clone = dup(STDOUT_FILENO);
        dup2(ch[1], STDOUT_FILENO);
        if (execve(args[0], args, envp))
			    //printf("error exec pipe 1.\n");
          dup2(config->stdout_clone, STDOUT_FILENO);
          close(config->stdout_clone);
          close(ch[1]);
          exit(0);
    }

    child2 = fork();
    if (child2 == 0){
        //* Child   2
        close(ch[1]);
        config->stdin_clone = dup(STDIN_FILENO);
        dup2(ch[0], STDIN_FILENO);
        //printf("val : %s \n", argss[0]);
        if (execve(argss[0], argss, envp))
            //printf("error exec pipe 2.\n");
        dup2(config->stdin_clone, STDIN_FILENO);
        close(config->stdin_clone);
        close(ch[0]);
        exit(0);
    }

    
    close(ch[0]);
    close(ch[1]);
    wait(NULL);
    wait(NULL);
    // sleep(10);
}

int main(int argc, char **argv, char **envp){
    t_config config;
    (void)argc;
    (void)argv;
    pipe_execute(&config, envp);
}