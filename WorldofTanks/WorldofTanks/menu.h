#pragma once
#include <string>

class Menu {
	bool m_highlighted = false;
	bool m_active = false;

public:
	void draw_option(std::string a, int b);

	void setHighlitght(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }

	bool contains(float x, float y);


	//bool contains(float x, float y);

};
