void SetColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);
void SetPos(int x, int y);

const short Blue = 1;
const short Green = 2;
const short LightBlue = 3;
const short Red = 4;

void SetColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);
}

void SetPos(int x, int y)
{
	COORD pos;
	HANDLE handle;
	pos.X = x;
	pos.Y = y;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}
