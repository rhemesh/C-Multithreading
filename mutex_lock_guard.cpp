#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m;
int count  = 0;
void func(int threadnum,int loopcount)
{
    std::lock_guard<mutex> lock(m);
    for(int i=0;i<loopcount;i++)
    {
        count++;
        cout<<"Thread "<<threadnum<<" Count = "<<count<<endl;
    }
}

int main()
{
    thread t1(func,1,10);
    thread t2(func,2,10);

    t1.join();
    t2.join();

    return 0;
}