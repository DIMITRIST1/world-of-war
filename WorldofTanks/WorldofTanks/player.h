#pragma once
#include <string>

class Player {
	float m_pos[2];
	float m_color[1];

	float m_orientation;
	int m_num;
	bool m_highlighted = false;
	bool m_active = false;
	bool m_alive = true;
	int m_stamina;
	int m_attack;

public:
	void draw_1(std::string e);
	void draw_2(std::string r);
	void update();
	void drawb(int t, int d);

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	int getPlayerNum() { return m_num; }
	bool getAlive() { return m_alive; }
	int getStamina() { return m_stamina; }
	int getAttack() { return m_attack; }

	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setAlive(bool a) { m_alive = a; }
	void setHighlitght(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }
	void setPlayerNum(int s) { m_num = s; }
	void setStamina(int f) { m_stamina = f; }
	void setAttack(int g) { m_attack = g; }

	bool contains(float x, float y);
	bool intersect(Player* target);


};
