#pragma once
#include "CBaseLayer.h"
class CChatAppLayer
	: public CBaseLayer
{
private:
	inline void		ResetHeader();
	CObject* mp_Dlg;

public:
	BOOL			Receive(unsigned char* ppayload);
	BOOL			Send(unsigned char* ppayload, int nlength);
	unsigned int	GetDestinAddress();
	unsigned int	GetSourceAddress();
	void			SetDestinAddress(unsigned int dst_addr);
	void			SetSourceAddress(unsigned int src_addr);

	CChatAppLayer(char* pName);
	virtual ~CChatAppLayer();

	typedef struct _CHAT_APP_HEADER {

		unsigned int	app_dstaddr; // destination address of application layer
		unsigned int	app_srcaddr; // source address of application layer
		unsigned short	app_length; // total length of the data
		unsigned char	app_type; // type of application data
		unsigned char	app_data[APP_DATA_SIZE]; // application data

	} CHAT_APP_HEADER, * PCHAT_APP_HEADER;

protected:
	CHAT_APP_HEADER		m_sHeader;

	enum {
		DATA_TYPE_CONT = 0x01,
		DATA_TYPE_END = 0x02
	};
};

