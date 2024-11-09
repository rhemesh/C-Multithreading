#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m;

int count = 0;

void func(int t,int loopcount)
{
    std::unique_lock<mutex>  ul(m,defer_lock);
    ul.lock();
    for(int i=0;i<loopcount;i++)
    {
        ++count;
        cout<<"Thread "<<t<<" Count = "<<count<<endl;
    }
}

int main()
{
    thread t1(func,1,20);
    thread t2(func,2,10);

    t1.join();
    t2.join();

    return 0;

}

//It works same as lock_guard but this one has some more features added in.unlike lock_guard in unique_lock we can lock() and unlock() whenever we want/
//Whenever we create object for the unique lock it qutomatically lock the thread and if we don't want to do so then use defer and ypu can lock after sometime.
//we can use conditional variable in unique lock();

/*
>It is an mutex ownership wrapper.It has a different locking stratagies they are:
	.defer_lock()  ->Do not aquire ownership of the mutex
	.try_to_lock() ->try to aquire ownership of the mutex without blocking
	.adopt_lock()  ->assume that calling thread already has the ownership
->It supports Time constrained attempts at locking (try_lock_for,try_lock_until)
*/