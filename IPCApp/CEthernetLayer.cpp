#include "pch.h"
#include "CEthernetLayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEthernetLayer::CEthernetLayer(char* pName)
	: CBaseLayer(pName)
{
	ResetHeader();
}

CEthernetLayer::~CEthernetLayer()
{
}

void CEthernetLayer::ResetHeader()
{
	memset(m_sHeader.enet_dstaddr, 0, 6);
	memset(m_sHeader.enet_srcaddr, 0, 6);
	memset(m_sHeader.enet_data, ETHER_MAX_DATA_SIZE, 6);
	m_sHeader.enet_type = 0;
}

unsigned char* CEthernetLayer::GetSourceAddress()
{
	return m_sHeader.enet_srcaddr;
}

unsigned char* CEthernetLayer::GetDestinAddress()
{
	//////////////////////// fill the blank ///////////////////////////////
	return m_sHeader.enet_dstaddr;
	///////////////////////////////////////////////////////////////////////
}

void CEthernetLayer::SetSourceAddress(unsigned char* pAddress)
{
	//////////////////////// fill the blank ///////////////////////////////
	memcpy(m_sHeader.enet_srcaddr, pAddress, 6);
	///////////////////////////////////////////////////////////////////////
}

void CEthernetLayer::SetDestinAddress(unsigned char* pAddress)
{
	memcpy(m_sHeader.enet_dstaddr, pAddress, 6);
}

BOOL CEthernetLayer::Send(unsigned char* ppayload, int nlength)
{
	memcpy(m_sHeader.enet_data, ppayload, nlength);

	BOOL bSuccess = FALSE;
	//////////////////////// fill the blank ///////////////////////////////
	bSuccess = mp_UnderLayer->Send((unsigned char*)&m_sHeader, nlength + ETHER_HEADER_SIZE);
	///////////////////////////////////////////////////////////////////////

	return bSuccess;
}

BOOL CEthernetLayer::Receive(unsigned char* ppayload)
{
	PETHERNET_HEADER pFrame = (PETHERNET_HEADER)ppayload;

	BOOL bSuccess = FALSE;
	//////////////////////// fill the blank ///////////////////////////////
	bSuccess = mp_aUpperLayer[0]->Receive((unsigned char*)pFrame->enet_data);
	///////////////////////////////////////////////////////////////////////

	return bSuccess;
}