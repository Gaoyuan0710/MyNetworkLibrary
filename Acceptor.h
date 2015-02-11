// =====================================================================================
// 
//       Filename:  Acceptor.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月10日 17时22分37秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef ACCEPTOR_H
#define ACCEPTOR_H


namespace liunian{
class EventLoop;
class Channel;

class Acceptor{
	public:
		Acceptor(EventLoop *loop);
	private:
		EventLoop *loop;
		Channel *acceptChannel;
		int listenFd;

};
}
