/*
A MD5 Generator

MD5 process:
1.Append the data until it's length is N*512+448 bit (always append)
( 1000000000... = 0x8000..... )
2.Record the original length and write it after the append data (64 bit and Little-Endian)
3.Fill magic numbers
(A=0x01234567 B=0x89ABCDEF C=0xFEDCBA98 D=0x76543210, remember to converte it into Little-Endian)
4.For every 512 bits:
Seperate 16 groups and do the following calculating:
(Mx for data, and all the data using Little-Endian)

Turn 1
a=FF(a,b,c,d,M0,7,0xd76aa478)
b=FF(d,a,b,c,M1,12,0xe8c7b756)
c=FF(c,d,a,b,M2,17,0x242070db)
d=FF(b,c,d,a,M3,22,0xc1bdceee)
a=FF(a,b,c,d,M4,7,0xf57c0faf)
b=FF(d,a,b,c,M5,12,0x4787c62a)
c=FF(c,d,a,b,M6,17,0xa8304613)
d=FF(b,c,d,a,M7,22,0xfd469501)
a=FF(a,b,c,d,M8,7,0x698098d8)
b=FF(d,a,b,c,M9,12,0x8b44f7af)
c=FF(c,d,a,b,M10,17,0xffff5bb1)
d=FF(b,c,d,a,M11,22,0x895cd7be)
a=FF(a,b,c,d,M12,7,0x6b901122)
b=FF(d,a,b,c,M13,12,0xfd987193)
c=FF(c,d,a,b,M14,17,0xa679438e)
d=FF(b,c,d,a,M15,22,0x49b40821)

Turn 2
a=GG(a,b,c,d,M1,5,0xf61e2562)
b=GG(d,a,b,c,M6,9,0xc040b340)
c=GG(c,d,a,b,M11,14,0x265e5a51)
d=GG(b,c,d,a,M0,20,0xe9b6c7aa)
a=GG(a,b,c,d,M5,5,0xd62f105d)
b=GG(d,a,b,c,M10,9,0x02441453)
c=GG(c,d,a,b,M15,14,0xd8a1e681)
d=GG(b,c,d,a,M4,20,0xe7d3fbc8)
a=GG(a,b,c,d,M9,5,0x21e1cde6)
b=GG(d,a,b,c,M14,9,0xc33707d6)
c=GG(c,d,a,b,M3,14,0xf4d50d87)
d=GG(b,c,d,a,M8,20,0x455a14ed)
a=GG(a,b,c,d,M13,5,0xa9e3e905)
b=GG(d,a,b,c,M2,9,0xfcefa3f8)
c=GG(c,d,a,b,M7,14,0x676f02d9)
d=GG(b,c,d,a,M12,20,0x8d2a4c8a)

Turn 3
a=HH(a,b,c,d,M5,4,0xfffa3942)
b=HH(d,a,b,c,M8,11,0x8771f681)
c=HH(c,d,a,b,M11,16,0x6d9d6122)
d=HH(b,c,d,a,M14,23,0xfde5380c)
a=HH(a,b,c,d,M1,4,0xa4beea44)
b=HH(d,a,b,c,M4,11,0x4bdecfa9)
c=HH(c,d,a,b,M7,16,0xf6bb4b60)
d=HH(b,c,d,a,M10,23,0xbebfbc70)
a=HH(a,b,c,d,M13,4,0x289b7ec6)
b=HH(d,a,b,c,M0,11,0xeaa127fa)
c=HH(c,d,a,b,M3,16,0xd4ef3085)
d=HH(b,c,d,a,M6,23,0x04881d05)
a=HH(a,b,c,d,M9,4,0xd9d4d039)
b=HH(d,a,b,c,M12,11,0xe6db99e5)
c=HH(c,d,a,b,M15,16,0x1fa27cf8)
d=HH(b,c,d,a,M2,23,0xc4ac5665)

Turn 4
a=II(a,b,c,d,M0,6,0xf4292244)
b=II(d,a,b,c,M7,10,0x432aff97)
c=II(c,d,a,b,M14,15,0xab9423a7)
d=II(b,c,d,a,M5,21,0xfc93a039)
a=II(a,b,c,d,M12,6,0x655b59c3)
b=II(d,a,b,c,M3,10,0x8f0ccc92)
c=II(c,d,a,b,M10,15,0xffeff47d)
d=II(b,c,d,a,M1,21,0x85845dd1)
a=II(a,b,c,d,M8,6,0x6fa87e4f)
b=II(d,a,b,c,M15,10,0xfe2ce6e0)
c=II(c,d,a,b,M6,15,0xa3014314)
d=II(b,c,d,a,M13,21,0x4e0811a1)
a=II(a,b,c,d,M4,6,0xf7537e82)
b=II(d,a,b,c,M11,10,0xbd3af235)
c=II(c,d,a,b,M2,15,0x2ad7d2bb)
d=II(b,c,d,a,M9,21,0xeb86d391)
When all done, add a to A, b to B ...
Do that all until end of data.
*/

/* still need to modify the update() and finalize() part to make the code more simple */

#ifndef MD5UTILITY_H
#define MD5UTILITY_H

#include<iostream>
#include<stdint.h>
#include<fstream>
using namespace std;


class MD5
{
private:
	char *HextoChar = "0123456789ABCDEF";
	string md5_str = "";
	char md5_char[16];
	uint32_t hashes[4], data[16], dataBlockSize = 0;
	uint64_t fileSize = 0;

	inline uint32_t reverseUINT32(uint32_t);
	inline uint64_t reverseUINT64(uint64_t);
	inline uint32_t rotateLeftUINT32(uint32_t, size_t);

	inline uint32_t F(uint32_t, uint32_t, uint32_t);
	inline uint32_t G(uint32_t, uint32_t, uint32_t);
	inline uint32_t H(uint32_t, uint32_t, uint32_t);
	inline uint32_t I(uint32_t, uint32_t, uint32_t);

	inline void FF(uint32_t&, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
	inline void GG(uint32_t&, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
	inline void HH(uint32_t&, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
	inline void II(uint32_t&, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

	void process(void);
	bool finalize(void);

	void updateMD5Results(void);
	void updateMD5Char(void);
	void updateMD5String(void);

public:
	MD5(void);
	MD5(char*);
	MD5(char*, size_t);
	~MD5(void);

	void init(void);
	void update(char*, size_t);
	void updateWithFilename(char*);

	string getMD5InString(void);
	char* getMD5InChar(void);
};

#endif


