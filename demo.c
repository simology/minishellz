#include<stdio.h>
typedef struct s_demo
{
    char a;
    char b;
} t_demo;

void functiona(t_demo *demo)
{
    demo->a = 'Z';
}

void functionb(t_demo *demo)
{
    demo->b = 'H';
}
int main(void)
{
    t_demo demo;
    int x[3][2] = {{0,1}, {2,3}, {4,5}};
    int num[3][4] = {
    {1, 2,  3,  4},
    {5, 6,  7,  8},
    {9, 10, 11, 12}
  };
    int *y;
    y = &num;
    functiona(&demo);
    functionb(&demo);
    printf( "val x %d \n", num[0][3] );
    printf("val y %d \n", y[4]);
    printf("val a : %c \nval b : %c \n", demo.a , demo.b);
    
}