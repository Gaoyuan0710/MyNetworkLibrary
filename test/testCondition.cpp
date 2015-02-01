// =====================================================================================
// 
//       Filename:  testCondition.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月31日 14时25分42秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include "../Condition.h"
#include "../Mutex.h"

using namespace liunian;
using std::cout;
using std::endl;

MutexLock mutex;
Condtion condititon(mutex);

int count = 0;

void *decrement_count(void *arg) {	
	MutexLockGuard mutexDecrement(mutex);

	cout << "The process decrement get lock" << endl;

	while (0 == count) {
		cout << "decrement count == 0" << endl;
		cout << "decrement count before wait " << endl;
		condititon.wait();
		cout << "decrement count after wait " << endl;
	}
	count ++;
}
void *increment_count(void* argv) {
	MutexLockGuard mutexIncreament(mutex);

	cout << "increment count get lock" << endl;

	if (0 == count ) {
		cout << "increment count befor signal " << endl;
		condititon.notify();
		cout << "increment count after signal " << endl;
	}

	count++;
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;


	pthread_create(&thread1, NULL, decrement_count, NULL);
	sleep(2);
	pthread_create(&thread2, NULL, increment_count, NULL);

	sleep(10);
	pthread_exit(0);


	return 0;
}

