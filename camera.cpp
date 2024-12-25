//==========================
//
// �J�������� [camera.cpp]
// Author: TEAM_2
//
//==========================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "camera.h"
#include "input.h"
#include "player.h"

//*****************************
// �O���[�o���ϐ��錾
//*****************************
Camera g_camera;				// �J�������

//=========================
// �J�����̏���������
//=========================
void InitCamera(void)
{
	// �ϐ��̏�����
	g_camera.posV = D3DXVECTOR3(0.0f, 280.0f, -20.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f,0.0f);				// �J�����̌��Ă���ʒu
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	g_camera.rot = D3DXVECTOR3(D3DX_PI * 0.65f, 0.0f, 0.0f);	// �p�x
	g_camera.g_CameraMode = CAMERAMODE_PLAYER;					// �������

	float fRotx = g_camera.posV.x - g_camera.posR.x;
	float fRoty = g_camera.posV.y - g_camera.posR.y;
	float fRotz = g_camera.posV.z - g_camera.posR.z;

	// ���_���璍���_�܂ł̋���
	g_camera.fDistance = sqrtf((fRotx * fRotx) + (fRoty * fRoty) + (fRotz * fRotz));	
}
//=========================
// �J�����̏I������
//=========================
void UninitCamera(void)
{
	// ����
}
//=========================
// �J�����̍X�V����
//=========================
void UpdateCamera(void)
{
	// �v���C���[���擾
	Player* pPlayer = GetPlayer();

	//// �}�E�X�����擾
	//DIMOUSESTATE pMouse = GetMouseState();

	// �J�����̉E�X�e�B�b�N
	StickCamera();

	//if (GetMousePress(0))
	//{// ���{�^���N���b�N
	//	// �J�����̉�]
	//	g_camera.rot.y += pMouse.lX * 0.001f;

	//	// �p�x�̐��K��
	//	if (g_camera.rot.y < -D3DX_PI)
	//	{// D3DX_PI��菬�����Ȃ�����
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}
	//	else if (g_camera.rot.y > D3DX_PI)
	//	{// D3DX_PI���傫���Ȃ�����
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}
	//}

	//******************
	// ���_�̐���
	//******************
	//if (GetKeyboardPress(DIK_LEFT) == true || JoypadPress(JOYKEY_LEFT_B))
	//{// LEFT�L�[�������ꂽ

	//	// �J�����̉�]
	//	g_camera.rot.y -= 0.03f;

	//	// �p�x�̐��K��
	//	if (g_camera.rot.y < -D3DX_PI)
	//	{// D3DX_PI��菬�����Ȃ�����
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}
	//}

	//if (GetKeyboardPress(DIK_RIGHT) == true || JoypadPress(JOYKEY_RIGHT_B))
	//{// RIGHT�L�[�������ꂽ
	//	// �J�����̉�]
	//	g_camera.rot.y += 0.03f;

	//	// �p�x�̐��K��
	//	if (g_camera.rot.y > D3DX_PI)
	//	{// D3DX_PI���傫���Ȃ�����
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}

	//}

#ifdef _DEBUG

	if (GetKeyboardPress(DIK_UP))
	{// UP�L�[�������ꂽ
		// �J�����̉�]
		g_camera.rot.x += 0.03f;

		// �p�x�̐��K��
		if (g_camera.rot.x > D3DX_PI)
		{// D3DX_PI��菬�����Ȃ�����
			g_camera.rot.x -= D3DX_PI * 2.0f;
		}

	}
	if (GetKeyboardPress(DIK_DOWN))
	{// DOWN�L�[�������ꂽ
		// �J�����̉�]
		g_camera.rot.x -= 0.03f;

		// �p�x�̐��K��
		if (g_camera.rot.x < -D3DX_PI)
		{// D3DX_PI��菬�����Ȃ�����
			g_camera.rot.x += D3DX_PI * 2.0f;
		}
	}

#endif // DEBUG

	
	if (g_camera.rot.x <= D3DX_PI * 0.55f)
	{// �J�����̉���

		g_camera.rot.x = D3DX_PI * 0.55f;
	}
	else if (g_camera.rot.x >= D3DX_PI * 0.9f)
	{// �J�����̏��

		g_camera.rot.x = D3DX_PI * 0.9f;
	}

	// �J�����̎��_�̏��
	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.x) * sinf(g_camera.rot.y) * g_camera.fDistance;
	g_camera.posV.y = g_camera.posR.y - cosf(g_camera.rot.x) * g_camera.fDistance;
	g_camera.posV.z = g_camera.posR.z - sinf(g_camera.rot.x) * cosf(g_camera.rot.y) * g_camera.fDistance;


	switch (g_camera.g_CameraMode)
	{// ���[�h�ؑ�
	case CAMERAMODE_NONE:
		break;

	case CAMERAMODE_PLAYER:
		// �v���C���[�ɒǏ]������
		g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rotDestPlayer.y) * 1.0f;
		g_camera.posRDest.y = pPlayer->pos.y + cosf(pPlayer->rotDestPlayer.y) * 1.0f;
		g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rotDestPlayer.y) * 1.0f;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posVDest.y = pPlayer->pos.y - cosf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fDistance;

		g_camera.posR.x += ((g_camera.posRDest.x - g_camera.posR.x) * 0.3f);
		g_camera.posR.z += ((g_camera.posRDest.z - g_camera.posR.z) * 0.3f);
		g_camera.posR.y += ((g_camera.posRDest.y - g_camera.posR.y) * 0.3f);

		g_camera.posV.x += ((g_camera.posVDest.x - g_camera.posV.x) * 0.3f);
		g_camera.posV.z += ((g_camera.posVDest.z - g_camera.posV.z) * 0.3f);

		break;

	default:
		break;
	}
#ifdef _DEBUG

	if (KeyboardTrigger(DIK_F2))
	{// ���[�h�ؑ�
		if (g_camera.g_CameraMode == CAMERAMODE_NONE)
		{// �Ǐ]���[�h
			g_camera.g_CameraMode = CAMERAMODE_PLAYER;
		}
		else if (g_camera.g_CameraMode == CAMERAMODE_PLAYER)
		{// �ʏ���
			g_camera.g_CameraMode = CAMERAMODE_NONE;
		}
	}

#endif // !_DEBUG
}
//=========================
// �J�����̐ݒ菈��
//=========================
void SetCamera(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X���擾
	pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
						&g_camera.posV,
						&g_camera.posR,
						&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,
								1450.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}
//=========================
// �J�����̎擾����
//=========================
Camera* GetCamera()
{
	return &g_camera;
}
//=========================
// �J�����̂��߂̉E�X�e�B�b�N����
//=========================
void StickCamera(void)
{
	// �X�e�B�b�N
	XINPUT_STATE* pStick = GetJoyStickAngle();

	if (GetJoyStick())
	{
		float RStickAngleY = pStick->Gamepad.sThumbRY;
		float RStickAngleX = pStick->Gamepad.sThumbRX;

		float DeadZone = 10920.0f;
		float fMag = sqrtf((RStickAngleX * RStickAngleX) + (RStickAngleY * RStickAngleY));

		if (fMag > DeadZone)
		{
			if (pStick->Gamepad.sThumbRX < -10920.0f)
			{
				// �p�x
				g_camera.rot.y -= 0.03f;

				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * sinf(g_camera.rot.y) * g_camera.fDistance;
				g_camera.posV.z = g_camera.posR.z - sinf(g_camera.rot.y) * cosf(g_camera.rot.y) * g_camera.fDistance;

			}
			else if (pStick->Gamepad.sThumbRX > 10920.0f)
			{
				// �p�x
				g_camera.rot.y += 0.03f;

				g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * sinf(g_camera.rot.y) * g_camera.fDistance;
				g_camera.posV.z = g_camera.posR.z - sinf(g_camera.rot.y) * cosf(g_camera.rot.y) * g_camera.fDistance;

			}


			// �p�x�̐��K��
			if (g_camera.rot.y > D3DX_PI)
			{// D3DX_PI���傫���Ȃ�����
				g_camera.rot.y -= D3DX_PI * 2.0f;
			}

			// �p�x�̐��K��
			if (g_camera.rot.y < -D3DX_PI)
			{// D3DX_PI��菬�����Ȃ�����
				g_camera.rot.y += D3DX_PI * 2.0f;
			}
		}
	}
}