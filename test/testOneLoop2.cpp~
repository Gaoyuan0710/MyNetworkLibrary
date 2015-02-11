// =====================================================================================
// 
//       Filename:  testOneLoop.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月11日 18时24分58秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "../EventLoop.h"
#include "../Thread.h"
#include "../CurrentThread.h"

#include <stdio.h>
#include <assert.h>
using namespace liunian;

void threadFunc()
{
  printf("threadFunc(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());

 	EventLoop loop;
  loop.loop();
}

int main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());

  EventLoop loop;

  Thread thread(threadFunc);
  thread.start();

  loop.loop();
  pthread_exit(NULL);
}

