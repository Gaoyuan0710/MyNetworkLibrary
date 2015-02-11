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

EventLoop* g_loop;

void threadFunc()
{
  g_loop->loop();
}

int main()
{
  EventLoop loop;
  g_loop = &loop;
  Thread t(threadFunc);
  t.start();
  t.join();
}

