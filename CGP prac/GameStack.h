#pragma once
#include <stack>
#include <memory>
#include "GameScene.h"
using namespace std;

class GameStack
{
private:
	stack <unique_ptr<GameScene>> scenes;

public:
	static GameStack& getInstance() {
		static GameStack instance;
		return instance;
	}
	void pushscene(unique_ptr<GameScene> scene);
	void popscene();
	unique_ptr<GameScene>& topscene();

};

