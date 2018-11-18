#pragma once
class Rectangle
{
public:
	Rectangle();
	~Rectangle();

	int m_left, m_right, m_top, m_bottom;

	Rectangle(int l, int r, int t, int b) : m_left(l), m_right(r), m_top(t), m_bottom(b) {};
	Rectangle(int w, int h) : m_left(0), m_right(w), m_top(0), m_bottom(h) {};

	int Width() const { return m_right - m_left; }
	int Height() const { return m_bottom - m_top; }

	void ClipTo(const Rectangle &other);
	void Translate(int dx, int dy);
};

