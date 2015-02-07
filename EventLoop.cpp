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
#include "EventLoop.h"

using namespace liunian;

EventLoop::EventLoop()
		:loopFlag(false)
{
	
}
EventLoop::~EventLoop(){

}
void EventLoop::loop(){
	loopFlag = true;

	while (loopFlag){
		sleep(100);
		loopFlag = false;
	}
}
