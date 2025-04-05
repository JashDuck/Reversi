#include "pch.h"
#include "Player.h"
#include "Board.h"

Player::Player(BoardValue color) : playerColor(color) {}
Player::~Player() {}

bool Player::MouseHandler(Board& board, HWND hWnd, RECT clientRect, int x, int y) {
	cellWidth = (clientRect.right - Board::borderX * 2) / Board::MATRIX_SIZE;
	cellHeight = (clientRect.bottom - Board::borderY * 2) / Board::MATRIX_SIZE;
	
	int indexX = x / cellWidth;
	int indexY = y / cellHeight;

	if (ValidCell(board, indexX, indexY)) {
		board.boardState[indexX][indexY] = playerColor;
        FlipPieces(board, indexX, indexY);
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
		return true;
	}

	return false;
}

bool Player::HasValidMove(const Board& board) const {
    for (int x = 0; x < Board::MATRIX_SIZE; x++) {
        for (int y = 0; y < Board::MATRIX_SIZE; y++) {
            if (ValidCell(board, x, y)) {
                return true;
            }
        }
    }
    return false;
}

bool Player::ValidCell(const Board& board, int x, int y) const {
    if (x < 0 || x >= Board::MATRIX_SIZE || y < 0 || y >= Board::MATRIX_SIZE) { return false; }

    if (board.boardState[x][y] != BoardValue::EMPTY) { return false; }

    int directions[8][2] = {
        { 1,  0}, {-1,  0}, { 0,  1}, { 0, -1},
        { 1,  1}, {-1, -1}, { 1, -1}, {-1,  1}
    };

    for (auto& dir : directions) {
        int dx = dir[0], dy = dir[1];
        int nx = x + dx, ny = y + dy;
        bool foundOpponent = false;

        while (nx >= 0 && nx < Board::MATRIX_SIZE && ny >= 0 && ny < Board::MATRIX_SIZE) {
            BoardValue currentValue = board.boardState[nx][ny];

            if (currentValue == BoardValue::EMPTY) { break; }

            if (currentValue == playerColor) {
                if (foundOpponent) { return true; }
                break;
            }

            foundOpponent = true;
            nx += dx;
            ny += dy;
        }
    }

    return false;
}

void Player::FlipPieces(Board& board, int x, int y) {
    int directions[8][2] = {
        { 1,  0}, {-1,  0}, { 0,  1}, { 0, -1},
        { 1,  1}, {-1, -1}, { 1, -1}, {-1,  1}
    };

    for (auto& dir : directions) {
        int dx = dir[0], dy = dir[1];
        int nx = x + dx, ny = y + dy;
        std::vector<std::pair<int, int>> piecesToFlip;

        while (nx >= 0 && nx < Board::MATRIX_SIZE && ny >= 0 && ny < Board::MATRIX_SIZE) {
            if (board.boardState[nx][ny] == BoardValue::EMPTY) {
                break;
            }
            if (board.boardState[nx][ny] == playerColor) {
                if (!piecesToFlip.empty()) {
                    for (auto& p : piecesToFlip) {
                        board.boardState[p.first][p.second] = playerColor;
                    }
                }
                break;
            }
            piecesToFlip.push_back({ nx, ny });
            nx += dx;
            ny += dy;
        }
    }
}