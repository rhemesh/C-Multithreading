#include<iostream>
#include<thread>
#include<mutex>
#include<future>

using namespace std;

typedef long long int uli;

void FindOddsum(promise<uli> Oddsumpromise,uli start,uli end)
{
    uli Oddsum1 = 0;
    for(uli i =start;i<end;i++)
    {
        if(i&1 == 1)
        {
            Oddsum1 += i;
        }
    }
    Oddsumpromise.set_value(Oddsum1);
}

int main()
{
    uli start = 0, end = 19000000;
    std::promise<uli> Oddsum;
    std::future<uli> futureoddsum = Oddsum.get_future();
    thread t(FindOddsum,std::move(Oddsum),start,end);

    cout<<"Waiting for the result.\n"<<endl;
    cout<<"Total Odd sum = "<<futureoddsum.get()<<endl;
    cout<<"Finished"<<endl;

    return 0;

}



//we can access local member of a function using thread promise and future