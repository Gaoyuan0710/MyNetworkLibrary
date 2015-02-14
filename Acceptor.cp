// =====================================================================================
// 
//       Filename:  Acceptor.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月10日 17时31分30秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "Acceptor.h"

using namespace liunian;

Acceptor::Acceptor(EventLoop *loop)
		:listenFd(-1),
		acceptChannel(NULL),
		loop(NULL)
{
	
}

