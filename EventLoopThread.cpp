// =====================================================================================
// 
//       Filename:  EventLoopThread.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月14日 19时50分42秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "EventLoopThread.h"
#include "EventLoop.h"

#include <boost/bind.hpp>

using namespace liunian;

EventLoopThread::EventLoopThread()
		:loop(NULL),
		quit(false),
		thread(boost::bind(&EventLoopThread::threadFunc, this)),
		mutex(),
		condition(mutex)
{}
EventLoopThread::~EventLoopThread()
{
	quit = true;
	loop->quit();
	thread.join();
}

EventLoop * EventLoopThread::startLoop(){
	thread.start();
	

	std::cout << "Thread  sssss " << std::endl;

	{
		MutexLockGuard lock(mutex);
		while(loop == NULL){
			std::cout << "hshh" << std::endl;
			condition.wait();
		}
	}

	std::cout << " Return " << std::endl;

	return loop;
}

void EventLoopThread::threadFunc(){
	EventLoop loop_;

	{
		MutexLockGuard lock(mutex);
		loop = &loop_;
		condition.notify();
	}

	std::cout << "Enter Loop" << std::endl;
	loop_.loop();
}
