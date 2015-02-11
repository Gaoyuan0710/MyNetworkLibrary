// =====================================================================================
// 
//       Filename:  Channel.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月27日 22时49分08秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <sys/epoll.h>

#include "EventLoop.h"
#include "Channel.h"

using namespace liunian;

Channel::Channel(EventLoop *loop, int socketfd)
		:loop(loop),
		socketfd(socketfd),
		events(0),
		revents(0),
		index(-1),
		readCallBack(NULL),
		writeCallBack(NULL),
		errorCallBack(NULL)
{
	
}
void Channel::setRevents(int revents){
	this->revents = revents;
}
void Channel::handleEvent(){
	if (revents & EPOLLIN){
		if (readCallBack){
			readCallBack();
		}
	}
	if (revents & EPOLLOUT){
		if (writeCallBack){
			writeCallBack();
		}	
	}
}
void Channel::enableReading(){
	events |= EPOLLIN;
	update();
}
void Channel::enableWriting(){
	events |= EPOLLOUT;
	update();
}
void Channel::update(){
	loop->updateChannel(this);
}
void Channel::setIndex(int index){
	this->index = index;
}
int Channel::getIndex(){
	return index;
}
int Channel::getEvents(){
	return events;
}

