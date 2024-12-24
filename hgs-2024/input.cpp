//===========================
//
//  ���͏���[input.cpp]
// Author:TEAM_2
//
//===========================

//*****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "input.h"

//*********************
// �}�N����`
//*********************
#define NUM_KEY_MAX (256) // �L�[�̍ő吔

//********************
// �\���̂��`
//********************
typedef struct
{
	bool bWasDir;		// �O��X���Ă������ǂ���
	bool bIsDir;		// ����X�������ǂ���
	bool bTrigger;		// �X�e�B�b�N�̃g���K�[
	bool bRepeat;		// �X�e�B�b�N�̃��s�[�g
	DWORD prevTime;		// ����
}Stick;

//*******************
//�񋓌^
//*******************
typedef enum
{
	STICK_TYPE_LEFT = 0,
	STICK_TYPE_RIGHT,
	STICK_TYPE_MAX
}STICK_TYPE;

//*******************
//�O���[�o���ϐ�
//*******************
LPDIRECTINPUT8 g_pInput = NULL;					// Directinput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		// ���̓f�o�C�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDIMouse = NULL;			// �}�E�X�f�o�C�X
DIMOUSESTATE g_zdiMouseState;					// �}�E�X���
DIMOUSESTATE g_MousePress;
DIMOUSESTATE g_MouseTrigger;
static DIMOUSESTATE g_CurrentMouseState;		// �}�E�X�̌��݂̓��͏��
static DIMOUSESTATE g_PrevMouseState;			// �}�E�X�̈�t���[���O�̓��͏��

BYTE g_aKeyState[NUM_KEY_MAX];					// �L�[�{�[�h�̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];					// �ߋ��̓��͓��e��ۑ�
XINPUT_STATE g_joyKeyState;						// �W���C�p�b�h�̃v���X���
XINPUT_STATE g_OldKeyState;						// �W���C�p�b�h�̃v���X���(����)
XINPUT_STATE g_joyKeyStateTrigger;				// �W���C�p�b�h�̃g���K�[���
												   
Stick g_stick[STICK_TYPE_MAX];					// �X�e�B�b�N�\���̂̏��
												   
bool g_Rstickrepeat;							// �X�e�B�b�N�̃��s�[�g

//=======================
// �L�[�{�[�h�̏���������
//=======================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput,
		NULL)))
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X����
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;


	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �L�[�{�[�h�̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//======================
// �L�[�{�[�h�̏I������
//======================
void UninitKeyboard(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	// �A�N�Z�X���̔j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//======================
// �L�[�{�[�h�̍X�V����
//======================
void UpdateKeyboard(void)
{

	BYTE aKeyState[NUM_KEY_MAX];						// �L�[�{�[�h�̓��͏��
	int nCntkey;
	for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
	{
		g_aOldState[nCntkey] = g_aKeyState[nCntkey];	// �L�[�{�[�h�̃v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			g_aKeyState[nCntkey] = aKeyState[nCntkey];	// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();			// �L�[�{�[�h�̃A�N�Z�X�����l��
	}
}
//=============================
// �L�[�{�[�h�̃v���X�����擾
//=============================
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;		// 3�����Z�q���g�p
}
//=============================
// �L�[�{�[�h�������^�b�v
//=============================
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//================================
// �L�[�{�[�h�𒷉���(�`���[�W�U��)
//================================
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//===============================
// �L�[�{�[�h�̌p������(�A�ˏ���)
//===============================
bool KeyboardRepeat(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//==============================
// �W���C�p�b�h�̏���������
//==============================
HRESULT InitJoypad(void)
{
	// �������̃N���A
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	// �������̃N���A
	memset(&g_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// Xinput�̃X�e�[�g��ݒ�(�L����)
	XInputEnable(true);

	// ������
	g_Rstickrepeat = false;		

	return S_OK;
}
//==============================
// �W���C�p�b�h�̏I��
//==============================
void UninitJoypad(void)
{
	// Xinput�̃X�e�[�g��ݒ�(������)
	XInputEnable(false);
}
//==============================
// �W���C�p�b�h�̍X�V
//==============================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;			// ���͏����擾

	//�W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;				// �������Ƃ��̓��͏��
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;		// 1F�O�̓��͏��

		g_joyKeyStateTrigger.Gamepad.wButtons = Button &~OldButton;

		g_joyKeyState = joykeyState;							// �W���C�p�b�h�̃v���X����ۑ�(�i�[)
	}

	// �X�V����
	UpdateStick();
}
//==============================
// �v���X�����擾
//==============================
bool JoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//==============================
// �g���K�[�����擾
//==============================
bool JoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//==========================
// �p�b�h�̃����[�X����
//==========================
bool JoypadRelease(JOYKEY key)
{
	bool Joykey = false;

	if (g_OldKeyState.Gamepad.wButtons & (0x01 << key) && !((g_OldKeyState.Gamepad.wButtons & (0x01 << key))))
	{
		Joykey = true;
	}

	return false;
}
//==========================
// �p�b�h�̃��s�[�g����
//==========================
bool JoypadRepeat(JOYKEY key)
{
	bool Joykey = false;

	if (g_OldKeyState.Gamepad.wButtons & (0x01 << key) && !((g_OldKeyState.Gamepad.wButtons & (0x01 << key))))
	{
		Joykey = true;
	}

	return Joykey;
}
//======================
// �p�b�h��L�X�e�B�b�N����
//======================
bool GetJoyStick(void)
{
	//���[�J���ϐ��錾
	bool joykey = false;

	//���S����Ȃ�������
	if (g_joyKeyState.Gamepad.sThumbLX >= 100 ||
		g_joyKeyState.Gamepad.sThumbLX <= -100 ||
		g_joyKeyState.Gamepad.sThumbLY >= 100 ||
		g_joyKeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}

	return joykey;
}
//=========================
// �p�b�h��R�X�e�B�b�N�̎擾
//=========================
bool GetJoyStickRrepeat(void)
{
	return g_Rstickrepeat;
}
//==============================
// �p�b�h��R�X�e�B�b�N�̃��s�[�g
//==============================
void UpdateStick(void)
{
	g_stick[STICK_TYPE_RIGHT].bWasDir = g_stick[STICK_TYPE_RIGHT].bIsDir;

	//�X�e�B�b�N�̎擾
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	// ���݂̎������擾
	DWORD currTime = timeGetTime();

	//���S����Ȃ�������
	g_stick[STICK_TYPE_RIGHT].bIsDir = false;

	if (g_joyKeyState.Gamepad.sThumbRX >= 1000 ||
		g_joyKeyState.Gamepad.sThumbRX <= -1000 ||
		g_joyKeyState.Gamepad.sThumbRY >= 1000 ||
		g_joyKeyState.Gamepad.sThumbRY <= -1000)
	{
		g_stick[STICK_TYPE_RIGHT].bIsDir = true;
	}

	g_Rstickrepeat = false;

	// �g���K�[����
	if (g_stick[STICK_TYPE_RIGHT].bIsDir == true && g_stick[STICK_TYPE_RIGHT].bWasDir == false)
	{ // �X�e�B�b�N������X���Ă��� ���� �O��X���Ă��Ȃ�
		g_stick[STICK_TYPE_RIGHT].bTrigger = true;

		// ���Ԃ�ێ� (FPS ����̂Ƃ��݂����Ɏ������擾����)
		g_stick[STICK_TYPE_RIGHT].prevTime = currTime;
	}

	// ���s�[�g����
	DWORD duration = (currTime - g_stick[STICK_TYPE_RIGHT].prevTime);
	if (g_stick[STICK_TYPE_RIGHT].bIsDir == true && duration >= 160)
	{ // �X�e�B�b�N���X���Ă��� ���� ���t���[���o�� (���̏ꍇ���� 60 �t���[���Ȃ̂� 1 �b)
		g_stick[STICK_TYPE_RIGHT].bRepeat = true;

		// ���Ԃ�ێ� (FPS ����̂Ƃ��݂����Ɏ������擾����)
		g_stick[STICK_TYPE_RIGHT].prevTime = currTime;

		g_Rstickrepeat = true;
	}

}
//========================
// �X�e�B�b�N���̎擾
//========================
XINPUT_STATE* GetJoyStickAngle(void)
{
	return &g_joyKeyState;
}
//===========================================
// DirectInput�̃}�E�X�f�o�C�X�p�̏���������
//===========================================
bool InitDInputMouse(HWND hWnd)
{
	HRESULT ret = S_FALSE;
	if (g_pInput == NULL)
	{
		return false;
	}

	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	ret = g_pInput->CreateDevice(GUID_SysMouse, &g_pDIMouse, NULL);
	if (FAILED(ret))
	{
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	ret = g_pDIMouse->SetDataFormat(&c_dfDIMouse);	// �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	if (FAILED(ret))
	{
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	ret = g_pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret))
	{
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	ret = g_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	g_pDIMouse->Acquire();


	return true;
}
//=========================================
// DirectInput�̃}�E�X�f�o�C�X�p�̉������
//=========================================
bool ReleaseDInputMouse()
{
	// DirectInput�̃f�o�C�X���J��
	if (g_pDIMouse) 
	{
		g_pDIMouse->Release();
		g_pDIMouse = NULL;
	}

	return true;
}
//=========================================
// DirectInput�̃}�E�X�f�o�C�X�p�̍X�V����
//=========================================
void UpdateMouse()
{
	DIMOUSESTATE g_zdiMouseState_bak;	// �}�E�X���(�ω����m�p)

	if (SUCCEEDED(g_pDIMouse->GetDeviceState(sizeof(g_zdiMouseState_bak), &g_zdiMouseState_bak)))
	{
		g_MousePress = g_zdiMouseState_bak;
	}

	// �X�V�O�ɍŐV�}�E�X����ۑ�����
	g_PrevMouseState = g_CurrentMouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
	HRESULT	hresult = g_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	if (FAILED(hresult))
	{
		g_pDIMouse->Acquire();
		hresult = g_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}

	else
	{
		g_pDIMouse->Acquire();
	}

	// �}�E�X���W���擾����
	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);
}
//==========================================
// �}�E�X�̃v���X���
//==========================================
bool GetMousePress(int nKey)
{
	return ((g_MousePress.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}
//==========================================
// �}�E�X�̃g���K�[���
//==========================================
bool GetMouseTrigger(int nKey)
{
	if (!(g_PrevMouseState.rgbButtons[nKey] &0x80) &&
		g_CurrentMouseState.rgbButtons[nKey] & 0x80)
	{
		return true;
	}

	return false;
}
//==========================================
// DirectInput�̃}�E�X�f�o�C�X��Ԏ擾����
//==========================================
DIMOUSESTATE GetMouseState()
{
	return g_MousePress;
}
//===================================================
// DirectInput�̃}�E�X�f�o�C�X��Ԏ擾����(Trigger)
//===================================================
DIMOUSESTATE GetMouseTriggerState()
{
	return g_MouseTrigger;
}
