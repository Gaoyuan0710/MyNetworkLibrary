// =====================================================================================
// 
//       Filename:  testTcpServer_v1.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月17日 13时34分24秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "../Acceptor.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../Socket.h"
#include <stdio.h>


using namespace liunian;

void newConnection(int sockfd, 
			const InetAddress& peerAddr){
	printf("newConnection(): accepted a new connection from %s\n", peerAddr.showIpAndPort().c_str());

  write(sockfd, "How are you?\n", 13);
  close(sockfd);
}

int main()
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(9981);
  EventLoop loop;

  Acceptor acceptor(&loop, listenAddr);
 
  acceptor.setDealNewConnectionCallBack(newConnection);

  acceptor.listen();

  loop.loop();
}
