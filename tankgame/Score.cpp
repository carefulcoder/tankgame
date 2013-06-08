#include "Score.h"

Score::Score() : score(0), multiplier(1), scoreCount(0) {}

/*
 * Add a score
 */
void Score::addScore() {
	scoreCount++;
	if (scoreCount % 10 == 0) {
		multiplier++;
	}
	score += multiplier;
}

int Score::getMultiplier() {
	return multiplier;
}

int Score::getScore() {
	return score;
}

void Score::resetMultiplier() {
	multiplier = 1;
	scoreCount = 0;
}

