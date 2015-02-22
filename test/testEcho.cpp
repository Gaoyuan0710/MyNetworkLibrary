#include "../TcpServer.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../CallBack.h"

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
               Buffer* buf,
               Timestamp receiveTime)
{
  printf("onMessage(): received %zd bytes from connection [%s] at %s\n",
         buf->readableSize(),
         conn->getname().c_str(),
		 receiveTime.toString().c_str());
        // receiveTime.toFormattedString().c_str());

  //std::cout << "On message function " << buf->retrieveAsString() << std::endl;
  conn->send(buf->retrieveAsString());
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
