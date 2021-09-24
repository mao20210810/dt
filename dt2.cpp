class ScreenInfo
{
public:
	char pad_0x0000[0x34]; //0x0000
	__int32 iScreenWidth; //0x0034 
	__int32 iScreenHeight; //0x0038 
};
 
class GameRenderer
{
public:
	char pad_0x0000[0x8]; //0x0000
	char* DeviceName; //0x0008 
	char pad_0x0010[0x18]; //0x0010
	char* DriverVersion; //0x0028 
	char pad_0x0030[0x498]; //0x0030
	ScreenInfo* m_pScreenInfo; //0x04C8  
};
 
class CHealthComponent
{
public:
	char pad_0x0000[0xA4]; //0x0000
	__int32 m_Health; //0x00A4 
	__int32 m_MaxHealth; //0x00A8 
};//Size=0x0140
 
class CAmmo
{
public:
	__int64 m_WeaponId1; //0x0000
	__int64 m_WeaponId2;
	int32_t iClipAmount; //0x0010
	char _0x0014[4]; // 0x0014
};//Size=0x018
 
class CWeaponInfo
{
public:
	char pad_0x0000[0x18]; //0x0000
	Array<CAmmo> m_pAmmo;
 
	CAmmo* getAmmo(int index)
	{
		return (CAmmo*)&m_pAmmo.m_firstElement[index];
	}
 
};//Size=0x0440
 
class CTeleport
{
public:
	char pad_0x0000[0x64]; //0x0000
	float flHeight; //0x0064 
	char pad_0x0068[0x8]; //0x0068
	D3DXVECTOR3 vPosition; //0x0070 
	char pad_0x007C[0x24]; //0x007C
	D3DXVECTOR3 vSpeed; //0x00A0 
	char pad_0x00AC[0xC]; //0x00AC
	float flSpeed; //0x00B8 
};
 
class CAnimation
{
public:
	char pad_0x0000[0x3B0]; //0x0000
	CTeleport* m_pNPCTeleBase; //0x0200 
};
 
class Agent
{
public:
	char pad_0x0000[0x70]; //0x0000
	D3DXVECTOR3 vPosition; //0x0070 
	char pad_0x007C[0x194]; //0x007C
	CAnimation* m_pAnimation; //0x0210 
	char pad_0x0218[0x1B0]; //0x0218
	__int32 iRank; //0x03C8 
	__int32 iDZRank; //0x03CC 
	char pad_0x03D0[0x180]; //0x03D0
	CWeaponInfo* m_pAmmo; //0x0550 
	char pad_0x0558[0x8]; //0x0558
	IndexInfo* m_pIndexInfo; //0x0560 
	char pad_0x0568[0xA8]; //0x0568
	CHealthComponent* m_pHealthComponent; //0x0610 
	char pad_0x0618[0x220]; //0x0618
	char playerName[24]; //0x0838
};
 
class CAimAngles
{
public:
	char pad_0x0000[0xC0]; //0x0000
	float flYaw; //0x00C0 
	float flPitch; //0x00C4 
	char pad_0x00C8[0x38]; //0x00C8
};
 
class CAimAnglesBase
{
public:
	char pad_0x0000[0x78]; //0x0000
	CAimAngles* m_pAimAngles; //0x0078 
};
 
class CMatrix
{
public:
	char pad_0x0000[0x10]; //0x0000
	D3DXMATRIX WorldMatrix; //0x0010 
	D3DXMATRIX ProjectionMatrix; //0x0050 
	char pad_0x0090[0x18]; //0x0090
	CAimAnglesBase* m_pAimanglesBase; //0x00A8 
};
 
class CMatrixBase
{
public:
	char pad_0x0000[0x20]; //0x0000
	CMatrix* m_pMatrix; //0x0020 
};
 
class CObject
{
public:
	char pad_0x0000[0x2F0]; //0x0000
	CMatrixBase* m_pMatrixBase; //0x02F0 
	char pad_0x02F8[0x1A0]; //0x02F8
	Agent** m_pEntList; //0x0498 
	__int32 numOfEntities; //0x04A0 
	__int32 maxNumOfEntites; //0x04A4 
 
	Agent* getObject(int index)
	{
		if (index >= 0 && index <= numOfEntities)
		{
			return (Agent*)m_pEntList[index];
		}
		else
		{
			return NULL;
		}
	}
};
 
class Client
{
public:
	char pad_0x0000[0x28]; //0x0000
	CObject* m_pObject; //0x0028 
	char pad_0x0030[0x8]; //0x0030
	void* m_pKeyInput; //0x0038 
 
};//Size=0x0030
 
class RLClient
{
public:
	char pad_0x0000[0x130]; //0x0000
	Client* m_pClient; //0x0130 
};//Size=0x0128
 
class IndexInfo
{
public:
	// not completely sure what's in here.
	struct Info
	{
		float unknown; // 0 - 4
		float data; // 4 - 8
		char poop[0x38];
	};
 
public:
	Info* GetInfoByIndex(unsigned int index)
	{
		if (!m_indexThing || !m_indexThing->info)
			return nullptr;
 
		return &m_indexThing->info[index];
	}
private:
	char unknown[0x28];
 
	struct IndexUnknown
	{
		char unknown[0x78];
		// array
		Info* info;
	} *m_indexThing;
};
 
class IndexModule
{
public:
	struct Indexer
	{
		uintptr_t GetOffset();
		std::string GetName();
		bool IsPointerName();
 
		char unknown[0x50];
		unsigned int index; // 0x50
		unsigned int unk; // 0x54
		char* namePtr; // 0x58
		unsigned int restOfName;
		unsigned int flags; // 0x64;
	};
 
	enum
	{
		//Spread
		AimSpreadMaxFinal = 3,
		AimSpreadMinFinal = 4,
		CoverAimSpreadMaxFinal = 27,
		CoverAimSpreadMinFinal = 28,
		CoverSpreadMaxFinal = 29,
		CoverSpreadMinFinal = 30,
 
		//Recoil
		HorizontalRecoilBorderLeftFinal = 71,
		HorizontalRecoilBorderRightFinal = 72,
		HorizontalRecoilLeftFinal = 73,
		HorizontalRecoilRecoveryTimeMSFinal = 74,
		HorizontalRecoilRightFinal = 75,
		HorizontalRecoilTimeMSFinal = 76,
 
		//RPM
		RPMFinal = 110,
 
		//Recoil
		RecoilBaseFinal = 119,
		RecoilClimbTimeMSFinal = 120,
		RecoilIncreasePerBulletFinal = 121,
		RecoilMaxFinal = 122,
		RecoilMinFinal = 123,
		RecoilRecoveryPerSecondFinal = 124,
		RecoilRecoveryTimeMSFinal = 125,
		RecoilResetTimeMSFinal = 126,
 
		//Reload
		ReloadTimeMSFinal = 127,
		EmptyClipFirstRoundReloadTimeMSFinal = 128,
		InitialShellReloadTimeMSFinal = 129,
		ReloadEndTimeMSFinal = 130,
		
		//Spread
		SpreadIncreaseSpeedFinal = 146,
		SpreadIncreaseTimeMSFinal = 147,
		SpreadMaxFinal = 148,
		SpreadMinFinal = 149,
		SpreadMovementModFinal = 150,
		SpreadReductionSpeedFinal = 151,
		
		//Sway
		AimSwayMinHorizontalFinal = 255,
		AimSwayMaxHorizontalFinal = 256,
		AimSwayMinVerticalFinal = 257,
		AimSwayMaxVerticalFinal = 258,
		AimSwaySpeedModifierFinal = 259,
	};
 
	char pad_0x0000[0x98]; //0x0000
	IndexModule::Indexer** pList; //0x0098
public:
	static IndexModule* Get();
 
public:
	Indexer* GetIndexer(int index);
private:
};