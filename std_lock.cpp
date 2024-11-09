#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

std::mutex m1,m2,m3,m4;

void thread1_func(void)
{
    std::lock(m1,m2);
    std::lock(m3,m4);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"Thread 1"<<endl;
    m1.unlock();
    m2.unlock();
    m3.unlock();
    m4.unlock();
}

void thread2_func(void)
{
    std::lock(m3,m4);
    std::lock(m1,m2);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout<<"Thread 2"<<endl;
    m3.unlock();
    m4.unlock();
    m1.unlock();
    m2.unlock();
}

int main()
{
    thread t1(thread1_func);
    thread t2(thread2_func);

    t1.join();
    t2.join();

    return 0;

}

//If we are using std::lock(m1,m2) it will not create deadlock.


/*
//In std lock,using these we will face deadlock issue
func1:
    std::lock(m1,m2);
    std::lock(m3,m4);
func2:
    std::lock(m3,m4);
    std::lock(m1,m2);

*/

