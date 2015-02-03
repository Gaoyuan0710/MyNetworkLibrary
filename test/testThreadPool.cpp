// =====================================================================================
// 
//       Filename:  testThreadPool.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月02日 20时56分16秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <boost/bind.hpp>

#include "../ThreadPool.h"
#include "../Thread.h"

using namespace liunian;
using std::cout;
using std::endl;

void print()
{
	printf("tid=%d\n", pthread_self());
}

void printString(const std::string& str)
{
	cout << str;
	printf("finish with tid=%lu\n", pthread_self());
	usleep(100*1000);
  
}

void test(int maxSize)
{
  cout << "Test ThreadPool with max queue size = " << maxSize << endl;
  ThreadPool pool("MainThreadPool");
  pool.setMaxQueueSize(maxSize);
  pool.start(5);

  cout << "Adding" << endl;
//  pool.addWork(print);
//  pool.addWork(print);
  for (int i = 0; i < 100; ++i)
  {
    char buf[32];
    snprintf(buf, sizeof buf, "task %d", i);
    pool.addWork(boost::bind(printString, std::string(buf)));
  }
  cout << "Done" << endl;

//  sleep(1000);
}

int main()
{
//  test(0);
//  test(1);
//  test(5);
  test(10);
//  test(50);
}
