#pragma once
#include "CBaseLayer.h"
class CEthernetLayer
	: public CBaseLayer
{
private:
	inline void		ResetHeader();

public:
	BOOL			Receive(unsigned char* ppayload);
	BOOL			Send(unsigned char* ppayload, int nlength);
	void			SetDestinAddress(unsigned char* pAddress);
	void			SetSourceAddress(unsigned char* pAddress);
	unsigned char* GetDestinAddress();
	unsigned char* GetSourceAddress();

	CEthernetLayer(char* pName);
	virtual ~CEthernetLayer();

	typedef struct _ETHERNET_HEADER {

		unsigned char	enet_dstaddr[6];		// destination address of ethernet layer
		unsigned char	enet_srcaddr[6];		// source address of ethernet layer
		unsigned short	enet_type;		// type of ethernet layer
		unsigned char	enet_data[ETHER_MAX_DATA_SIZE]; // frame data

	} ETHERNET_HEADER, * PETHERNET_HEADER;

protected:
	ETHERNET_HEADER	m_sHeader;
};

