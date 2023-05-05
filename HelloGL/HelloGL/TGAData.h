#pragma once

class TGAData
{
public:
	char ImageType; //byte 3
	unsigned short ImageWidth, ImageHeight; //field 5, byte set 5,6/7,8
	char Depth; //field 5, byte 9
	int FileSize;
};