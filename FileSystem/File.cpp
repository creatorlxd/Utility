#include "FileSystem.h"

File::File()
{
	m_pFILE = nullptr;
	m_FileMode = FileMode::None;
}

File::~File()
{
	if (m_FileMode != FileMode::None)
		Close();
}

void File::Open(const string & filename, unsigned char mode)
{
	m_FileName = filename;
	m_FileMode = mode;
	string opt;
	if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) == 0)
	{
		opt = "r";
	}
	if ((mode&FileMode::Read) == 0 && (mode&FileMode::Write) != 0)
	{
		opt = "w";
	}
	if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) != 0)
	{
		opt = "r";
	}
	if ((mode&FileMode::Binary) != 0)
	{
		opt += "b";
	}
	if ((mode&FileMode::Read) != 0 && (mode&FileMode::Write) != 0)
	{
		opt += "+";
	}

	if (fopen_s(&m_pFILE, filename.c_str(), opt.c_str()) != 0)
		ThrowError(string("can not open file:" + filename));
	
	if ((mode&FileMode::Append) != 0)
	{
		fseek(m_pFILE, 0, SEEK_END);
	}
}

void File::Close()
{
	if (m_FileMode == FileMode::None)
		ThrowError("can not Close a File without Open or has been closed");

	fclose(m_pFILE);
	m_FileMode = FileMode::None;
	m_FileName.clear();
}

FilePosition File::GetBeginPosition()
{
	FilePosition buff,re;
	fgetpos(m_pFILE, &buff);
	fseek(m_pFILE, 0, SEEK_SET);
	fgetpos(m_pFILE, &re);
	fsetpos(m_pFILE, &buff);
	return re;
}

FilePosition File::GetEndPosition()
{
	FilePosition buff, re;
	fgetpos(m_pFILE, &buff);
	fseek(m_pFILE, 0L, SEEK_END);
	fgetpos(m_pFILE, &re);
	fsetpos(m_pFILE, &buff);
	return re;
}

FilePosition File::GetCurrentPosition()
{
	FilePosition re;
	fgetpos(m_pFILE, &re);
	return re;
}

void File::SetFilePosition(FilePosition pos)
{
	fsetpos(m_pFILE, &pos);
}

void File::Read(void * adr, size_t size)
{
	fread_s(adr, size, size, 1, m_pFILE);
}

void File::Wirte(const void * adr, size_t size)
{
	fwrite(adr, size, 1, m_pFILE);
}

File & File::operator>>(char * cstr)
{
	string str;
	*this >> str;
	memcpy(cstr, str.c_str(), sizeof(char)*str.size());
	return *this;
}

File& File::operator>>(string & str)
{
	char c = ' ';
	while (c == ' ' || c == '\r' || c == '\n')
	{
		c = fgetc(m_pFILE);
	}
	while (c != ' '&&c != EOF&&c != '\r'&&c != '\n')
	{
		str += c;
		c = fgetc(m_pFILE);
	}
	return *this;
}

File & File::operator>>(int & i)
{
	if((m_FileMode&FileMode::Read)!=0)
		fscanf_s(m_pFILE, "%d", &i);
	return *this;
}

File & File::operator>>(unsigned int & ui)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%ud", &ui);
	return *this;
}

File & File::operator>>(short & s)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%hd", &s);
	return *this;
}

File & File::operator>>(unsigned short & us)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%hud", &us);
	return *this;
}

File & File::operator>>(long & l)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%ld", &l);
	return *this;
}

File & File::operator>>(unsigned long & ul)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%uld", &ul);
	return *this;
}

File & File::operator>>(long long & ll)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%I64d", &ll);
	return *this;
}

File & File::operator>>(unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%I64ud", &ull);
	return *this;
}

File & File::operator>>(char & c)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, " \r\n\t%c", &c,sizeof(char));
	return *this;
}

File & File::operator>>(unsigned char & uc)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%hhu", &uc);
	return *this;
}

File & File::operator>>(float & f)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%f", &f);
	return *this;
}

File & File::operator>>(double & d)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%lf", &d);
	return *this;
}

File & File::operator>>(long double & ld)
{
	if ((m_FileMode&FileMode::Read) != 0)
		fscanf_s(m_pFILE, "%Lf", &ld);
	return *this;
}

File & File::operator<<(const PrintMode & pm)
{
	switch (pm)
	{
	case EndLine:
	{
		fscanf_s(m_pFILE, "\n");
		fflush(m_pFILE);
	}
	default:
		break;
	}
	return *this;
}

File & File::operator<<(const char * cstr)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%s", cstr);
	return *this;
}

File & File::operator<<(const string & str)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%s", str.c_str());
	return *this;
}

File & File::operator<<(const int & i)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%d", i);
	return *this;
}

File & File::operator<<(const unsigned int & ui)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%ud", ui);
	return *this;
}

File & File::operator<<(const short & s)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%hd", s);
	return *this;
}

File & File::operator<<(const unsigned short & us)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%hud", us);
	return *this;
}

File & File::operator<<(const long & l)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%ld", l);
	return *this;
}

File & File::operator<<(const unsigned long & ul)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%lud", ul);
	return *this;
}

File & File::operator<<(const long long & ll)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%I64d", ll);
	return *this;
}

File & File::operator<<(const unsigned long long & ull)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%I64ud", ull);
	return *this;
}

File & File::operator<<(const char & c)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%c", c);
	return *this;
}

File & File::operator<<(const unsigned char & uc)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%hhu", uc);
	return *this;
}

File & File::operator<<(const float & f)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%f", f);
	return *this;
}

File & File::operator<<(const double & d)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%lf", d);
	return *this;
}

File & File::operator<<(const long double & ld)
{
	if ((m_FileMode&FileMode::Write) != 0)
		fprintf_s(m_pFILE, "%Lf", ld);
	return *this;
}
