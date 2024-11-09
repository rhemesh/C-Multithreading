#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

condition_variable cv;

mutex m1;
int balance  = 0;
void addMoney(int amount)
{
    lock_guard<mutex> lg(m1);
    balance += amount;
    cout<<"Amount "<<amount<<" added to total balance"<<endl;
    cv.notify_one();
}

void WithdrawMoney(int amount)
{
    unique_lock<mutex> ul(m1);
    cv.wait(ul,[] {return (balance!=0) ? true : false;});
    if(balance >= amount)
    {
        balance -=amount;
        cout<<"Amount "<<amount<<" deducted from the total balance"<<endl;
    }
    else{
        cout<<"Insufficient balance,withdraw failed"<<endl;
    }

    cout<<"Total balance remaining = "<<balance<<endl;
}

int main()
{
    int add;
    printf("Enter the amount to add to bank account:\n");
    scanf("%d",&add);
    int draw;
    printf("Enter the amount to withdraw from the account balance:\n");
    scanf("%d",&draw);
    thread t1(addMoney,add);
    thread t2(WithdrawMoney,draw);

    t1.join();
    t2.join();

    return 0;

}

//Here we are trying to add and remove from the account using condition variable .
//Once oney is added it is getting notified to the withdraw function using cv that i have added amount youstart your work .
