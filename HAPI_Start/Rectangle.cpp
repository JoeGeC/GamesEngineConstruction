#include "Rectangle.h"
#include <algorithm>

Rectangle::Rectangle()
{
}


Rectangle::~Rectangle()
{
}

void Rectangle::ClipTo(const Rectangle &other)
{
	m_left = std::max(m_left, other.m_left); //returns greater value
	m_right = std::min(m_right, other.m_right); //returns smaller value
	m_top = std::max(m_top, other.m_top);
	m_bottom = std::min(m_bottom, other.m_bottom);
}

void Rectangle::Translate(int dx, int dy)
{
	m_left += dx;
	m_right += dx;
	m_top += dy;
	m_bottom += dy;
}

void Rectangle::ShrinkRect()
{
	m_left += m_right / 10;
	m_right -= m_right / 10;
	m_top += m_bottom / 10;
	m_bottom -= m_bottom / 10;
}