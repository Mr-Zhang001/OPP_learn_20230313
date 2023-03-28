#ifndef __OOP1_H__
#define __OOP1_H__

struct controller_vtbl;


//属性
typedef struct 
{
    int input;
    int output;
    int P_parameter, I_parameter, D_parameter;
    int Sum_error;
    int Last_error;

    struct controller_vtbl *vptr;  
    /* data */
}controller, *Pcontroller;

//方法，通过定义函数指针指向需要实现方法的指针
typedef struct controller_vtbl
{
    controller * (*Init_controller)(void);   //return a point
    void         (*Del_controller)(controller * const Me);
    controller   (*Get_controller)(const controller * const Me);
    void         (*Set_controller)(controller * const Me, int P, int I, int D);
    int          (*Out_controller)(controller *const Me, int input);
}controller_vtbl, *Pcontroller_vtbl;

    controller * Init_controller(void);   //return a point
    void         Del_controller(controller * const Me);
    controller   Get_controller(const controller * const Me);
    void         Set_controller(controller * const Me, int P, int I, int D);
    int          Out_controller(controller *const Me, int input);


#endif
