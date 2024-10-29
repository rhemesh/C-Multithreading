#include<iostream>
#include<thread>
#include<semaphore>

using namespace std;

std::binary_semaphore signal_to_produce{1},signal_to_consume{0};
#define buffer_size 5
int buff[buffer_size];

void producer(void)
{
    signal_to_produce.acquire();
    while(1)
    {
        cout<<"Produced  = ";
        for(int i=0;i<buffer_size;i++)
        {
            buff[i] = i*i;
            cout<<buff[i]<<" ";
        }
    }
    cout<<endl;
    signal_to_consumer.release();
}

void consumer(void)
{
    signal_to_consume.acquire();
    while(1)
    {
        cout<<"Consumed = ";
        for(int i=buffer_size;i>0;i--)
        {
            cout<<buff[i]<<" ";
        }
    }
    cout<<endl;
    signal_to_producer.release();
}

int main()
{
    thread producer_thread(producer);
    thread consumer_thread(consumer);

    cout<<"[main] got the thread"<<endl;

    producer_thread.join();
    consumer_thread.join();

    return 0;
}