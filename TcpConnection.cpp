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
		}
TcpConnection::~TcpConnection(){
}

void TcpConnection::connectionEstablished(){
	setState(kEstablish);
	channel->enableReading();
}
void TcpConnection::handleRead(){
	char buf[65535];

	ssize_t n = ::read(channel->getSocket(), buf, sizeof(buf));

	if (n == 0){
		std::cout << "should be closed" << std::endl;
	}
	messageCallBack(shared_from_this(), buf, n);
}
