/*
  md5 generator
  test program
*/

#include<iostream>
#include"..\Include\md5.h"
using namespace std;

/*

  Usage:
		//file
		MD5 m;
		m.updateWithFilename(fileName);

		MD5 m(fileName);

		//string
		MD5 m;
		m.update("TEST",4);

		MD5 m("TEST",4);

		//print as string
		cout<<m.getMD5InString().c_str();

*/
void main(int argc, char **argv){
	MD5 hash;
	char cTmp[256],cTmp2[256];
	string sTmp;
	cin >> cTmp;
	cin >> cTmp2;
	sTmp = cTmp2;
	if (strcmp(cTmp, "FILE") == 0) hash.updateWithFilename(cTmp2);
	else if (strcmp(cTmp, "STRING") == 0) hash.update(cTmp2, sTmp.size());
	cout << hash.getMD5InString().c_str();
}
