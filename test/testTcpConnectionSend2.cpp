#include "../TcpServer.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../CallBack.h"
#include <stdio.h>

using namespace liunian;

std::string message1;
std::string message2;
int sleepSeconds = 20;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->ifEstablish())
  {
    printf("onConnection(): new connection [%s] from %s\n",
           conn->getname().c_str(),
           conn->getOtherAddress().showIpAndPort().c_str());
    
	if (sleepSeconds > 0){
		sleep(sleepSeconds);
	}
	
	conn->send(message1);
    conn->send(message2);
    conn->shutdown();
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

  buf->retrieveAll();
}

int main(int argc, char* argv[])
{
  printf("main(): pid = %d\n", getpid());

  int len1 = 100;
  int len2 = 200;

  if (argc > 2)
  {
    len1 = atoi(argv[1]);
    len2 = atoi(argv[2]);
  }

  message1.resize(len1);
  message2.resize(len2);
  std::fill(message1.begin(), message1.end(), 'A');
  std::fill(message2.begin(), message2.end(), 'B');

  InetAddress listenAddr(9981);
  EventLoop loop;

  TcpServer server(&loop, listenAddr);
  server.setConnectionCallBack(onConnection);
  server.setMessageCallBack(onMessage);
  server.start();

  loop.loop();
}
