#pragma once
class Board;

class Player {
private:
	int cellWidth;
	int cellHeight;
public:
	Player(BoardValue color);
	~Player();

	bool MouseHandler(Board& board, HWND hWnd, RECT clientRect, int x, int y);

	bool HasValidMove(const Board& board) const;

	bool ValidCell(const Board& board, int x, int y) const;
	void FlipPieces(Board& board, int x, int y);

	BoardValue playerColor;
};