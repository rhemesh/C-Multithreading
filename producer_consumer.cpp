#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<deque>

using namespace std;

mutex m;
std::condition_variable cv;
std::deque<int> buffer;

bool done  = false;
const unsigned int maxsize = 100;

void producer(int val)
{
    while(val)
    {
        std::unique_lock<mutex> pl(m);
        cv.wait(pl,[] {return buffer.size() < maxsize;});
        buffer.push_back(val);
        cout<<"Produced = "<<val<<endl;
        val--;
        pl.unlock();
        cv.notify_one();
    }
    {
        std::lock_guard<mutex> lg(m);
        done  = true;
    }

    cv.notify_one();
}

void consumer(void)
{
    while(true)
    {
        std::unique_lock<mutex> cl(m);
        cv.wait(cl,[]{return buffer.size() > 0 || done;});
        if(buffer.empty() && done)
        {
            break;
        }
        int val = buffer.back();
        buffer.pop_back();
        cout<<"Consumed  = "<<val<<endl;
        cl.unlock();
        cv.notify_one();

    }
}

int main()
{
    thread t1(producer,20);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;

}


//Producer and consumer problem ->using condition variabled notifying each other process completion 