
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


char *read_line(void)
{
  char *line;
  line = readline( "minishell> " );
  if (line == NULL)
    return (0);
  else
    return (line);
}

void shell_loop(void)
{
  char *line;
  //char **args;
  int status;

  status = 1;

  while(status) 
  {
    line = read_line();
    //args = lsh_split_line(line);
    //status = lsh_execute(args);

    //free(line);
    //free(args);
    printf("val : %s \n", line);
  }
}

/*
int main()
{

    printf("val : %s \n", read_line());
    return 0;
}
*/
int main(void)
{
  // Load config files, if any.

  // Run command loop.
  shell_loop();

  // Perform any shutdown/cleanup.

  return (1);
}