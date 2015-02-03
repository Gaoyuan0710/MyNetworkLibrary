// =====================================================================================
// 
//       Filename:  ThreadPool.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月02日 19时56分36秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <boost/bind.hpp>
#include <stdio.h>

#include "ThreadPool.h"

using namespace liunian;

ThreadPool::ThreadPool(const string &name)
		:mutex(),
		notEmpty(mutex),
		notFull(mutex),
		threadPoolName(name),
		maxQueueSize(0),
		isRunning(false)
{

}
ThreadPool::~ThreadPool(){
	if (isRunning){
		stop();
	}
}
void ThreadPool::start(int numThreads){
	isRunning = true;

	threads.reserve(numThreads);

	for (int i = 0; i < numThreads; i++){
		char id[32];
		snprintf(id, sizeof(id), "%d", i + 1);
		threads.push_back(new Thread(boost::bind(&ThreadPool::beginRunning, this), threadPoolName +
						id));
		threads[i].start();
	}
	if (numThreads == 0 && workToDo){
		workToDo();
	}
}
void ThreadPool::stop(){
	{
		MutexLockGuard lock(mutex);
		isRunning = false;
		notEmpty.notigyAll();
	}
	//for_each(threads.begin(), threads.end(), boost::bind(&Thread::join, _1));
}
void ThreadPool::addWork(const Task &task){
	if (threads.empty()){
		task();
	}
	else{
		MutexLockGuard lock(mutex);
		while (isFull()){
			notFull.wait();
		}
		workQueue.push(task);
		notEmpty.notigyAll();
	}
}

ThreadPool::Task ThreadPool::takeWork(){
	MutexLockGuard lock(mutex);

	while (workQueue.empty() && isRunning){
		notEmpty.wait();
	}
	Task task;
	if (!workQueue.empty()){
		task = workQueue.front();
		workQueue.pop();

		if (maxQueueSize > 0){
			notFull.notigyAll();
		}
	}
	return task;
}

bool ThreadPool::isFull() const{
	return maxQueueSize > 0 && workQueue.size() >= maxQueueSize;
}

void ThreadPool::beginRunning(){
	if (workToDo){
		workToDo();
	}

	while (isRunning){
		Task task(takeWork());

		if (task){
			task();
		}
	}
}
