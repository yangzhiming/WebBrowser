#include "StdAfx.h"
#include "ByteStream.h"

namespace ByteStream
{

size_t SizeOfString(const std::string& src)
{
	return src.length();
}

size_t ReadString(const BYTE* pos, std::string& dst, size_t len)
{
	if(len == 0)
		return 0;

	dst.assign((const char*)pos, len);
	return len;
}

size_t WriteString(const BYTE* pos, const std::string& src)
{
	memcpy_s((void*)pos, src.length(), src.c_str(), src.length());
	return src.length();
}

size_t ReadDword(const BYTE* pos, DWORD& dwData, size_t len)
{
	dwData = *((DWORD*)pos);
	return sizeof(DWORD);
}

size_t WriteDword(BYTE* pos, DWORD dwData)
{
	memcpy_s((void*)pos, sizeof(dwData), &dwData, sizeof(DWORD));
	return sizeof(DWORD);
}

}