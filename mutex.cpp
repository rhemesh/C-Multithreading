#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

std::mutex m;
int count = 0;
void func()
{
    m.lock();
    ++count;
    m.unlock();
}

int main()
{
    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    cout<<"Count = "<<count<<endl;

    return 0;
}

//By using mutex lock and unlock,we can avoid race condition ie. both threads trying to modify the critical section.