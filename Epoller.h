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

#ifndef EPOLLER_H
#define EPOLLER_H

#include <iostream>
#include <sys/epoll.h>
#include <vector>

#include "EventLoop.h"
#include "Channel.h"

using std::vector;

namespace liunian{
class Epoll{
	public:
		typedef vector <struct epoll_event> EventList;
		typedef vector <Channel *> ChannelList;
		
		Epoll(EventLoop *loop);
		~Epoll();
		void poll(ChannelList *channelList);


		bool updateChannel(Channel *channel);
		bool removeChannel(Channel *channel);
		void fillActiveChannels(int numEvents, 
					ChannelList *channelList) const;
	private:
		int epollFd;
		EventList events;
};
}
#endif
