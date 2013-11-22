#pragma once

namespace ByteStream
{
	size_t SizeOfString(const std::string& src);
	size_t WriteString(const BYTE* pos, const std::string& src);
	size_t ReadString(const BYTE* pos, std::string& dst, size_t len);
	size_t WriteDword(BYTE* pos, DWORD dwData);
	size_t ReadDword(const BYTE* pos, DWORD& dwData, size_t len);
}