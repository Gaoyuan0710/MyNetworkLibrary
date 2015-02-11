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

#include "EventLoop.h"
#include "Channel.h"
#include "Epoller.h"
#include "CurrentThread.h"

using namespace liunian;
using namespace CurrentThread;

using std::cout;
using std::endl;

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
		:loopFlag(false),
		epoll(new Epoll(this)),
		threadId(CurrentThread::tid())
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
void EventLoop::quit(){
	loopFlag = false;
}
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
