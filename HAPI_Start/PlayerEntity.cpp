#include "PlayerEntity.h"
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

using namespace HAPISPACE;

PlayerEntity::PlayerEntity(std::string spriteName, int noOfFrames) : Entity(spriteName, noOfFrames)
{
}

PlayerEntity::~PlayerEntity()
{
}

void PlayerEntity::Update(Visualisation &viz)
{
	Vector2 pos{ GetPosition() };

	if (m_health <= 0)
		m_alive = false;

	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData& contData = HAPI.GetControllerData(0);

	//to move with keyboard
	if (keyData.scanCode['D'] || keyData.scanCode[HK_RIGHT])
	{
		if (keyData.scanCode['W'] || keyData.scanCode[HK_UP])
		{
			pos.x += m_dSpeed;
			pos.y -= m_dSpeed;
		}
		else if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN])
		{
			pos.x += m_dSpeed;
			pos.y += m_dSpeed;
		}
		else
		{
			pos.x += m_speed;
		}
	}
	else if (keyData.scanCode['A'] || keyData.scanCode[HK_LEFT])
	{
		if (keyData.scanCode['W'] || keyData.scanCode[HK_UP])
		{
			pos.x -= m_dSpeed;
			pos.y -= m_dSpeed;
		}
		else if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN])
		{
			pos.x -= m_dSpeed;
			pos.y += m_dSpeed;
		}
		else
		{
			pos.x -= m_speed;
		}
	}
	else if (keyData.scanCode['W'] || keyData.scanCode[HK_UP])
	{
		pos.y -= m_speed;
	}
	else if (keyData.scanCode['S'] || keyData.scanCode[HK_DOWN])
	{
		pos.y += m_speed;
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
				pos.x += m_dSpeed;
				pos.y -= m_dSpeed;
			}
			else if (thumbY < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			{
				pos.x += m_dSpeed;
				pos.y += m_dSpeed;
			}
			else
			{
				pos.x += m_speed;
			}
		}
		else if (thumbX < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_LEFT])
		{
			if (thumbY > HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_UP])
			{
				pos.x -= m_dSpeed;
				pos.y -= m_dSpeed;
			}
			else if (thumbY < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			{
				pos.x -= m_dSpeed;
				pos.y += m_dSpeed;
			}
			else
			{
				pos.x -= m_speed;
			}
		}
		else if (thumbY > HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_UP])
			pos.y -= m_speed;
		else if (thumbY < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || contData.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			pos.y += m_speed;
	}

	SetPosition(pos);
}

void PlayerEntity::Collision(int damage, string collider)
{
	m_health -= damage;
}