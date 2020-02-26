#include "Player.h"

Player::Player() {
	playerScore = 0;
}

void Player::setPlayerScore(int score) {
	playerScore = score;
}

void Player::addPlayerScore(int value) {
	playerScore += value;
}

int Player::getPlayerScore() {
	return playerScore;
}
