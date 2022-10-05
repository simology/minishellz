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
  splited = ft_split(line, ' ');
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
    //status = lsh_execute(args);
    //printf("val : %s \n", args[1]);

    free(line);
    //free(args);
  }
}

int main(void)
{
  // Load config files, if any.

  // Run command loop.
  shell_loop();

  // Perform any shutdown/cleanup.

  return (1);
}