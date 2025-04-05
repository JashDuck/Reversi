#pragma once
class AIPlayer : public Player {
public:
	std::vector<std::pair<int, int>> GetValidMoves(const Board& board);

	int CountFlipsInDirection(const Board& board, int x, int y, int dx, int dy);
	int SimulateMoveAndCountFlips(const Board& board, int x, int y);

	int EvaluateMove(Board& board, int x, int y);
	std::pair<int, int> ChooseBestMove(const Board& board);

	void move(Board& board, HWND hWnd);
};

