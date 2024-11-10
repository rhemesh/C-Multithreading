#include<iostream>
#include<thread>
#include<future>

using namespace std;

typedef long long int lli;

lli FindOddsum(int start,int end)
{
    lli Oddsum = 0;
    cout<<"THread Id in main : "<<this_thread::get_id()<<endl;
    for(lli i = start;i<end;i++)
    {
        if(i&1)
        {
            Oddsum += i;
        }
    }
    return Oddsum;
}
int main()
{
    lli start = 0,end = 1900000000;
    //std::future<lli> futureSum = std::async(std::launch::deferred,FindOddsum,start,end);
    std::future<lli> futureSum = std::async(std::launch::async,FindOddsum,start,end);

    cout<<"THread Id in main : "<<this_thread::get_id()<<endl;
    cout<<"Waiting for the result"<<endl;

    cout<<"Sum of Odd Numbers =  "<<futureSum.get()<<endl;

    cout<<"Finished"<<endl;

    return 0;

}

//async is used to run function asynchronously (potentially in different thread) and in async no need of creating promise object.It will give promise to future internally in async.
//Thread creation happens in future async only.
//async has different launching polices
//1.launch::async and 2.launch::diferred
//launch async will create new thread and function runs asynchronously and in launch::diferred it will not create new thread function runs using main thread only