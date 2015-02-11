// =====================================================================================
// 
//       Filename:  testReactor_v1.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月11日 23时17分47秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "../Channel.h"
#include "../EventLoop.h"
#include "../CurrentThread.h"


#include <stdio.h>
#include <sys/timerfd.h>

using namespace liunian;

EventLoop* g_loop;

void timeout()
{
  printf("Timeout!\n");
  g_loop->quit();
}

int main()
{
  EventLoop loop;
  g_loop = &loop;

  int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  Channel channel(&loop, timerfd);
  channel.setReadCallBack(timeout);
  channel.enableReading();

  struct itimerspec howlong;
  bzero(&howlong, sizeof howlong);
  howlong.it_value.tv_sec = 5;
  ::timerfd_settime(timerfd, 0, &howlong, NULL);

  loop.loop();

//  ::close(timerfd);
}

