#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

mutex m;
int count = 0;
void Counttill100000()
{
    for(int i=0;i<100000;i++)
    {
        if(m.try_lock())
        {
            ++count;
        }
        m.unlock();
    }
}

int main()
{
    std::thread t1(Counttill100000);
    std::thread t2(Counttill100000);

    t1.join();
    t2.join();

    cout<<"Count  = "<<count<<endl;
    
    return 0;

}//try_lock() is an non-blocking state because if it not got lock() then it will not wait for the previous one to finish its work,It just returns control back to the main.

//Here if we use try_lock() output will not be 200000 and if we use lock() it will be 200000 because in lock() it will wait until the previous thread finishes it work and starts executing.