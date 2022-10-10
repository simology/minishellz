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

void shell_loop(void)
{
  char *line;
  char **args;
  int status;

  status = 1;

  while(status) 
  {
    line = read_line();
    args = split_command_line(line);
	
    status = cmd_prepare(args);
    //printf("val : %d \n", len_num_builtins());

    free(line);
    free(args);
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

int cmd_execute(char **args){

pid_t pid = fork();
  if(pid == 0) {
	printf("Child => PPID: %d PID: %d\n", getppid(), getpid());
	printf("cmd 1 : %s \n", args[0]);
	printf("cmd 2 : %s \n", args[1]);
    if (execvp(args[0], args) == -1) {
      	printf("error exec.\n");
    }
	exit(EXIT_FAILURE);
    
  }
  else if(pid > 0) {
    printf("Parent => PID: %d\n", getpid());
    printf("Waiting for child process to finish.\n");
    wait(NULL);
    printf("Child process finished.\n");
  }
  else {
    printf("Unable to create child process.\n");
  }
 
  return 1;

}

int cmd_prepare(char **args)
{
  int i;
  char **cmd;
	char **lab;
	lab = builtin_str();
  i = 0;
  cmd = lab;
  ft_argv_print(args);  	
	
	printf("add of cmd %p \nadd of cmd %p \n", cmd, args);

  /*
  char *cmd[] = {
  "cd",
  "exit",
  "help"
  };

  int (*builtin_func[]) (char **) = {
  &cmd_cd,
  &cmd_exit
  };
  */
 
  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  while(i < len_num_builtins(cmd)){
  //while(i < lsh_num_builtins(cmd)){
      if (ft_strcmp(args[0], cmd[i]) == 0) {
        return (builtin_func(cmd[i], args));
        //return (*builtin_func[i])(args);
    }
    
    i++;
  }
        

printf("count : %d \n", len_num_builtins(cmd));
  return cmd_execute(args);
}

int main(void)
{
  // Load config files, if any.

  // Run command loop.
  shell_loop();

  // Perform any shutdown/cleanup.

  return (1);
}