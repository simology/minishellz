#include "minishell.h"

int main(void)
{
    char **test;
    test = builtin_str();
    int i = 0;
    while(test[i]){

    printf("val : %s \n", test[i]);
    i++;
    }
    printf("val : %d \n", len_num_builtins(test));
    
}