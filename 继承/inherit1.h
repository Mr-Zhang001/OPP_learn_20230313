#ifndef __INHERIT1_h__
#define __INHERIT1_h__

/*函数行为表， C++中称为虚表*/
struct Base_skill
{
    int (*illet_skill)(Base_Pets * const Me);
};

typedef struct 
{
    char name[10];
    int  Heal_value;
    //指向函数行为表
    struct Base_skill const *vptr;
}Base_Pets;

struct Child_skill
{
    int (*rice_skill)(Child_Pets * const Me);
};

typedef struct
{
    //来自继承
    Base_Pets base_pet;
    /*自己的属性*/
    int Magic_value;
    struct Child_skill const *vptr;
}Child_Pets;

int Rich_skill(Child_Pets * const Me);
int Illet_skill(Base_Pets * const Me);




#endif