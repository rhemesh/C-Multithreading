#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m1,m2;


void func(int t)
{
    std::scoped_lock lock(m1,m2);

    cout<<"Thread "<<t<<endl;
}
int main()
{
    int numthreads = 5;
    thread threads[numthreads];

    for(int i=0;i<numthreads;i++)
    {
        threads[i] = std::thread(func,i);
    }

    for(int i=0;i<numthreads;i++)
    {
        threads[i].join();
    }

    return 0;

}