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

int cmd_execute(char **args)
{
  pid_t pid;
  pid_t wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh child");
    }
    exit(EXIT_FAILURE);
  } 
  else if (pid < 0) {
    // Error forking
    perror("lsh fork");
  } 
  else {
    // Parent process
    while(!WIFEXITED(status) && !WIFSIGNALED(status))
    {
      wpid = waitpid(pid, &status, WUNTRACED);
    }
  }

  return 1;
}

int cmd_prepare(char **args)
{
  int i;
  char **cmd;
  i = 0;
  cmd = builtin_str();

  /*
  char *builtin_str[] = {
  "cd",
  "exit"
  };
  */

  int (*builtin_func[]) (char **) = {
  &cmd_cd,
  &cmd_exit
  };

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
  printf("val : %s \n", args[0]);
  while(i < len_num_builtins(cmd)){
      if (strcmp(args[0], cmd[i]) == 0) {
        //printf("builtin cmd %s and invoke %s \n", args[0], cmd[i]);
      return (*builtin_func[i])(args);
    }
    i++;
  }

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