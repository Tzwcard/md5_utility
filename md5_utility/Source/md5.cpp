#include"..\Include\md5.h"

MD5::MD5(void)
{
	clear();
}

MD5::MD5(string type, string data)
{
	genMD5(type, data);
}

MD5::~MD5(void)
{
	;
}

void MD5::setMD5(string md5Hash)
{
	md5 = md5Hash;
}

void MD5::genMD5(string type, string data)
{
	clear();
	if (strcmp(type.c_str(), "FILE") == 0) setMD5(getMD5_file(data));
	else if (strcmp(type.c_str(), "STRING") == 0) setMD5(getMD5_str(data));
}

string MD5::getMD5(void)
{
	return(md5);
}

void MD5::clear(void)
{
	A = 0x67452301;	B = 0xefcdab89; C = 0x98badcfe; D = 0x10325476;
	fileSize = 0;
	memset(data, 0x00000000, sizeof(data));
}

string MD5::md5ToString(void)
{
	string MD5 = "";
	int i;
	for (i = 0; i < 8; i++) MD5.insert(MD5.size(), sizeof(char), HextoChar[((A) >> ((7 - i) * 4) & 0xf)]);
	for (i = 0; i < 8; i++) MD5.insert(MD5.size(), sizeof(char), HextoChar[((B) >> ((7 - i) * 4) & 0xf)]);
	for (i = 0; i < 8; i++) MD5.insert(MD5.size(), sizeof(char), HextoChar[((C) >> ((7 - i) * 4) & 0xf)]);
	for (i = 0; i < 8; i++) MD5.insert(MD5.size(), sizeof(char), HextoChar[((D) >> ((7 - i) * 4) & 0xf)]);
	return (MD5);
}

/*
MD5 calculating process
*/
void MD5::process(void)
{
	uint32_t a, b, c, d;
	a = A; b = B; c = C; d = D;

	//convert to Little-Endian
	for (int i = 0; i<16; i++) data[i] = reverseUINT32(data[i]);

	//Turn 1
	FF(a, b, c, d, data[0], 7, 0xd76aa478);
	FF(d, a, b, c, data[1], 12, 0xe8c7b756);
	FF(c, d, a, b, data[2], 17, 0x242070db);
	FF(b, c, d, a, data[3], 22, 0xc1bdceee);
	FF(a, b, c, d, data[4], 7, 0xf57c0faf);
	FF(d, a, b, c, data[5], 12, 0x4787c62a);
	FF(c, d, a, b, data[6], 17, 0xa8304613);
	FF(b, c, d, a, data[7], 22, 0xfd469501);
	FF(a, b, c, d, data[8], 7, 0x698098d8);
	FF(d, a, b, c, data[9], 12, 0x8b44f7af);
	FF(c, d, a, b, data[10], 17, 0xffff5bb1);
	FF(b, c, d, a, data[11], 22, 0x895cd7be);
	FF(a, b, c, d, data[12], 7, 0x6b901122);
	FF(d, a, b, c, data[13], 12, 0xfd987193);
	FF(c, d, a, b, data[14], 17, 0xa679438e);
	FF(b, c, d, a, data[15], 22, 0x49b40821);

	//Turn 2
	GG(a, b, c, d, data[1], 5, 0xf61e2562);
	GG(d, a, b, c, data[6], 9, 0xc040b340);
	GG(c, d, a, b, data[11], 14, 0x265e5a51);
	GG(b, c, d, a, data[0], 20, 0xe9b6c7aa);
	GG(a, b, c, d, data[5], 5, 0xd62f105d);
	GG(d, a, b, c, data[10], 9, 0x02441453);
	GG(c, d, a, b, data[15], 14, 0xd8a1e681);
	GG(b, c, d, a, data[4], 20, 0xe7d3fbc8);
	GG(a, b, c, d, data[9], 5, 0x21e1cde6);
	GG(d, a, b, c, data[14], 9, 0xc33707d6);
	GG(c, d, a, b, data[3], 14, 0xf4d50d87);
	GG(b, c, d, a, data[8], 20, 0x455a14ed);
	GG(a, b, c, d, data[13], 5, 0xa9e3e905);
	GG(d, a, b, c, data[2], 9, 0xfcefa3f8);
	GG(c, d, a, b, data[7], 14, 0x676f02d9);
	GG(b, c, d, a, data[12], 20, 0x8d2a4c8a);

	//Turn 3
	HH(a, b, c, d, data[5], 4, 0xfffa3942);
	HH(d, a, b, c, data[8], 11, 0x8771f681);
	HH(c, d, a, b, data[11], 16, 0x6d9d6122);
	HH(b, c, d, a, data[14], 23, 0xfde5380c);
	HH(a, b, c, d, data[1], 4, 0xa4beea44);
	HH(d, a, b, c, data[4], 11, 0x4bdecfa9);
	HH(c, d, a, b, data[7], 16, 0xf6bb4b60);
	HH(b, c, d, a, data[10], 23, 0xbebfbc70);
	HH(a, b, c, d, data[13], 4, 0x289b7ec6);
	HH(d, a, b, c, data[0], 11, 0xeaa127fa);
	HH(c, d, a, b, data[3], 16, 0xd4ef3085);
	HH(b, c, d, a, data[6], 23, 0x04881d05);
	HH(a, b, c, d, data[9], 4, 0xd9d4d039);
	HH(d, a, b, c, data[12], 11, 0xe6db99e5);
	HH(c, d, a, b, data[15], 16, 0x1fa27cf8);
	HH(b, c, d, a, data[2], 23, 0xc4ac5665);

	//Turn 4
	II(a, b, c, d, data[0], 6, 0xf4292244);
	II(d, a, b, c, data[7], 10, 0x432aff97);
	II(c, d, a, b, data[14], 15, 0xab9423a7);
	II(b, c, d, a, data[5], 21, 0xfc93a039);
	II(a, b, c, d, data[12], 6, 0x655b59c3);
	II(d, a, b, c, data[3], 10, 0x8f0ccc92);
	II(c, d, a, b, data[10], 15, 0xffeff47d);
	II(b, c, d, a, data[1], 21, 0x85845dd1);
	II(a, b, c, d, data[8], 6, 0x6fa87e4f);
	II(d, a, b, c, data[15], 10, 0xfe2ce6e0);
	II(c, d, a, b, data[6], 15, 0xa3014314);
	II(b, c, d, a, data[13], 21, 0x4e0811a1);
	II(a, b, c, d, data[4], 6, 0xf7537e82);
	II(d, a, b, c, data[11], 10, 0xbd3af235);
	II(c, d, a, b, data[2], 15, 0x2ad7d2bb);
	II(b, c, d, a, data[9], 21, 0xeb86d391);

	A += a; B += b; C += c; D += d;
}

bool MD5::finallize(int dataBlockSize)
{
	uint32_t tmp = 0x00000000;
	int i = dataBlockSize, j = 0;
	//last (2) block
	//1.fill 512 bits, 2blocks
	if (i == 56) {
		fileSize += i * 8;
		fileSize = reverseUINT64(fileSize);
		//block1
		data[14] = 0x80000000; data[15] = 0x00000000;
		process();
		//block2
		for (j = 0; j<14; j++) data[j] = 0x00000000;
		data[14] = (fileSize >> 32) & 0xffffffff; data[15] = fileSize & 0xffffffff;
		process();
	}
	//2.fill <512 bits, 1blocks
	else if (i<56)
	{
		fileSize += i * 8;
		fileSize = reverseUINT64(fileSize);
		//block1
		i++; j++; tmp = tmp << 8; tmp += 0x80;
		if (j == 4) { data[(i - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		while (i<56)
		{
			i++; j++; tmp = tmp << 8; tmp += 0x00;
			if (j == 4) { data[(i - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		}
		data[14] = (fileSize >> 32) & 0xffffffff; data[15] = fileSize & 0xffffffff;
		process();
	}
	//3.fill <512 bits, 2blocks
	else
	{
		fileSize += i * 8;
		fileSize = reverseUINT64(fileSize);
		//block1
		i++; j++; tmp = tmp << 8; tmp += 0x80;
		if (j == 4) { data[(i - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		while (i<64)
		{
			i++; j++; tmp = tmp << 8; tmp += 0x00;
			if (j == 4) { data[(i - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		}
		process();
		//block2
		for (j = 0; j<14; j++) data[j] = 0x00000000;
		data[14] = (fileSize >> 32) & 0xffffffff; data[15] = fileSize & 0xffffffff;
		process();
	}
	return(true);
}

/*
Call process
*/

/* error occur when fileSize==64*n bytes
   fix it later
*/

string MD5::getMD5_file(string inputFileName)
{
	fstream in;
	char t[1];
	int i = 0, j = 0;
	//magic initalize
	uint32_t  tmp = 0x00000000;
	//fileread init
	in.open(inputFileName.c_str(), ios::binary | ios::in);
	if (!in) { cout << "ERROR!"; exit(0); }
	//seperate block and process
	in.read(t, sizeof(t));
	while (!in.eof())
	{
		while (i<64 && !in.eof())
		{
			i++; j++;
			tmp = tmp << 8; tmp += (unsigned char)t[0];
			if (j == 4) { data[(i - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
			in.read(t, sizeof(t));
		}
		if (!in.eof() || (i == 64) {
			fileSize += 512;
			process();
			i = 0;
		}
	}
	finallize(i);
	//file read finished.
	in.clear(); in.close();
	A = reverseUINT32(A); B = reverseUINT32(B); C = reverseUINT32(C); D = reverseUINT32(D);
	//cout<<(long*)(reverseUINT64(fileSize)/8);
	//printMD5(A, B, C, D);
	return(md5ToString().c_str());
}

string MD5::getMD5_str(string strData)
{
	char t[1] = { 0x00 };
	int i = 0, j = 0, k = 0;
	uint32_t tmp = 0x00000000;
	t[0] = strData[k];
	while ((size_t)k < strData.size())
	{
		while (i<64 && (size_t)k < strData.size())
		{
			i++; j++; k++;
			tmp = tmp << 8; tmp += (unsigned char)t[0];
			if (j == 4) { data[(i - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
			t[0] = strData[k];
		}
		if ((size_t)k < strData.size() || (i == 64)) {
			fileSize += 512;
			process();
			i = 0;
		}
	}
	finallize(i);
	A = reverseUINT32(A); B = reverseUINT32(B); C = reverseUINT32(C); D = reverseUINT32(D);
	return(md5ToString().c_str());
}
