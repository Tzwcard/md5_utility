/*
  md5 generator
*/

#include<iostream>
#include"..\Include\md5.h"
using namespace std;

/*

  Usage:
        MD5 m;
		//file
		m.genMD5("FILE",fileName);
		cout<<m.getMD5().c_str();
		//string
		m.genMD5("STRING","TEST");
		cout<<m.getMD5().c_str();

		MD5 n("STRING","TEST");
        cout<<n.getMD5().c_str();

*/
void main(int argc, char **argv){
	string test;
	char tmp[256],tmp2[256];
	cin >> tmp;
	cin >> tmp2;
	MD5 hash=MD5(tmp,tmp2);
	cout << hash.getMD5().c_str();
}
