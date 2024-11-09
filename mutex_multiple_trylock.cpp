#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

mutex m1,m2;

int X=0,Y=0;

void Dosomeworkfor_seconds(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
void IncrementXY(int& XorY,std::mutex &m,const char* dest)
{
    for(int i=0;i<10;i++)
    {
        m.lock();
        ++XorY;
        cout<<dest<<XorY<<endl;
        m.unlock();
        Dosomeworkfor_seconds(1);
    }
}

void ConsumeXY(void)
{
    int Usecount = 10;
    int XplusY = 0;
    while(1)
    {
        int lock_results = std::try_lock(m1,m2);
        if(lock_results == -1)
        {
            if(X!=0 && Y!=0)
            {
                --Usecount;
                XplusY +=X+Y;
                X = 0;
                Y = 0;
                cout<<"XplusY = "<<XplusY<<endl; 
            }
            m1.unlock();
            m2.unlock();
            if(Usecount == 0)
            {
                break;
            }
        }
    }
}

int main()
{
    std::thread t1(IncrementXY,std::ref(X),std::ref(m1), "X = ");
    std::thread t2(IncrementXY,std::ref(Y),std::ref(m2), "Y = ");
    std::thread t3(ConsumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;

}