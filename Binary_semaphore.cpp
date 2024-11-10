#include<iostream>
#include<semaphore>
#include<thread>
#include<chrono>

using namespace std;

std::binary_semaphore smmaintothread{0},smthreadtomain{0};


void func()
{
    smmaintothread.acquire();

    cout<<"[thread]got signal"<<endl;

    cout<<"Inside thread"<<endl;

    std::this_thread::sleep_for(chrono::seconds(3));

    cout<<"[thread]sent a signal "<<endl;

    smthreadtomain.release();

}

int main()
{
    thread t(func);

    cout<<"[main] sent the signal"<<endl;

    smmaintothread.release();

    smthreadtomain.acquire();

    cout<<"[main]got the signal"<<endl;

    t.join();
     
}

//This is an binary semaphore.
//Semaphores are used to synchronize and notify 
//they use acquire and release to lock and unlock
//starting it will blocked ie 0.
//std::binary_semaphore supports from c++ 20.
