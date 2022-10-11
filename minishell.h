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
#include <sys/types.h>
#define SPACE_DELM ' '

typedef struct s_config
{
    char    **builtin_cmd;
    char    **args_cmd;
    int     builtin_len;
    char    *banner;
} t_config;


char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);


char    *read_line(t_config *config);

int     cmd_execute(t_config *config);
int     cmd_prepare(t_config *config);

int     cmd_cd(char **args);
int     cmd_exit(char **args);

void ft_argv_print(char **argv);
int lsh_num_builtins(char **builtin_str);
int len_num_builtins(char **builtin_str);
char **builtin_str(void);
int  builtin_func(char *cmd, char **args);


void shell_init(t_config *config);
void shell_loop(t_config *config);
#endif