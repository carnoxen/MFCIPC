#include "pch.h"
#include "CChatAppLayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChatAppLayer::CChatAppLayer(char* pName)
	: CBaseLayer(pName),
	mp_Dlg(NULL)
{
	ResetHeader();
}

CChatAppLayer::~CChatAppLayer()
{

}

void CChatAppLayer::SetSourceAddress(unsigned int src_addr)
{
	m_sHeader.app_srcaddr = src_addr;
}

void CChatAppLayer::SetDestinAddress(unsigned int dst_addr)
{
	m_sHeader.app_dstaddr = dst_addr;
}

void CChatAppLayer::ResetHeader()
{
	m_sHeader.app_srcaddr = 0x00000000;
	m_sHeader.app_dstaddr = 0x00000000;
	m_sHeader.app_length = 0x0000;
	m_sHeader.app_type = 0x00;
	memset(m_sHeader.app_data, 0, APP_DATA_SIZE);
}

unsigned int CChatAppLayer::GetSourceAddress()
{
	return m_sHeader.app_srcaddr;
}

unsigned int CChatAppLayer::GetDestinAddress()
{
	return m_sHeader.app_dstaddr;
}

BOOL CChatAppLayer::Send(unsigned char* ppayload, int nlength)
{
	m_sHeader.app_length = (unsigned short)nlength;

	BOOL bSuccess = FALSE;
	//////////////////////// fill the blank ///////////////////////////////
	memcpy(m_sHeader.app_data, ppayload, (nlength > APP_DATA_SIZE) ? APP_DATA_SIZE : nlength);
	bSuccess = mp_UnderLayer->Send((unsigned char*)&m_sHeader, nlength + APP_HEADER_SIZE);
	///////////////////////////////////////////////////////////////////////

	return bSuccess;
}

BOOL CChatAppLayer::Receive(unsigned char* ppayload)
{
	PCHAT_APP_HEADER app_hdr = (PCHAT_APP_HEADER)ppayload;

	if (app_hdr->app_dstaddr == m_sHeader.app_srcaddr ||
		(app_hdr->app_srcaddr != m_sHeader.app_srcaddr &&
			app_hdr->app_dstaddr == (unsigned int)0xff))
	{
		//////////////////////// fill the blank ///////////////////////////////
		unsigned char GetBuff[APP_DATA_SIZE];
		memset(GetBuff, 0, APP_DATA_SIZE);
		memcpy(GetBuff, app_hdr->app_data, (app_hdr->app_length > APP_DATA_SIZE) ? APP_DATA_SIZE : app_hdr->app_length);

		CString Msg;
		if (app_hdr->app_dstaddr == (unsigned int)0xff) {
			Msg.Format("[%d:B] %s", app_hdr->app_srcaddr, (char*)GetBuff);
		}
		else {
			Msg.Format("[%d:%d] %s", app_hdr->app_srcaddr, app_hdr->app_dstaddr, (char*)GetBuff);
		}
		mp_aUpperLayer[0]->Receive((unsigned char*)Msg.GetBuffer(0));
		///////////////////////////////////////////////////////////////////////
		return TRUE;
	}
	else
		return FALSE;
}