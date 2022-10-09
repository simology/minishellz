#include "minishell.h"

/*
char *builtin_str[] = {
  "cd",
  "exit"
};
*/
char **builtin_str(void)
{
    char *cmd;
    char **str;
    cmd = "cd exit";
    str = ft_split(cmd, (char)SPACE_DELM);
    return str;    
}

int len_num_builtins(char **builtin_str) {
  //return sizeof(builtin_str()) / sizeof(char *);
  int i;
  i = 0;
  while(builtin_str[i]){
    i++;
  }
  return (i);
}

/*
  Builtin function implementations.
*/
int cmd_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } 
  else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int cmd_exit(char **args)
{
  return 0;
}