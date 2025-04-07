#pragma once
class AIPlayer : public Player {
public:
	std::vector<std::pair<int, int>> GetValidMoves(const Board& board);

	int CountFlipsInDirection(const Board& board, int x, int y, int dx, int dy);
	int SimulateMove(const Board& board, int x, int y);

	std::pair<int, int> ChooseMostPieces(const Board& board, std::vector<std::pair<int, int>> validMoves);

	int Minimax(Board board, int depth, bool maximizingPlayer);
	int EvaluateBoard(const Board& board);
	std::pair<int, int> ChooseMinimax(const Board& board, std::vector<std::pair<int, int>> validMoves);

	void move(Board& board, HWND hWnd, Difficulty difficulty);
};

