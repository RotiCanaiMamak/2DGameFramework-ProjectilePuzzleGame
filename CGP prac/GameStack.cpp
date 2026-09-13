#include "GameStack.h"
#include <stack>


void GameStack::pushscene(unique_ptr<GameScene> scene) {
	scenes.push(move(scene));
}

void GameStack::popscene() {
	scenes.pop();
}

unique_ptr<GameScene>& GameStack::topscene() {
	return scenes.top();
}