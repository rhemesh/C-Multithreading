#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>


using namespace std;

typedef long long int lli;

lli EvenSum = 0,OddSum = 0;

void FindEvensum(lli start,lli end)
{
    for(lli i = start;i<end;i++)
    {
        if((i&1) == 0)
        {
            EvenSum += i;
        }
    }
}

void FindOddsum(lli start,lli end)
{
    for(lli i=start;i<end;i++)
    {
        if(i&1)
        {
            OddSum += i;
        }
    }
}

int main()
{
    lli start,end; 
    printf("Enter start and end values to get sum of even and odd:\n");
    scanf("%lld %lld",&start,&end);

    thread t1(FindEvensum,start,end);
    thread t2(FindOddsum,start,end);

    t1.join();
    t2.join();

    cout<<"Sum of Even numbers = "<<EvenSum<<endl;
    cout<<"Sum of Odd numbers = "<<OddSum<<endl;

    return 0;

}