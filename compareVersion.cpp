// =====================================================================================
// 
//       Filename:  compareVersion.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月03日 11时23分21秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <string>

using std::string;


class Solution {
	public:
		int compareVersion(string version1, string version2) {
			int val1, val2;
			int idx1 = 0, idx2 = 0;
			
			while (idx1 < version1.length() || idx2 < version2.length()) {
				val1 = 0; 
				
				while (idx1 < version1.length()) {
					if (version1[idx1] == '.') {
                    ++idx1;
                    break;
                }
                val1 = val1 * 10 + (version1[idx1] - '0');
                ++idx1;
            }
            val2 = 0; 
            while (idx2 < version2.length()) {
                if (version2[idx2] == '.') {
                    ++idx2;
                    break;
                }
                val2 = val2 * 10 + (version2[idx2] - '0');
                ++idx2;
            }
            if (val1 > val2) return 1;
            if (val1 < val2) return -1;
        }
        return 0;
    }
};
int main(int argc, char *argv[])
{
	Solution testSolution;
	cout << testSolution.compareVersion.cpp("1.1", "1.2");

	return 0;
}

