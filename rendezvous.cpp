#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, std::shared_ptr<int> threadCount){

  std::cout << "first\n";
  //put barrier code here
  mutexSem->Wait();
  *threadCount -= 1; //this is not shared, needs to be shared (use shared pointer?)
  mutexSem->Signal();
  
  if(*threadCount == 1) barrierSem->Signal();
  barrierSem->Wait();

  std::cout << "second\n";
  barrierSem->Signal();
}


int main(void){
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  std::shared_ptr<int> threadCount;
  
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
  threadCount=std::make_shared<int>(5);

  /*!< An array of threads*/
  std::vector<std::thread> threadArray(*threadCount);
  /*!< Pointer to barrier object*/

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,mutexSem,barrierSem,threadCount);
  }

  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
