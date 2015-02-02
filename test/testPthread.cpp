// =====================================================================================
// 
//       Filename:  testPthread.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月02日 16时27分09秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "../Thread.h"

using namespace liunian;
using std::cout;
using std::endl;

void ThreaProcess(){
	int countNum = 100;

	for (int i = 0; i < countNum; i++){
		if (i % 10 == 0){
			cout << endl;
		}
		cout << i << "  ";
	}
}
int main(int argc, char *argv[])
{
	boost::function<void ()> f;

	f = boost::bind(&ThreaProcess);

	Thread testThread(f, "ThreadTest");

	testThread.start();

	sleep(1000 * 1000);
	return 0;
}

