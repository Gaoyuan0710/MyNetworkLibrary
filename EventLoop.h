// =====================================================================================
// 
//       Filename:  EventLoop.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月27日 22时14分25秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <iostream>
#include <pthread.h>
#include <boost/noncopyable.hpp>

namespace liunian{
class EventLoop : boost::noncopyable{
	public:
		EventLoop();
		~EventLoop();
		void loop();
		bool isInLoopThread() const{
			return (this->threadId == pthread_self());
		}
	private:
		bool loopFlag;
		const pid_t threadId;
};
}
#endif
