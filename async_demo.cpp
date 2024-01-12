#include<future>
#include<iostream>

/*
A  B  C
This are the tasks I want to do

Option 1(Single Thread Multithread)::one after the other.Always complete one thing before
          starting the next task
Option 2(Multithread)::I will complete all the tasks in such a way that I "Practically start all of them at the same time"
          but keep juggling them based on some criteria""here Criteria ==conditions"
Option 3(Parallel execution)::Map number of tasks amongst number of avialable "workers"[threading but check number
          of cores first]Conditions applicable ::tasks should be independent 
Option 4(Asynchronous Execution)::Start a task.Either delegate to another worker or do it yourself  aFter sometime
         If someone else is doing a task,monitor it,wait for their work to be done,
         take follow -up actions accordingly
*/

/*
2 Tasks
Calculate factorial of 5
Calculate Square of a number given by the user 

*/

int square(std::future<int>& ft)
{ 
    std::this_thread::sleep_for(std::chrono::seconds(2));  
    std::cout<<"Hello From Square! "<<"\n";
    int number=ft.get();
    return number*number;
}
int factorial(int number)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));  
    if(number<0)
    {
        throw std::runtime_error("Negative number error!");
    }
    else if(number==0||number==1)
    {
        return 1;
    }
    else{
        return number*factorial(number-1);
    }
}


int main()
{
    //Step 1:make a promise to provide input
    std::promise<int>pr;
    //step 2:A future linked to the promise
    std::future<int> ft=pr.get_future();
/*
OS: LAunch Square(if possible as a new thread)

*/

    std::future<int>result_ft=std::async(std::launch::async,&square,std::ref(ft));
    int val=0;
    std::cout<<"Enter a number:  "<<"\n";
    std::cin>>val;
    pr.set_value(val);
    std::cout<<factorial(5);
    std::cout<<"Result of Square is: "<<result_ft.get()<<"\n";
}

/*
client server architecture

future promise model
square calculation 
Main needs to delegate the task of square calculation

---->A new thread for square 

*/






