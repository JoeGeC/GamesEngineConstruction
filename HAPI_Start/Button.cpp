#include "Button.h"



Button::Button(std::string spriteName, Vector2 pos) : m_spriteName(spriteName), m_position(pos)
{
}


Button::~Button()
{
}

void Button::Update(Visualisation &viz)
{
	//rectangles
	m_buttonRect = viz.GetSpriteCollection().at(m_spriteName)->CreateRectangle();

	const HAPI_TMouseData &mouseData = HAPI.GetMouseData();
	m_buttonRect.Translate(m_position.x, m_position.y);

	DWORD time = HAPI.GetTime();
	if (time - m_lastClickTime > 200)
	{
		if (!((m_buttonRect.m_right < mouseData.x || m_buttonRect.m_left > mouseData.x)
			|| (m_buttonRect.m_bottom < mouseData.y || m_buttonRect.m_top > mouseData.y))
			&& mouseData.leftButtonDown)
		{
			m_clicked = !m_clicked;
			m_lastClickTime = time;
		}
	}
}
	

void Button::Render(Visualisation &viz)
{
	viz.RenderSprite(m_spriteName, (int)m_position.x, (int)m_position.y, true, 0);
}