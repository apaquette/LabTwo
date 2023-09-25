#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, std::shared_ptr<int> threadCount){

  std::cout << "first\n";
  mutexSem->Wait();
  *threadCount -= 1;
  mutexSem->Signal();
  
  if(*threadCount == 0) barrierSem->Signal();
  barrierSem->Wait();

  std::cout << "second\n";
  barrierSem->Signal();
}


int main(void){
  std::shared_ptr<Semaphore> mutexSem = std::make_shared<Semaphore>(1);
  std::shared_ptr<Semaphore> barrierSem = std::make_shared<Semaphore>(0);
  std::shared_ptr<int> threadCount = std::make_shared<int>(5);

  /*!< An array of threads*/
  std::vector<std::thread> threadArray(*threadCount);
  /*!< Pointer to barrier object*/

  for(unsigned long int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,mutexSem,barrierSem,threadCount);
  }

  for(unsigned long int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
