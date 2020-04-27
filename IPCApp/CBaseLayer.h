#pragma once
class CBaseLayer
{
public:
	char* GetLayerName();

	CBaseLayer* GetUnderLayer();
	CBaseLayer* GetUpperLayer(int nindex);
	void			SetUnderUpperLayer(CBaseLayer* pUULayer = NULL);
	void			SetUpperUnderLayer(CBaseLayer* pUULayer = NULL);
	void			SetUnderLayer(CBaseLayer* pUnderLayer = NULL);
	void			SetUpperLayer(CBaseLayer* pUpperLayer = NULL);

	CBaseLayer(char* pName = NULL);
	virtual ~CBaseLayer();

	// param : unsigned char*	- the data of the upperlayer
	//         int				- the length of data
	virtual	BOOL	Send(unsigned char*, int) { return FALSE; }
	// param : unsigned char*	- the data of the underlayer
	virtual	BOOL	Receive(unsigned char* ppayload) { return FALSE; }
	virtual	BOOL	Receive() { return FALSE; }

protected:
	char* m_pLayerName;
	CBaseLayer* mp_UnderLayer;							// UnderLayer pointer
	CBaseLayer* mp_aUpperLayer[MAX_LAYER_NUMBER];		// UpperLayer pointer
	int				m_nUpperLayerCount;						// UpperLayer Count
};