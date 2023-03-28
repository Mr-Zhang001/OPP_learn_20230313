#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Base_Pets
{
    public:

    Base_Pets()
    {
        std::cout<<"Create Base_pets"<<std::endl;
    }
    ~Base_Pets()
    {
        cout<<"Del Base_pets"<<endl;
    }

    int Illet_skill(void)
    {
        cout<<"use the illet_skill is running"<<endl;
        return 1;
    }

    char name[10];
    int Heal_value;
};

class Child_Pets:public Base_Pets
{
    public:
    //方法
    int Rich_skill(void)
    {
        cout<<"use the rich skell"<<std::endl;
        return 1;
    }

    Child_Pets()
    {
        std::cout<<"Creat Child_Pets"<<std::endl;
    }

    ~Child_Pets()
    {
        std::cout<<"Del Child_Peets()"<<std::endl;
    }

    //属性
    int Magic_value;
};

void test()
{
    Child_Pets test;
    test.Rich_skill();
    test.Illet_skill();
}

int main()
{
    test();
    system("pause");
}



