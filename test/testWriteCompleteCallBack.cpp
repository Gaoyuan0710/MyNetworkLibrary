#include "../TcpServer.h"
#include "../EventLoop.h"
#include "../InetAddress.h"
#include <stdio.h>

using namespace liunian;
std::string message;

void onConnection(const TcpConnectionPtr& conn)
{
  if (conn->ifEstablish())
  {
    printf("onConnection(): new connection [%s] from %s\n",
           conn->getname().c_str(),
           conn->getOtherAddress().showIpAndPort().c_str());
    conn->send(message);
  }
  else
  {
    printf("onConnection(): connection [%s] is down\n",
           conn->getname().c_str());
  }
}

void onWriteComplete(const TcpConnectionPtr& conn)
{
  conn->send(message);
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

int main()
{
  printf("main(): pid = %d\n", getpid());

  std::string line;
  for (int i = 33; i < 127; ++i)
  {
    line.push_back(char(i));
  }
  line += line;

  for (size_t i = 0; i < 127-33; ++i)
  {
    message += line.substr(i, 72) + '\n';
  }

  InetAddress listenAddr(9981);
  EventLoop loop;

  TcpServer server(&loop, listenAddr);
  server.setConnectionCallBack(onConnection);
  server.setMessageCallBack(onMessage);
  server.setWriteCompleteCallBack(onWriteComplete);
  server.start();

  loop.loop();
}
