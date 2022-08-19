#include "player.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>
using namespace std;

void Player::draw_1(std::string e)
{
	graphics::Brush br;

	float h_1 = 1.0f * m_highlighted;

	SETCOLOR(br.fill_color, h_1,h_1,h_1 );
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string(e);
	graphics::drawRect(m_pos[0]+0.03, m_pos[1], PLAYER_SIZE * 1.23f, PLAYER_SIZE * 1.23f,br);
	
	SETCOLOR_1(br.fill_color,1.5f);
	br.texture = ASSET_PATH + std::string(e);
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
}

void Player::draw_2(std::string r)
{
	graphics::Brush br;

	float h_2 = 1.0f * m_highlighted;

	SETCOLOR(br.fill_color, h_2,h_2,h_2);
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string(r);
	graphics::drawRect(m_pos[0]-0.03f, m_pos[1], PLAYER_SIZE * 1.23f, PLAYER_SIZE * 1.23f, br);
	
	SETCOLOR(br.fill_color, 1.0f,1.0f,1.0f);
	br.texture = ASSET_PATH + std::string(r);
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
}


void Player::update()
{

}

bool Player::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < PLAYER_SIZE * 0.5f;
}

bool Player::intersect(Player* tgt)
{
	return distance(m_pos[0], m_pos[1], tgt->m_pos[0], tgt->m_pos[1]) < PLAYER_ATTACK_RANGE;
		
}



void Player::drawb(int t, int d)
{
	graphics::Brush br;
	br.texture = ASSET_PATH + std::string("Untitled-1-Brbf.png");
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1] - 1.5f, PLAYERB, PLAYER_SIZE, br);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.outline_opacity = 1.0f;
	graphics::setFont("DREDWERK.TTF");
	br.fill_opacity = 1.0f;
	string sr = to_string(t);
	graphics::drawText(m_pos[0], m_pos[1] - 1.99f, LETTERS, sr, br);

	string q;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.outline_opacity = 1.0f;
	graphics::setFont("DREDWERK.TTF");
	string st = to_string(d);
	graphics::drawText(m_pos[0], m_pos[1] - 1.69f, LETTERS, st, br);
}