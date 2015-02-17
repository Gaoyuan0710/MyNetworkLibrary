// =====================================================================================
// 
//       Filename:  CallBack.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月17日 18时05分39秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef CALLBACK_H
#define CALLBACK_H
#include <map>

#include "TcpConnection.h"

using std::map;
namespace liunian{
class TcpConnection;

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef map<string, TcpConnectionPtr> ConnectionMap;
typedef boost::function<void (const TcpConnectionPtr&)> ConnectionCallBack;
typedef boost::function<void (const TcpConnectionPtr&, const char *message, ssize_t len)> MessageCallBack;
typedef boost::function<void (const TcpConnectionPtr&)> CloseCallBack;
}
#endif
