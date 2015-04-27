#include"..\Include\md5.h"

MD5::MD5(void)
{
	init();
}

MD5::MD5(char* fileName)
{
	init();
	updateWithFilename(fileName);
}

MD5::MD5(char* input, size_t length)
{
	init();
	update(input, length);
}

MD5::~MD5(void)
{
	;
}

inline uint32_t MD5::reverseUINT32(uint32_t x)
{
	return(((x& 0xff000000) >> 24) | ((x& 0x00ff0000) >> 8) | ((x& 0x0000ff00) << 8) | ((x& 0x000000ff) << 24));
}

inline uint64_t MD5::reverseUINT64(uint64_t x)
{
	return(((x& 0xff00000000000000) >> 56) | ((x& 0x00ff000000000000) >> 40) | ((x& 0x0000ff0000000000) >> 24) | ((x& 0x000000ff00000000) >> 8) | ((x& 0x00000000ff000000) << 8) | ((x& 0x0000000000ff0000) << 24) | ((x& 0x000000000000ff00) << 40) | ((x& 0x00000000000000ff) << 56));
}

inline uint32_t MD5::rotateLeftUINT32(uint32_t x, size_t n)
{
	return((x << n) | (x >> (32 - n)));
}

inline uint32_t MD5::F(uint32_t x, uint32_t y, uint32_t z)
{
	return((x & y) | ((~x) & z));
}

inline uint32_t MD5::G(uint32_t x, uint32_t y, uint32_t z)
{
	return((x & z) | (y & (~z)));
}
inline uint32_t MD5::H(uint32_t x, uint32_t y, uint32_t z)
{
	return(x ^ y ^ z);
}
inline uint32_t MD5::I(uint32_t x, uint32_t y, uint32_t z)
{
	return(y ^ (x | (~z)));
}

/*
FF(a,b,c,d,x,s,ti) a=b+((a+F(b,c,d)+x+ti)<<<s)
GG(a,b,c,d,x,s,ti) a=b+((a+G(b,c,d)+x+ti)<<<s)
HH(a,b,c,d,x,s,ti) a=b+((a+H(b,c,d)+x+ti)<<<s)
II(a,b,c,d,x,s,ti) a=b+((a+I(b,c,d)+x+ti)<<<s)
*/
inline void MD5::FF(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a = rotateLeftUINT32(a + F(b, c, d) + x + ac, s) + b;
}
inline void MD5::GG(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a = rotateLeftUINT32(a + G(b, c, d) + x + ac, s) + b;
}
inline void MD5::HH(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a = rotateLeftUINT32(a + H(b, c, d) + x + ac, s) + b;
}
inline void MD5::II(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a = rotateLeftUINT32(a + I(b, c, d) + x + ac, s) + b;
}

string MD5::getMD5InString(void)
{
	return(md5_str);
}

char* MD5::getMD5InChar(void)
{
	return(md5_char);
}

void MD5::init(void)
{
	hashes[0] = 0x67452301;	hashes[1] = 0xefcdab89; hashes[2] = 0x98badcfe; hashes[3] = 0x10325476;
	dataBlockSize = 0;
	fileSize = 0;
	memset(data, 0x00000000, sizeof(data));

	md5_str = "";
	memset(md5_char, 0x00, sizeof(md5_char));
}

void MD5::updateMD5Results(void)
{
	updateMD5String();
	updateMD5Char();
}

void MD5::updateMD5Char(void)
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		md5_char[i * 4 + j] = (hashes[i] >> ((4 - j) * 8)) & 0xff;
}

void MD5::updateMD5String(void)
{
	md5_str = "";
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 8; j++)
		md5_str.insert(md5_str.size(), sizeof(char), HextoChar[((hashes[i]) >> ((7 - j) * 4) & 0xf)]);
}

/*
MD5 calculating process
*/
void MD5::process(void)
{
	uint32_t a, b, c, d;
	a = hashes[0]; b = hashes[1]; c = hashes[2]; d = hashes[3];

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

	hashes[0] += a; hashes[1] += b; hashes[2] += c; hashes[3] += d;
}

bool MD5::finalize()
{
	uint32_t tmp = 0x00000000;
	int j = 0;
	//last (2) block
	//1.fill 512 bits, 2blocks
	if (dataBlockSize == 56) {
		fileSize += dataBlockSize * 8;
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
	else if (dataBlockSize<56)
	{
		fileSize += dataBlockSize * 8;
		fileSize = reverseUINT64(fileSize);
		//block1
		dataBlockSize++; j++; tmp = tmp << 8; tmp += 0x80;
		if (j == 4) { data[(dataBlockSize - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		while (dataBlockSize<56)
		{
			dataBlockSize++; j++; tmp = tmp << 8; tmp += 0x00;
			if (j == 4) { data[(dataBlockSize - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		}
		data[14] = (fileSize >> 32) & 0xffffffff; data[15] = fileSize & 0xffffffff;
		process();
	}
	//3.fill <512 bits, 2blocks
	else
	{
		fileSize += dataBlockSize * 8;
		fileSize = reverseUINT64(fileSize);
		//block1
		dataBlockSize++; j++; tmp = tmp << 8; tmp += 0x80;
		if (j == 4) { data[(dataBlockSize - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		while (dataBlockSize<64)
		{
			dataBlockSize++; j++; tmp = tmp << 8; tmp += 0x00;
			if (j == 4) { data[(dataBlockSize - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
		}
		process();
		//block2
		for (j = 0; j<14; j++) data[j] = 0x00000000;
		data[14] = (fileSize >> 32) & 0xffffffff; data[15] = fileSize & 0xffffffff;
		process();
	}
	for (int i = 0; i < 4; i++)	hashes[i] = reverseUINT32(hashes[i]);
	return(true);
}

/*
Call process
*/

/* error occur when fileSize==64*n bytes
   fix it later
*/

void MD5::updateWithFilename(char* inputFileName)
{
	fstream in;
	char t[1];
	int i = 0, j = 0;
	//magic initalize
	uint32_t  tmp = 0x00000000;
	//fileread init
	in.open(inputFileName, ios::binary | ios::in);
	if (!in) { cout << "ERROR!"; exit(0); }
	//seperate block and process
	in.read(t, sizeof(t));
	while (!in.eof())
	{
		while (dataBlockSize<64 && !in.eof())
		{
			dataBlockSize++; j++;
			tmp = tmp << 8; tmp += (unsigned char)t[0];
			if (j == 4) { data[(dataBlockSize - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
			in.read(t, sizeof(t));
		}
		if (!in.eof() || (dataBlockSize == 64))
		{
			fileSize += 512;
			process();
			dataBlockSize = 0;
		}
	}
	finalize();
	in.clear(); in.close();
	updateMD5Results();
}

void MD5::update(char* dataIn, size_t length)
{
	char t[1] = { 0x00 };
	int i = 0, j = 0, k = 0;
	uint32_t tmp = 0x00000000;
	t[0] = dataIn[k];
	while ((size_t)k < length)
	{
		while (dataBlockSize<64 && (size_t)k < length)
		{
			dataBlockSize++; j++; k++;
			tmp = tmp << 8; tmp += (unsigned char)t[0];
			if (j == 4) { data[(dataBlockSize - 1) >> 2] = tmp; tmp = 0x00000000; j = 0; }
			t[0] = dataIn[k];
		}
		if ((size_t)k < length || (dataBlockSize == 64))
		{
			fileSize += 512;
			process();
			dataBlockSize = 0;
		}
	}
	finalize();
	updateMD5Results();
}
