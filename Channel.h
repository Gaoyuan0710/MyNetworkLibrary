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

#ifndef CHANNEL_H 
#define CHANNEL_H

#include <iostream>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

#include "EventLoop.h"

namespace liunian{
class Channel : boost::noncopyable{
	public:
		typedef boost::function<void ()> EventCallBack;
		Channel(EventLoop *loop, int sockfd);
		void handleEvent();
	private:


};
}
#endif
