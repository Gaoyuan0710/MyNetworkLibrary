// =====================================================================================
// 
//       Filename:  Timestamp.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月12日 16时22分17秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <iostream>
#include <string>

using std::string;

namespace liunian{
class Timestamp{
	public:
		Timestamp();
		explicit Timestamp(int64_t miroSeconds = 0.0);
		~Timestamp();
		bool valid();
		int64_t mircoSecondsSinceEpoch();
		string toString() const;

		static Timestamp now();
		static Timestamp nowAfter(double seconds);
		static double nowMicroSeconds();
		static const int kMincroSecondsPerSecond = 1000 * 1000;

	private:
		int64_t mircoSecondsSinceEpoch;
};

inline bool operator < (Timestamp lhs, Timestamp rhs);
inline bool operator == (Timestamp lhs, Timestamp rhs);

inline bool Timestamp addTime(Timestamp timestamp, double seconds);

}




#endif
