// =====================================================================================
// 
//       Filename:  EventLoop.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月27日 22时14分44秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <assert.h>
#include <sys/eventfd.h>

#include "EventLoop.h"
#include "Channel.h"
#include "Epoller.h"
#include "CurrentThread.h"

using namespace liunian;
using namespace CurrentThread;

using std::cout;
using std::endl;

__thread EventLoop* t_loopInThisThread = 0;


static int createEventfd()
{
  int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0)
  {
      cout << "Failed in eventfd" << endl;
      abort();
    }
  return evtfd;
}

EventLoop::EventLoop()
		:loopFlag(false),
		epoll(new Epoll(this)),
		threadId(CurrentThread::tid()),
		callingPendingFunctors(false),
		timerQueue(new TimerQueue(this)),
		wakeUpFd(createEventfd()),
		wakeupChannel(new Channel(this, wakeUpFd))
{
	cout << "EventLoop Create " << this << "in thread"
		<< threadId << endl;

	if (t_loopInThisThread){
		cout << "Another EventLoop " 
			<< t_loopInThisThread 
			<< "Exits in this thread " << threadId 
			<< endl;
	}
	else{
		t_loopInThisThread = this;
	}
	
}
EventLoop::~EventLoop(){

}
void EventLoop::loop(){

	assertInLoopThread();

	loopFlag = true;

	while (loopFlag){
		activeChannels.clear();
		epoll->poll(&activeChannels);
		for (ChannelList::iterator it =
					activeChannels.begin();
					it != activeChannels.end();
					it++){
			(*it)->handleEvent();
		}
	}
}
//void EventLoop::quit(){
//	loopFlag = false;
//}
void EventLoop::updateChannel(Channel *channel){
	epoll->updateChannel(channel);
}
bool EventLoop::isInLoopThread(){
	return threadId == CurrentThread::tid();
} 

void EventLoop::abortNotInLoopThread(){
	cout << "EventLoop::abortNotInLoopThread - EventLoop " << this << " was created in threadId = "
		<< threadId << "  current thread id  = "
		<< CurrentThread::tid();
}



void EventLoop::quit()
{
  loopFlag = false;

  if (!isInLoopThread())
  {
      wakeup();
    }
}

void EventLoop::runInLoop(const Functor& cb)
{
  if (isInLoopThread())
  {
      cb();
    }
  else
  {
      queueInLoop(cb);
    }
}

void EventLoop::queueInLoop(const Functor& cb)
{
  {
    MutexLockGuard lock(mutex);
    pendingFunctors.push_back(cb);
    }

  if (!isInLoopThread() || callingPendingFunctors)
  {
      wakeup();
    }
}

TimerId EventLoop::runAt(const Timestamp& time, const Functor& cb)
{
  return timerQueue->addTimer(cb, time, 0.0);
}

TimerId EventLoop::runAfter(double delay, const Functor& cb)
{
  Timestamp time(addTime(Timestamp::now(), delay));
  return runAt(time, cb);
}

TimerId EventLoop::runEvery(double interval, const Functor& cb)
{
  Timestamp time(addTime(Timestamp::now(), interval));
  return timerQueue->addTimer(cb, time, interval);
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
  	ssize_t n = ::write(wakeUpFd, &one, sizeof one);
  	
	if (n != sizeof one)
	{
		std::cout << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}
