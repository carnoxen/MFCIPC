#pragma once
#include "CBaseLayer.h"
class CFileLayer
	: public CBaseLayer
{
public:
	BOOL	Receive();
	BOOL	Send(unsigned char* ppayload, int nlength);

	CFileLayer(char* pName);
	virtual ~CFileLayer();
};
