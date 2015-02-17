// =====================================================================================
// 
//       Filename:  TcpConnection.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月17日 19时04分03秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <boost/bind.hpp>
#include <iostream>

#include "TcpConnection.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

using namespace liunian;

TcpConnection::TcpConnection(
			EventLoop *loop,
			const std::string&name,
			int sockfd,
			const InetAddress& localAddr,
			const InetAddress& otherAddr)
		:loop(loop),
		name(name),
		state(kConnecting),
		socket(new Socket(sockfd)),
		channel(new Channel(loop, sockfd)),
		localAddr(localAddr),
		otherAddr(otherAddr){
			channel->setReadCallBack(
						boost::bind(&TcpConnection::handleRead, this));
			channel->setWriteCallBack(
						boost::bind(&TcpConnection::handleWrite, this));
			channel->setCloseCallBack(
						boost::bind(&TcpConnection::handleClose, this));
			channel->setErrorCallBack(
						boost::bind(&TcpConnection::handleError, this));
		}
TcpConnection::~TcpConnection(){
}

void TcpConnection::connectionEstablished(){
	setState(kEstablish);
	channel->enableReading();
	connectionCallBack(shared_from_this());
}
void TcpConnection::connectionDestroyed(){
	std::cout << "state " << std::endl;
	std::cout << state << std::endl;
	assert(state == kEstablish);
	setState(kDisConnected);
	channel->disableAll();
//	closeCallBack(shared_from_this());

	connectionCallBack(shared_from_this());
	loop->removeChannel(get_pointer(channel));

}
void TcpConnection::handleRead(){
	char buf[65535];

	ssize_t n = ::read(channel->getSocket(), buf, sizeof(buf));

	if (n > 0){
		messageCallBack(shared_from_this(), buf, n);
	}
	else if (n == 0){
		std::cout << "should be closed" << std::endl;
		std::cout << " " << state << std::endl;
		handleClose();
	}
	else {
		handleError();
	}
}

void TcpConnection::handleWrite(){

}

void TcpConnection::handleClose(){
	channel->disableAll();
	closeCallBack(shared_from_this());
}
void TcpConnection::handleError(){
	std::cout << "Tcp handleError" << std::endl;
}
