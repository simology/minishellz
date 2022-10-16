#include "demo.h"
/*
ls
ls -l
ls -l | wc -l
ls -l | wc -l >> test.txt
ls -l | grep -s test | wc -l
echo aaa > file.txt
echo "hello"
echo hello

detect operator 
1 pipe
2 red

*/
int operator_detector(char *cmd, char *operator){
    int i;
    i = 0;
    while(cmd[i]){
        if(operator[0] && operator[1]){
            if(cmd[i] == operator[0] && cmd[i + 1] == operator[1]){
            return (1);
            }          
        }
        else{
            if(cmd[i] == operator[0]){
                if(cmd[i + 1] == operator[0]){
                    return(0);
                }
                else {
                return (1);
                }
            }
        }
        i++;
    }
    return (0);
}
int cmd_parser(){
return(0);
}
int main(void){
    char *ex = "ls -l | grep -s test | wc -l < file.txt";
    t_config config;
    config.i = 0;
    printf("val op %d \n", operator_detector(ex, "<"));
    printf("val : %s \n", ex);
    return (0);
}