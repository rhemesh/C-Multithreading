#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

mutex m1,m2;

void thread1_func(void)
{
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m2.lock();
    cout<<"Thread 1"<<endl;
    m1.unlock();
    m2.unlock();
}

void thread2_func(void)
{
    m2.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m1.lock();
    cout<<"Thread 2"<<endl;
    m2.unlock();
    m1.unlock();
}

int main()
{
    thread t1(thread1_func);
    thread t2(thread2_func);

    t1.join();
    t2.join();

    return 0;

}

//Here we get deadlock because each threads are locked in different functions.