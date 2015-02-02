// =====================================================================================
// 
//       Filename:  Thread.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月02日 10时42分38秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <pthread.h>
#include <string>

using std::string;

namespace liunian{
class Thread : boost::noncopyable{
		typedef boost::function<void ()> ThreadFunc;
	private:
		static int currentNum;
		bool isStart;
		bool isJoin;
		pthread_t pthreadId;
		boost::shared_ptr<pid_t> tid;
		ThreadFunc func; 
		string threadName;
		static void * startThread(void * thread);
	public:
		explicit Thread(const ThreadFunc &, const string &name = string());
		~Thread();
		bool start();

		int join(pthread_t pthread);
		pid_t getThreadId() const {
			return pthreadId;
		}
		string getThreadName() const{
			return threadName;
		}
		static int getTotalThreadNum(){
			return currentNum;
		}
};
}

#endif
