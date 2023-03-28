#include "stdio.h"
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int input;
    int output;
    int P_parameter,I_parameter,D_parameter;
    int Sum_error; //总偏差
    int Last_error; //上次偏差
    /* data */
}controller;


//初始化构造对象
controller * Init_Controller(void)
{
    controller *temp;
    temp = (controller *)malloc(sizeof(controller));
    memset(temp,0,sizeof(controller));
    return temp;
}

//删除对象
void Del_controller(controller * const Me)
{
    if(Me != NULL)
        free(Me);
}

void Set_Controller(controller * const Me,int P, int I, int D)
{
    Me->P_parameter = P;
    Me->I_parameter = I;
    Me->D_parameter = D;
}

controller Get_Controller(const controller * const Me, int P,int I,int D)
{
    return (*Me);
}

