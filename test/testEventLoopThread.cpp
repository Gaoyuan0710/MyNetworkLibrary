// =====================================================================================
// 
//       Filename:  testTimerQueue.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月12日 23时20分55秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================
#include "../EventLoop.h"
#include "../EventLoopThread.h"
#include "../CurrentThread.h"

#include <stdio.h>

using namespace liunian;


void runInThread()
{
  printf("runInThread(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());
}

int main()
{
  printf("main(): pid = %d, tid = %d\n",
         getpid(), CurrentThread::tid());

  EventLoopThread loopThread;
  EventLoop* loop = loopThread.startLoop();
  loop->runInLoop(runInThread);
  sleep(1);
  loop->runAfter(2, runInThread);
  sleep(3);
  loop->quit();

  printf("exit main().\n");
}

