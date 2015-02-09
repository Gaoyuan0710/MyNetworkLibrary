// =====================================================================================
// 
//       Filename:  Epoller.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月28日 00时11分58秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <vector>
#include <sys/epoll.h>

#include "Epoller.h"

using namespace liunian;
using std::vector;
using std::endl;
using std::cout;

Epoll::Epoll(){
	epollFd = epoll_create(1);

	if (epollFd <= 0){
		cout << "epoll_create error" << endl;
	}
}
Epoll::~Epoll(){
}
void Epoll::poll(vector <Channel *> *channel){
	int fds = epoll_wait(epollFd, 
				&*events.begin(), 
				static_cast<int>(events.size()), 
				-1);

	if (fds == -1){
		cout << "epoll_wait error" << endl;
		return ;
	}
	fillActiveChannels(fds, channel);
}
void Epoll::fillActiveChannels(int numEvents, vector<Channel *> *activeChannels) const{
	for (int i = 0; i < numEvents; i++){
		Channel *channelTemp = static_cast<Channel *> (events[i].data.ptr);
		channelTemp->setRevents(events[i].events);
		activeChannels->push_back(channelTemp);
	}
}
void Epoll::updateChannel(Channel *channel){
	struct epoll_event temp;

	int index = channel->getIndex();

	temp.data.ptr = channel;
	temp.events = channel->getEvents();
	
	int fd = channel->getSocket();

	if (index == -1){
		channel->setIndex(1);
		epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &temp);
	}
	else{
		epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &temp);
	}
}
