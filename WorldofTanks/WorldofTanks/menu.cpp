#include "menu.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>
using namespace std;

void Menu::draw_option(std::string a, int b)
{
	graphics::Brush br;

	float h_1 = 1.0f ;

	SETCOLOR(br.fill_color, h_1, h_1, h_1);
	br.texture = ASSET_PATH + std::string("Untitled-1-Recovered-Recovered.png");
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.8f;
	graphics::drawRect(CANVAS_WIDTH / 2 , (CANVAS_HEIGHT / 2) + b, MENU_SIZE*2.5f, MENU_SIZE, br);

	SETCOLOR(br.fill_color,1.0f,1.0f,1.0f);
	br.outline_opacity = 1.0f ;
	graphics::setFont("DREDWERK.TTF");
	br.fill_opacity = 1.0f;
	graphics::drawText(CANVAS_WIDTH / 2 - 4.3, (CANVAS_HEIGHT / 2) + b, LETTER_SIZE, a, br);

}

//bool Menu::contains(float x, float y)
//{
	//return distance(x, y, m_pos[0], m_pos[1]) < PLAYER_SIZE * 1.23f;
//}