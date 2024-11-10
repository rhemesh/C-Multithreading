#include<iostream>
#include<thread>

using namespace std;

/*
//Function Pointer
void func(int val)
{
    while(val-- > 0)
    {
        cout<<val<<" ";
    }
}
int main()
{
    thread t(func,10);

    t.join();
}
*/

/*
//Lambda function
int main()
{

    auto func = [] (int x)
    {
        while(x-- >0)
        {
            cout<<x<<" ";
        }
    };

    thread t(func,15);
    t.join();
}

*/

/*
//Functor (Function Object)

class B
{
    public:
    void operator()(int x)
    {
        while(x++ < 15)
        {
            cout<<x<<" ";
        }
    }
};

int main()
{
    thread t(B(),5);

    t.join();
}
*/
/*
//Non-static member function
class Base
{
    public:
    void func(int x)
    {
        if(x == 10)
        {
            cout<<"X value is 10";
        }
    }
};

int main()
{
    Base b;

    thread t(&Base::func,&b,10);

    t.join();

}
*/

//static member function
class car
{
    public:
    static void color(string str)
    {
        cout<<"color = "<<str;
    }
};

int main()
{
    thread t(&car::color,"White");

    t.join();

    return 0;

}


/*
There are fMultiple types to create a thread,They are:
1.Function pointer
2.Lambda function
3.Functor (Function object)
4.non-static member function and,
5.static member function

*/