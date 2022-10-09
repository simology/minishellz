#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#define SPACE_DELM ' '

char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int     cmd_execute(char **args);
int     cmd_prepare(char **args);

int     cmd_cd(char **args);
int     cmd_exit(char **args);



int len_num_builtins(char **builtin_str);
char **builtin_str(void);
#endif