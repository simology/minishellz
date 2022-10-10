#include "minishell.h"

char **builtin_str(void)
{
    char *cmd;
    char **str;
    cmd = "cd exit help";
    str = ft_split(cmd, (char)SPACE_DELM);
    return (str);    
}

int lsh_num_builtins(char **builtin_str) {
  return sizeof(builtin_str) / sizeof(char *);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 - *s2 == 0)
		{
			s1++;
			s2++;
		}
		else
		{
			return (*s1 - *s2);
		}
	}
	return (*s1 - *s2);
}
void ft_argv_print(char **argv)
{
  int i = 0;
  while (argv[i]){
    printf("argv print %s \n", argv[i]);
    i++;
  }
}
int builtin_func(char *cmd, char **args){
  printf("inside : %s \n ", args[0]);
  if (ft_strcmp(cmd, "cd") == 0)
    return (cmd_cd(args));
  else if (ft_strcmp(cmd, "exit") == 0)
    return (cmd_exit(args));
  return (0);
}
int len_num_builtins(char **builtin_str) {
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
  (void)args;
  return 0;
}