class Score {
public:
	Score();
	void addScore();
	int getScore();
	int getMultiplier();
	void resetMultiplier();
private:
	int score;
	int multiplier;
	int scoreCount;
};