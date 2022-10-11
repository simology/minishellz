#include "minishell.h"


char *read_line(void)
{
  char *line;
  line = readline( "minishell> " );
  if (line == NULL)
    return (0);
  else
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
    //printf("VAL : %s \n", splited[position]);
    position++;
  }
  //printf("total split %d \n", position);
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
  char *line;
  
  int status;

  status = 1;

  while(status) 
  {
    line = read_line();
    config->args_cmd = split_command_line(line);
    status = cmd_prepare(config);
    free(line);
    //free(args);
  }
}

int old_cmd_execute(char **args)
{
  pid_t pid;
  //pid_t wpid;
  //int status;
  printf("cmd from exe : %s \n", args[0]);
  printf("cmd from exe 2 : %s \n", args[1]);
  pid = fork();
  if (pid == 0) {
    printf("Child PID: %d\n", getpid());
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("exec error");
    }
    //exit(EXIT_FAILURE);
  }
  else {
    // Error forking
    perror("lsh fork");
  }
  /*
  else {
    // Parent process
    while(!WIFEXITED(status) && !WIFSIGNALED(status))
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    }
  }
  */
  return 1;
}

int cmd_execute(t_config *config){

	pid_t pid;

	pid = fork();

	if(pid == 0) {
		/*
		printf("cmd 1 : %s \n", config->args_cmd[0]);
		printf("args 2 : %s \n", config->args_cmd[1]);
		*/
		if (execvp(config->args_cmd[0], config->args_cmd) == -1) {
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
	else {
		
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

void shell_init(t_config *config){
	
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);

}

int main(void)
{
	t_config config;
	shell_init(&config);
	shell_loop(&config);
  	return (1);
}