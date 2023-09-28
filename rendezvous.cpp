#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, std::shared_ptr<int> threadCount){
  std::cout << "first\n";
  mutexSem->Wait();
  --(*threadCount);
  
  
  if(*threadCount == 0) {
    mutexSem->Signal();
    barrierSem->Signal();//1 signal
  }else{
    mutexSem->Signal();
    barrierSem->Wait(); //N-1 waits
  }

  std::cout << "second\n";
  mutexSem->Wait();
  ++(*threadCount);
  

  if(*threadCount < 4) barrierSem->Signal();//N-2 signals
  mutexSem->Signal();
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
