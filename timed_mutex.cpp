#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

timed_mutex m;

int Amount  = 0;
/*
//try_lock_for()
void Increment(int i)
{
    if(m.try_lock_for(chrono::seconds(1)))
    {
        ++Amount;
        std::this_thread::sleep_for(chrono::seconds(1));
        cout<<"Thread "<<i<<"Entered"<<endl;
        m.unlock();
    }
    else
    {
        cout<<"Thread "<<i<<"Could not get the lock"<<endl;
    }
}
*/

//try_lock_until()
void Increment(int i)
{
    auto now = std::chrono::steady_clock::now();
    if(m.try_lock_until(now + chrono::seconds(2)))
    {
        ++Amount;
        std::this_thread::sleep_for(chrono::seconds(1));
        cout<<"Thread "<<i<<"Entered"<<endl;
        m.unlock();
    }
    else
    {
        cout<<"Thread "<<i<<"Could not get the lock"<<endl;
    }
}

int main()
{
    thread t1(Increment,1);
    thread t2(Increment,2);

    t1.join();
    t2.join();

    cout<<"Amount  = "<<Amount<<endl;

    return 0;

}

//we have used timed_mutex here,what ever time we specify in the timed mutex it will wait till that time for lock() if itgets the lock it return true or else false.