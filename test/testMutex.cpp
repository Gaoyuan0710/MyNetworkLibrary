// =====================================================================================
// 
//       Filename:  testMutex.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月19日 16时45分41秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "../Mutex.h"

using namespace liunian;
using std::cout;
using std::endl;

MutexLock mutex;

static void *test1(void *ptr) {
	MutexLockGuard lock(mutex);
	cout << "thread1 test " << endl;
	sleep(10);
	cout << "thread1 over " << endl;
}
static void *test2(void *ptr) {
	MutexLockGuard lock(mutex);
	cout << "thread2 test " << endl;
	sleep(10);
	cout << "thread2 over " << endl;
}


int main(int argc, char *argv[])
{
	pthread_t test_thread;

	cout << "Main test" << endl;

	pthread_create(&test_thread, NULL, test1, NULL);
	pthread_create(&test_thread, NULL, test2, NULL);

	sleep(50);
	cout << "Main over" << endl;
	pthread_join(test_thread, NULL);


	return 0;
}
