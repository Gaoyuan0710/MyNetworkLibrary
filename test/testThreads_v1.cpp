 #include "../TcpServer.h"
 #include "../EventLoop.h"
 #include "../InetAddress.h"
#include "../CurrentThread.h"

 #include <stdio.h>
 
using namespace liunian;

 void onConnection(const TcpConnectionPtr& conn)
 {
   if (conn->ifEstablish())
   {
    printf("onConnection(): tid=%d new connection [%s] from %s\n",
				CurrentThread::tid(),
            conn->getname().c_str(),
            conn->getOtherAddress().showIpAndPort().c_str());
   }
   else
   {
    printf("onConnection(): tid=%d connection [%s] is down\n",
           CurrentThread::tid(),
            conn->getname().c_str());
   }
 }
 
 void onMessage(const TcpConnectionPtr& conn,
                Buffer* buf,
                Timestamp receiveTime)
 {
  printf("onMessage(): tid=%d received %zd bytes from connection [%s] at %s\n",
         CurrentThread::tid(),
          buf->readableSize(),
          conn->getname().c_str(),
          receiveTime.toString().c_str());
 
   conn->send(buf->retrieveAsString());
 }
 
int main(int argc, char* argv[])
 {
   printf("main(): pid = %d\n", getpid());
 
  	InetAddress listenAddr(9981);
   EventLoop loop;
 
   TcpServer server(&loop, listenAddr);
   server.setConnectionCallBack(onConnection);
   server.setMessageCallBack(onMessage);
  if (argc > 1) {
    server.setThreadNum(atoi(argv[1]));
  }
   server.start();
 
   loop.loop();
 }
