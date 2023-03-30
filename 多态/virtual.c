struct Base_skill_vtabl;   //基类函数表
struct Child_skill_vtabl;  //子类


/**************************************************************/
/*基类属性*/
typedef struct 
{
    char name[10];  //名字
    int Heal_value; //健康值
	/*函数表指针，C++如果使用的virtual关键词，虚化了称为虚指针，指向函数行为表*/
    struct Base_skill_vtabl const *vptr;
}Base_Pets;

/*函数行为表，C++如果使用的virtual关键词，称为虚表*/
struct Base_skill_vtabl
{
    int (*illet_skill)(Base_Pets * const Me);  //
    int (*ordinary_skill)(void * const Me);    //
};

/**************************************************************/



/**************************************************************/
/*子类属性*/
typedef struct 
{
	/*继承基类属性*/
    Base_Pets *base_pet;     //   
	/*自己的属性*/
	int Magic_value;
    struct Child_skill_vtabl const *vptr;
}Child_Pets;

struct Child_skill_vtabl
{
    int (*rice_skill)(Child_Pets* const Me);
    int (*ordinary_skill)(void * const Me);
};

/*********************************************************/

/*virtual -> 普通函数  ->多态函数*/
/*普通函数*/
int Rich_skill(Child_Pets* const Me);
int Illet_skill(Base_Pets * const Me);
int Child_Ordinary_skill(void * const Me);
int Base_Ordinary_skill(void * const Me);

/*多态函数*/
/*通过传参的不同，实现多态*/
int Ordinary_skill(void * const Me);

/*********************************************************/


//构造基类
Base_Pets * Ctor_base_Pets(char *name)
{  
    Base_Pets *ptr;

    struct Base_skill_vtabl *table;
    /*分配空间*/
    ptr=(Base_Pets *)malloc(sizeof(Base_Pets));

    table=(struct Base_skill_vtabl *)malloc(sizeof(struct Base_skill_vtabl));    
    //清零
    memset(ptr,0,sizeof(struct Base_skill_vtabl));
    
    strcpy(ptr->name,name);

    ptr->vptr=table;

    table->illet_skill=&Illet_skill;
    table->ordinary_skill=&Base_Ordinary_skill;  //实现了替换

    printf("create Base_Pets class\n");
    return ptr;

}
//析构对象
void Del_Base_Pets(Base_Pets * const Me)
{

    printf("Destroy Base_Pets\n");
    if(Me!=NULL) 
    {
        free((void *)Me->vptr);
        free(Me);
    }
}

/*********************************************************/


//构造子类
Child_Pets *Ctor_Child_Pets(char *name,int magic_value)
{  
 
    Child_Pets *ptr;

    struct Child_skill_vtabl *table;
    /*分配空间*/
    ptr=(Child_Pets *)malloc(sizeof(Child_Pets));
    table=(struct Child_skill_vtabl *)malloc(sizeof(struct Child_skill_vtabl)); 

    //清零
    memset(ptr,0,sizeof(struct Child_skill_vtabl));
    
    ptr->base_pet=Ctor_base_Pets(name);  //子类继承基类
    ptr->Magic_value=10;

    ptr->vptr=table;                                          

    table->rice_skill=&Rich_skill;
    table->ordinary_skill=&Child_Ordinary_skill;

    printf("create Child_Pets class\n");   
    return ptr;
}

//删除对象/析构对象
void Del_Child_Pets(Child_Pets * const Me)
{

    printf("Destroy Child_Pets\n");

    if(Me!=NULL) 
    {
        Del_Base_Pets(Me->base_pet);
        free((void *)Me->vptr);
        free(Me);
    }
}

/*********************************************************/



int Rich_skill(Child_Pets* const Me)
{
    printf("use the rich skill\n");
    return 1;
}

int Illet_skill(Base_Pets * const Me)
{
    printf("use the illet skill\n");
    return 1;
}

/*调用接口函数，也就调用函数指针*/
//这个inline   是个啥意思
//答案：这个inline,内联函数修饰符， 这个Oridinary_skill()就是内联函数。
//内联函数有着函数可以方便被重复调用的优点，也有能让函数运行效率大大提高的优点，
//但是它也不是完美无瑕，也有其弱点，官方说法就是有其局限性
//说白了， inline内联函数，就是一种时间换空间的策略。



//韦东山项目里面设置 网络处理函数用的就是这个原理，return set_netProcess()
inline int Ordinary_skill(void * const Me)
{
	/*将传进来的指针，强制转换为子类  ，为什么此刻强制转换为子类呢，因为子类大，够地方
	如果Me是基类，则返回Base
    这里仅仅是实现调用的操作*/
    Child_Pets * const _Me=(Child_Pets *)Me;  
    return (_Me->vptr->ordinary_skill(Me));  //返回子类 虚拟函数表中的oridinary_skill()
}

/*这里是精髓，通过强制指针转换来达到访问不同对象的目的*/
int Base_Ordinary_skill(void * const Me)
{
    /*指针显示转换，就可以传入同一对象的指针，访问不同对象的内容*/
    Base_Pets const * const _Me=(Base_Pets * const)Me;
    printf("Base_Pets use Ordinary_skill,without magic\r\n");
    return 0;
}
/*这里是精髓，通过强制指针转换来达到访问不同对象的目的*/
int Child_Ordinary_skill(void * const Me)
{
    /*指针显示转换，就可以访问不同对象的内容*/
    Child_Pets const * const _Me=(Child_Pets * const)Me;
    
    printf("Child_Pets use Ordinary_skill,magic val is %d\r\n",_Me->Magic_value);
    
    return 0;
}

int main()
{
    Child_Pets *test;  //创建子类对象指针

    test=Ctor_Child_Pets("child",10);  //创建对象

    /*普通调用*/
    printf("samlpe function \r\n");
    test->base_pet->vptr->illet_skill(test->base_pet);  //子类继承基类，然后调用基类技能illet_skill()
    test->vptr->rice_skill(test);                       //子类自己的技能
    test->vptr->ordinary_skill(test);					//子类自己的技能
    printf("polymorphic function \r\n");
    
    /*多态调用*/
	//采用内联，将函数实体直接嵌入过来
    Ordinary_skill(test);//传入子类指针
    Ordinary_skill(test->base_pet);//传入基类指针

    Del_Child_Pets(test);

    system("pause");

}

/*  运行结果
子类构造：
create Base_Pets class
create Child_Pets class
普通调用：
samlpe function
use the illet skill
use the rich skill
Child_Pets use Ordinary_skill,magic val is 10

多态调用：
polymorphic function
Child_Pets use Ordinary_skill,magic val is 10
Base_Pets use Ordinary_skill,without magic
子类析构：
Destroy Child_Pets
Destroy Base_Pets
Press any key to continue . . .
*/

