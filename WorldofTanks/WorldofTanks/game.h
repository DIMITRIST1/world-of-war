#pragma once
#include <list>
#include "player.h"
#include "menu.h"
#include "Event.h"

class Game {
public:
	enum game_state_t {STATE_INIT,STATE_LOADING1,STATE_LOADING2,STATE_LOADING3, STATE_GAMEOVER};
	enum loading_state_t{STATE_START, STATE_IDLE, STATE_PLAYER1, STATE_PLAYER2,STATE_MOVING, STATE_ATTACKING};
protected:
	static Game* m_instance;
	std::list<Player*> m_players;

	Player* m_active_player = nullptr;
	Player* m_target_player = nullptr;
	
	std::list<Event*> m_Events;

	game_state_t m_state = STATE_INIT;
	loading_state_t l_state = STATE_START;
	float m_init_pos_x;
	float m_init_pos_y;

	
	void updateStartScreen();
	void updateLevelScreen();
	void updateGameOver();
	void drawStartScreen();
	void drawLevelScreen(std::string p1,std::string p2,std::string p3);
	void drawturn(int x, int y, std::string t);
	void drawGameOver(int winner);

	Game() {}
public:
		void draw();
		void update();
		void init();
		void processEvents();
		void addEvent(Event* evt);
		~Game();
		static Game* getInstance();
		
};