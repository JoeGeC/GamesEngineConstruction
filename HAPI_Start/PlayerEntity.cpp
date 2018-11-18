#include "PlayerEntity.h"
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

using namespace HAPISPACE;

PlayerEntity::PlayerEntity(std::string spriteName) : Entity(spriteName)
{
}


PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update()
{
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& contData = HAPI.GetControllerData(0);

	//to move with keyboard
	if (keyData.scanCode['D'] || keyData.scanCode[HK_RIGHT])
	{
		if (keyData.scanCode['W'] || keyData.scanCode[HK_UP])
		{
			m_position.x += dSpeed;
			m_position.y -= dSpeed;
		}
		else if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN])
		{
			m_position.x += dSpeed;
			m_position.y += dSpeed;
		}
		else
		{
			m_position.x += speed;
		}
	}
	else if (keyData.scanCode['A'] || keyData.scanCode[HK_LEFT])
	{
		if (keyData.scanCode['W'] || keyData.scanCode[HK_UP])
		{
			m_position.x -= dSpeed;
			m_position.y -= dSpeed;
		}
		else if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN])
		{
			m_position.x -= dSpeed;
			m_position.y += dSpeed;
		}
		else
		{
			m_position.x -= speed;
		}
	}
	else if (keyData.scanCode['W'] || keyData.scanCode[HK_UP])
	{
		m_position.y -= speed;
	}
	else if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN])
	{
		m_position.y += speed;
	}

	//to move with xbox left joystick or dpad
	if (contData.isAttached)
	{
		int thumbX = contData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
		int thumbY = contData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];

		if (thumbX > HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_RIGHT])
		{
			if (thumbY > HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_UP])
			{
				m_position.x += dSpeed;
				m_position.y -= dSpeed;
			}
			else if (thumbY < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			{
				m_position.x += dSpeed;
				m_position.y += dSpeed;
			}
			else
			{
				m_position.x += speed;
			}
		}
		else if (thumbX < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_LEFT])
		{
			if (thumbY > HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_UP])
			{
				m_position.x -= dSpeed;
				m_position.y -= dSpeed;
			}
			else if (thumbY < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			{
				m_position.x -= dSpeed;
				m_position.y += dSpeed;
			}
			else
			{
				m_position.x -= speed;
			}
		}
		else if (thumbY > HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_UP])
			m_position.y -= speed;
		else if (thumbY < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			m_position.y += speed;
	}
		
}