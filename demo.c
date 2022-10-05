#include "minishell.h"

int main(void)
{
    char str[] = "Hell wolrd ciao";
    char **dd;
    dd = ft_split(str, ' ');
    printf("val : %s \n", dd[1]);
}