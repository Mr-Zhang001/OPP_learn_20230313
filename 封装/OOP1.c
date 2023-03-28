#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include "OOP1.h"



//构造
controller *Init_controller(void)
{
    Pcontroller ptcontroller;
    Pcontroller_vtbl ptcontroller_vtbl;

    ptcontroller = (Pcontroller)malloc(sizeof(controller));

    ptcontroller_vtbl = (Pcontroller_vtbl)malloc(sizeof(controller_vtbl));

    memset(ptcontroller,0,sizeof(controller));

    ptcontroller_vtbl->Init_controller = &Init_controller;
    ptcontroller_vtbl->Del_controller = &Del_controller;
    ptcontroller_vtbl->Set_controller = &Set_controller;
    ptcontroller_vtbl->Get_controller = &Get_controller;
    ptcontroller_vtbl->Out_controller = &Out_controller;

    ptcontroller -> vptr = ptcontroller_vtbl;

    return ptcontroller;
}

//析构
void Del_controller(controller * const Me)
{
    if(Me != NULL)
    {
        free(Me -> vptr);
        free(Me);
        printf("Del_controller is running!\r\n");
    }
}

//设置参数
void Set_controller(controller * const Me, int P, int I, int D)
{
    Me->P_parameter = P;
    Me->I_parameter = I;
    Me->D_parameter = D;
}

controller Get_controller(const controller * const Me)
{
    return (*Me);
}

int Out_controller(controller * const Me, int input)
{
    float iIncpid=0;
    int now_error = input;
    Me->Sum_error+=input;

    if(Me->Sum_error >500)
    {
        Me->Sum_error = 500;
    }
    if(Me->Sum_error < -500)
    {
        Me->Sum_error = -500;
    }

    Me->output = Me->P_parameter * input
        +Me->I_parameter * Me->Sum_error
        +Me->D_parameter * (now_error-Me->Last_error);

    Me->Last_error=now_error;
    return(Me->output);   //返回计算值

}


int main()
{
    controller *test;
    controller read_val;

    //构造，创建一个对象
    test=Ctor_controller();

    //设置对象的值 
    test->vptr->Set_controller(test,1,1,1);
    
    //查看对象的值
    read_val=test->vptr->Get_controller(test);

    printf("对象 P= %d I=%d D=%d \r\n",read_val.P_parameter,read_val.I_parameter,read_val.D_parameter);

    //调用控制器一次：
    printf("控制器输出=%d \r\n",test->vptr->Out_controller(test,100));
    
    //删除/销毁一个对象
    test->vptr->Del_controller(test);
}