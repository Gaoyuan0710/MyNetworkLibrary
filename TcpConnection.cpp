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
#include "Timestamp.h"

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
						boost::bind(&TcpConnection::handleRead, this, _1));
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
	
	std::cout << "TcpConnection ConnectionDestroyed" << std::endl;
	assert(state == kEstablish);
	setState(kDisConnected);
	channel->disableAll();
	//sleep(100);
//	closeCallBack(shared_from_this());

	connectionCallBack(shared_from_this());
	loop->removeChannel(get_pointer(channel));

}
void TcpConnection::handleRead(Timestamp recvTime){
	char buf[65535];
	int saveError = 0;

	ssize_t n = inputBuffer.readFd(channel->getSocket(), &saveError);

	std::cout << "n = " << n << std::endl;
	//sleep(10);
	if (n > 0){
		messageCallBack(shared_from_this(), &inputBuffer, recvTime);
	}
	else if (n == 0){
		std::cout << "should be closed" << std::endl;
		std::cout << " " << state << std::endl;
	//	sleep(100);
		handleClose();
	}
	else {
		errno = saveError;
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
