// =====================================================================================
// 
//       Filename:  testTcpConnection_v1.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月17日 20时10分31秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "../TcpServer.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../CallBack.h"
#include "../Buffer.h"

#include <stdio.h>

using namespace liunian;

void onConnection(const TcpConnectionPtr& conn)
{

  if (conn->ifEstablish())
  {
    printf("onConnection(): new connection [%s] from %s\n",
           conn->getname().c_str(),
           conn->getOtherAddress().showIpAndPort().c_str());
  }
  else
  {
    printf("onConnection(): connection [%s] is down\n",
           conn->getname().c_str());
  }
}

void onMessage(const TcpConnectionPtr& conn,
               Buffer *buf,
               Timestamp receiveTime)
{
  printf("onMessage(): received %zd bytes from connection [%s]\n",
         buf->readableSize(),
		 conn->getname().c_str(),
		 receiveTime.toString().c_str());
  printf("On message:%s\n", buf->retrieveAllAsString().c_str());


}

int main()
{
  printf("main(): pid = %d\n", getpid());

  InetAddress listenAddr(9981);
  EventLoop loop;

  TcpServer server(&loop, listenAddr);
 
  server.setConnectionCallBack(onConnection);
  server.setMessageCallBack(onMessage);
  server.start();

  loop.loop();
}

