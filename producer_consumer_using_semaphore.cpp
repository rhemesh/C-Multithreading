#include<iostream>
#include<thread>
#include<semaphore>
#include<deque>
#include<atomic>

std::deque<int> buffer;
std::atomic<bool> done_producing(false);
using namespace std;

std::binary_semaphore signal_to_produce(1),signal_to_consume(0);

void produce(int val)
{

    while(val > 0)
    {
        signal_to_produce.acquire();
        buffer.push_back(val);
        cout<<"Produced = "<<val<<endl;
        val--;
        signal_to_consume.release();
    }
    done_producing = true;
}

void consume(void)
{
    while(true)
    {
        signal_to_consume.acquire();
        if(buffer.empty() && done_producing)
        {
            break;
        }
        int val = buffer.back();
        buffer.pop_back();
        cout<<"Consumed = "<<val<<endl;
        signal_to_produce.release();

    }

}

int main()
{
    thread t1(produce,10);
    thread t2(consume);

    t1.join();
    t2.join();

    return 0;

}