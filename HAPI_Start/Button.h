#pragma once

#include "Vector2.h"
#include "Visualisation.h"
#include "Rectangle.h"

class Button
{
private:
	Vector2 m_position{ 0, 0 };
	std::string m_spriteName;
	Rectangle m_buttonRect;
	bool m_clicked{ false };
	int m_lastClickTime{ 0 };
	bool m_leftButtonClick{ false };

public:
	Button(std::string spriteName, Vector2 pos);
	~Button();
	void Render(Visualisation &viz);
	void Update(Visualisation &viz);

	bool IsClicked() const { return m_clicked; }
	std::string GetSpriteName() const { return m_spriteName; }
	DWORD GetClickTime() const { return m_lastClickTime; }
};

