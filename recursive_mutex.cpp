#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

recursive_mutex m;

int count = 0;
void recursion(int t,int num)
{
    if(num < 0)
    {
        return;
    }

    m.lock();
    cout<<"Count = "<<count++<<endl;
    recursion(t,--num);
    m.unlock();
    cout<<"Thread unlocked"<<endl;
}

int main()
{
    thread t1(recursion,1,10);
    thread t2(recursion,2,10);

    t1.join();
    t2.join();

    return 0;

}


//Here we have used recursive_mutex to lock the same thread multiple times.