#include "minishell.h"


char *read_line(t_config *config)
{
  char *line;
  line = readline(config->banner);
  if (line == NULL)
    return (0);
  else
    add_history(line);
    return (line);
}

char **split_command_line(char *line)
{
  int position;
  char **tokens;
  char **splited;

  position = 0;
  splited = ft_split(line, (char)SPACE_DELM);
  while (splited[position] != '\0'){
    position++;
  }
  tokens = malloc(position * sizeof(char*));
  position = 0;
  while(splited[position] != '\0'){
    tokens[position] = splited[position];
    position++;
  }
  tokens[position] = 0;
  return tokens;
}

char **split_pipe_cmd(char *line)
{
  int position;
  char **tokens;
  char **splited;

  position = 0;
  splited = ft_split(line, (char)PIPE_DELM);
  while (splited[position] != '\0'){
    position++;
  }
  tokens = malloc(position * sizeof(char*));
  position = 0;
  while(splited[position] != '\0'){
    tokens[position] = splited[position];
    position++;
  }
  tokens[position] = 0;
  return tokens;
}
void shell_loop(t_config *config)
{  
  int status;

  status = 1;

  while(status) 
  {
    config->line = read_line(config);
    config->args_cmd = split_command_line(config->line);
    
    status = pipe_execute(config);
    //status = cmd_prepare(config);

    //operator_detector(config);
    //config->pipe_cmd = split_pipe_cmd(config->line);
  
    //ft_argv_print(config->pipe_cmd);
    free(config->line);
    //free(args);
  }
}


int cmd_execute(t_config *config){

	pid_t pid;

	pid = fork();

	if(pid == 0) {
		/*
		printf("cmd 1 : %s \n", config->args_cmd[0]);
		printf("args 2 : %s \n", config->args_cmd[1]);
		*/
		//if (execvp(config->args_cmd[0], config->args_cmd) == -1) {
      if(execve(ft_pathfinder("", config->envp), config->args_cmd, config->envp)){
			printf("error exec.\n");
	}
		exit(EXIT_FAILURE);

	}
	else if(pid > 0) {
		/*
		printf("Parent => PID: %d\n", getpid());
		printf("Waiting for child process to finish.\n");
		*/
		wait(NULL);
		/*
		printf("Child process finished.\n");
		*/
	}
	return 1;

}



int cmd_prepare(t_config *config)
{
	int i;
	i = 0;
	//ft_argv_print(config->args_cmd);  	
	
  if (config->args_cmd[0] == NULL) {
    return 1;
  }

  while(i < config->builtin_len){
      if (ft_strcmp(config->args_cmd[0], config->builtin_cmd[i]) == 0) {
        return (builtin_func(config->builtin_cmd[i], config->args_cmd));
    }
	i++;
  }
	return cmd_execute(config);
}

int pipe_detector(t_config *config){

return (config->n_pipe);
}

int operator_detector(t_config *config){
  /*
  if(config->n_pipe)
    return(pipe_execute(config));
  */
  return (config->n_pipe);
}

int pipe_execute(t_config *config){
    char *args[2];
    args[0] = "/bin/ls";
    args[1] = "-l";

    char *argss[2];
    argss[0] = "/usr/bin/wc";
    argss[1] = "-l";
    int     ch[2];
    pid_t   child1;
    pid_t   child2;
    pipe(ch);
    child1 = fork();
    if (0 == child1) {
        //* Child   1
        printf("val : %s", args[0]);
        config->stdout_clone = dup(STDOUT_FILENO);
        dup2(STDOUT_FILENO, ch[1]);
        if (execve(args[0], args, config->envp))
			    printf("error exec pipe 1.\n");
          dup2(STDOUT_FILENO, config->stdout_clone);
          close(config->stdout_clone);
    }
    else
    {
        //* Parent
        child2 = fork();
        if (0 == child2) {
            //* Child   2
        config->stdin_clone = dup(STDIN_FILENO);
        dup2(STDIN_FILENO, ch[0]);
        printf("val : %s", argss[0]);
        if (execve(argss[0], argss, config->envp))
            printf("error exec pipe 2.\n");
        dup2(STDIN_FILENO, config->stdin_clone);
        close(ch[1]);
        }
        else
        {
            //* Parent
            close(ch[0]);
            close(ch[1]);
            waitpid(child1, NULL, 0);
            waitpid(child2, NULL, 0);
            return (1);
        }
    }
  return (0);
}

void shell_init(t_config *config, char **envp){
	config->envp = envp;
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);
  config->banner = ft_strcat(getenv("USER"), "@minishell>");
  config->n_pipe = 0;
}

int main(int argc, char **argv,char **envp)
{
  (void)argc;
  (void)argv;
	t_config config;
	shell_init(&config, envp);
	shell_loop(&config);
  	return (1);
}