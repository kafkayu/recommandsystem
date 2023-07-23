//#include"video.h"
#include"cluster.h"
using namespace std;
#include<time.h>
int main()
{



	Load();
	createNewPeople();

	clock_t s, e;
	//for (int i =71; i < 500; i += 3) {
	//	s = clock();
	//	F3VideoSearch(u_video[i][1]);
	//	e = clock();
	//	cout << "birch time = " << double(e - s) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ） 
	//}

	//s = clock();
	//Birch();
	//e = clock();
	//cout << "birch time = " << double(e - s) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）

	//s = clock();
	//notBirchkmeans();
	//e = clock();
	//cout << "not birch time = " << double(e - s) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）




	s = clock();
	//kmeans();
	e = clock();
	kmeans2();
	//Save();
	cout << "birch+kmeans time = " << double(e-s) / CLOCKS_PER_SEC << "s" << endl;  //输出时间（单位：ｓ）
	return 0;
}