#include "defines.h"
#include "game.h"
#include "sgg/graphics.h"
#include <string>
#include "Event.h"
#include <cstdlib>

int k = 0;
int t = 2;
int l = 0;
int winner = 0;

void Game::updateStartScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	if (mx >= CANVAS_WIDTH / 2 - 4.3f && mx <= CANVAS_WIDTH / 2 + 4.3f && my >= CANVAS_HEIGHT / 2 -4.0f && my <= CANVAS_HEIGHT / 2 -2.5f && ms.button_left_pressed && m_state == STATE_INIT) {
		m_state = STATE_LOADING1;
	}
	if (mx >= CANVAS_WIDTH / 2 - 4.3f && mx <= CANVAS_WIDTH / 2 + 4.3f && my >= CANVAS_HEIGHT / 2 -1.0f && my <= CANVAS_HEIGHT / 2 +0.5f && ms.button_left_pressed && m_state == STATE_INIT) {
		m_state = STATE_LOADING2;
	}
	if (mx >= CANVAS_WIDTH / 2 - 4.3f && mx <= CANVAS_WIDTH / 2 + 4.3f && my >= CANVAS_HEIGHT / 2 +2.0f && my <= CANVAS_HEIGHT / 2 +3.5f && ms.button_left_pressed && m_state == STATE_INIT) {
		m_state = STATE_LOADING3;
	}
	

}

void Game::updateLevelScreen()
{
	processEvents();
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	Player* cur_player = nullptr;

	if (l == 0){
		if (t % 2 == 0)
			l_state = STATE_PLAYER1;
		else
			l_state = STATE_PLAYER2;
		l++;
	}

	for (auto player : m_players)
	{
		if (player->contains(mx, my) && t%2 == player->getPlayerNum() ) {

			player->setHighlitght(true);
			cur_player = player;
		}
		else
			player->setHighlitght(false);

	}
	if (ms.button_left_pressed && cur_player)
	{
		m_active_player = cur_player;
		m_active_player->setActive(true);
		for (auto player : m_players)
		{
			if (player != m_active_player)
				player->setActive(false);
		}
		m_init_pos_x = m_active_player->getPosX();
		m_init_pos_y = m_active_player->getPosY();

	}
	if (ms.dragging && m_active_player) 
	{
		if (distance(m_init_pos_x, m_init_pos_y, mx, my) < PLAYER_MOTION_RANGE)
		{
			
			for (auto p : m_players) {
				if (p == m_active_player)
					continue;
				if (p->getPosX() != mx || p->getPosY() != my){

					if (RAND0TO1() < 0.15f)
						addEvent(new SmokeEvent(mx, my));
					mx = PLAYER_SIZE * (0.5f + (int)(mx / PLAYER_SIZE));
					my = PLAYER_SIZE * (0.5f + (int)(my / PLAYER_SIZE));

					m_active_player->setPosX(mx);
					m_active_player->setPosY(my);

					l_state = STATE_MOVING;
				}
			}
		}
	}
	
	if (ms.button_left_released && m_active_player && (m_init_pos_x != m_active_player->getPosX() || m_init_pos_y != m_active_player->getPosY())) {
		t = t + 1;
		l = 0;

		m_target_player = nullptr;
		for (auto p : m_players)
		{
			if (p == m_active_player)
				continue;
			if (p->intersect(m_active_player) && p->getPlayerNum() != m_active_player->getPlayerNum() && p->getPosX() == m_active_player->getPosX() && ( ( p->getPlayerNum() == 0 && p->getPosY() < m_active_player->getPosY()) || (p->getPlayerNum() == 1 && p->getPosY() > m_active_player->getPosY())))
			{
				if (m_active_player->getPlayerNum()==0)
					addEvent(new fireevent(m_active_player->getPosX(), m_active_player->getPosY() + 1.0f));
				else
					addEvent(new fireevent(m_active_player->getPosX(), m_active_player->getPosY() - 1.0f));

				l_state = STATE_ATTACKING;
				m_target_player = p;
				int s = m_target_player->getStamina();
				m_target_player->setStamina( s - m_active_player->getAttack());

				if (m_target_player->getStamina() <= 0) {
					m_target_player->setAlive(false);
					addEvent(new explodeevent(m_target_player->getPosX(), m_target_player->getPosY()));
				}
			}
			else
			{
				l_state = STATE_IDLE;
			}
		}
		if (m_target_player) {
			if (m_target_player->getAlive() == false) {
				m_players.remove(m_target_player);
				delete m_target_player;
			}
		}
					
		m_active_player->setActive(false);
				
		l_state = STATE_IDLE;
		m_active_player->setActive(false);
		m_active_player = nullptr;
	}
	int i = 0;
	int j = 0;
	for (auto player : m_players)
	{
		player->update();

		if (player->getAlive()) 
		{
			if (player->getPlayerNum() == 0)
			{
				i=i+1;
			}
			else
			{
				j=j+1;
			}
		}
	}

	if (i == 0 || j == 0)
	{
		m_state = STATE_GAMEOVER;
		if (j == 0)
			winner = 1;
		else
			winner = 2;
	}
}

void Game::updateGameOver()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	if (mx >= CANVAS_WIDTH / 2 - 4.3f && mx <= CANVAS_WIDTH / 2 + 4.3f && my >= CANVAS_HEIGHT / 2 + 1.0f && my <= CANVAS_HEIGHT / 2 + 2.5f && ms.button_left_pressed && m_state == STATE_GAMEOVER) {
		m_state = STATE_INIT;
	}
	if (mx >= CANVAS_WIDTH / 2 - 4.3f && mx <= CANVAS_WIDTH / 2 + 4.3f && my >= CANVAS_HEIGHT / 2 + 4.0f && my <= CANVAS_HEIGHT / 2 + 5.5f && ms.button_left_pressed && m_state == STATE_GAMEOVER) {
		exit(0);
	}
}

void Game::drawStartScreen()
{
	if (m_state == STATE_INIT) {
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		SETCOLOR_1(br.fill_color, 1.0f);

		br.texture = ASSET_PATH + std::string("menu.png");
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		Menu* p = new Menu();
		p->draw_option("EARTH GAME", -3);
		p->draw_option("AIR GAME", 0);
		p->draw_option("SEA GAME", 3);
	}
}

void Game::drawLevelScreen(std::string p1,std::string p2,std::string p3)
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string(p3);
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::Brush sq;
	sq.outline_opacity = 0.3f;
	sq.fill_opacity = 0.0f;
	for(int i = 0; i<CANVAS_WIDTH / PLAYER_SIZE; i++)
		for (int j = 0; j < CANVAS_WIDTH / PLAYER_SIZE; j++)
		{
			float x = (i + 0.5f) * PLAYER_SIZE;
			float y = (j + 0.5f) * PLAYER_SIZE;
			if (m_active_player && distance(x, y, m_init_pos_x, m_init_pos_y) < PLAYER_MOTION_RANGE)
			{
				SETCOLOR(sq.fill_color, 1.0f, 1.0f, 1.0f)
				sq.fill_opacity = 0.4f;
			}
			else
			{
				sq.fill_opacity = 0.0f;
			}
			graphics::drawRect(x, y, PLAYER_SIZE, PLAYER_SIZE, sq);
		}
	
	for (auto ev : m_Events)
		ev->draw();

	
	for (auto player : m_players)
	{
		if (player->getPlayerNum() == 1) {
			player->draw_1(p1);
		}
		else {
			player->draw_2(p2);
		}
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	for (auto player : m_players)
	{
		if (player->contains(mx, my) && !ms.button_left_down && t % 2 == player->getPlayerNum()) {
			player->drawb(player->getStamina(), player->getAttack());
		}

	}

	if (t % 2 == 0) 
		drawturn(1.0f, 1.0f, "PLAYER 1 IS YOUR TURN");
	
	else
		drawturn(CANVAS_WIDTH - 5.0f, CANVAS_HEIGHT - 1.0f, "PLAYER 2 IS YOUR TURN");

}



void Game::draw()
{
	if (m_state!=STATE_LOADING1 && m_state != STATE_LOADING2 && m_state != STATE_LOADING1)
	{
		drawStartScreen();
		//return;
	}
	if (m_state==STATE_LOADING1) {
		drawLevelScreen("tank1.png","tank2.png","tank-back.png");
		//return;
	}
	if (m_state==STATE_LOADING2) {
		drawLevelScreen("plane2.png","plane1.png", "plane-back.png");
		//return;
	}
	if (m_state==STATE_LOADING3) {
		drawLevelScreen("boat2.png","boat1.png", "sea-back.png");
		//return;
	}
	if (m_state == STATE_GAMEOVER) {
		drawGameOver(winner);
	}
}

void Game::drawturn(int x, int y, std::string t)
{
	graphics::Brush br;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.outline_opacity = 1.0f;
	graphics::setFont("DREDWERK.TTF");
	br.fill_opacity = 1.0f;
	graphics::drawText(x, y, 0.3f, t, br);
}

void Game::drawGameOver(int winner)
{
	if (m_state == STATE_GAMEOVER) {
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		SETCOLOR_1(br.fill_color, 1.0f);

		br.texture = ASSET_PATH + std::string("gameover.png");
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		br.outline_opacity = 1.0f;
		graphics::setFont("DREDWERK.TTF");
		br.fill_opacity = 1.0f;
		std::string w = "WINNER IS PLAYER " + std::to_string(winner);
		graphics::drawText(CANVAS_WIDTH/2 - 5.0f, CANVAS_HEIGHT/2 - 1, 1.0f, w, br);

		Menu* p = new Menu();
		p->draw_option("MENU", 2);
		p->draw_option("EXIT", 5);
	}
}



void Game::update()  
{
	
	if (m_state == STATE_INIT)
	{
		//addEvent(new FadeFromBlackEvent());
		updateStartScreen();
		return;
	}
	if (m_state == STATE_GAMEOVER)
	{
		//addEvent(new FadeFromBlackEvent());
		updateGameOver();
		return;
	}
	if (m_state == STATE_LOADING1 || m_state == STATE_LOADING2 || m_state == STATE_LOADING3)
		//addEvent(new FadeFromBlackEvent());
		
		init();
		updateLevelScreen();
		l_state = STATE_IDLE;	
}

void Game::init()
{
	if (k == 0) 
	{
		float ix = 0.0f;
		for (int i = 0; i < 4; i++)
		{
			float jy = 0.0f;
			for (int j = 0; j < 2; j++)
			{
				Player* p = new Player();
			
				p->setStamina(6);
				p->setAttack(2);
				p->setAlive(true);
				
				if ((j + 2) % 2 == 0)
					p->setPlayerNum(0);
				else
					p->setPlayerNum(1);
				
				p->setPosX(int(CANVAS_WIDTH * (ix + 0.72f) / 4.0f));
				p->setPosY(int(CANVAS_HEIGHT * (jy + 0.4f) / 2.0f));

				m_players.push_front(p);

				jy = jy + 1.3f;
			}
			ix = ix + 0.8571f;
		} 
	}
	k = k + 1;
	graphics::preloadBitmaps(ASSET_PATH);
}

Game::~Game()
{
	for (auto p:m_players)
	{
		delete p;
	}
	m_players.clear();
}

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game;
	return m_instance;
}

void Game::processEvents()
{
	for (auto e : m_Events)
	{
		e->update();
	}

	m_Events.remove_if([](Event* ev) {return !ev->active(); });
}

void Game::addEvent(Event* evt)
{
	m_Events.push_front(evt);
}

Game* Game::m_instance = nullptr;