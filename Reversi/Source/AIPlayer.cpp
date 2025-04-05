#include "pch.h"
#include "Player.h"
#include "AIPlayer.h"
#include "Board.h"

std::vector<std::pair<int, int>> AIPlayer::GetValidMoves(const Board& board) {
    std::vector<std::pair<int, int>> moves;
    for (int x = 0; x < Board::MATRIX_SIZE; x++) {
        for (int y = 0; y < Board::MATRIX_SIZE; y++) {
            if (ValidCell(board, x, y)) {
                moves.push_back({ x, y });
            }
        }
    }
    return moves;
}

int AIPlayer::CountFlipsInDirection(const Board& board, int x, int y, int dx, int dy) {
    int flips = 0;
    int nx = x + dx;
    int ny = y + dy;
    bool foundOpponent = false;

    while (nx >= 0 && nx < Board::MATRIX_SIZE && ny >= 0 && ny < Board::MATRIX_SIZE) {
        BoardValue currentValue = board.boardState[nx][ny];

        if (currentValue == BoardValue::EMPTY) {
            return 0;
        }

        if (currentValue == playerColor) {
            return (foundOpponent ? flips : 0);
        }

        foundOpponent = true;
        flips++;
        nx += dx;
        ny += dy;
    }

    return 0;
}

int AIPlayer::SimulateMoveAndCountFlips(const Board& board, int x, int y) {
    if (board.boardState[x][y] != BoardValue::EMPTY) {
        return 0;
    }

    int totalFlips = 0;

    int directions[8][2] = {
        { 1,  0}, {-1,  0}, { 0,  1}, { 0, -1},
        { 1,  1}, {-1, -1}, { 1, -1}, {-1,  1}
    };

    for (int i = 0; i < 8; i++) {
        totalFlips += CountFlipsInDirection(board, x, y, directions[i][0], directions[i][1]);
    }

    return totalFlips;
}

int AIPlayer::EvaluateMove(Board& board, int x, int y) {
    Board boardCopy = board;
    int piecesFlipped = SimulateMoveAndCountFlips(boardCopy, x, y);
    return piecesFlipped;
}

std::pair<int, int> AIPlayer::ChooseBestMove(const Board& board) {
    std::pair<int, int> bestMove = { -1, -1 };
    int bestScore = -1;

    for (int x = 0; x < Board::MATRIX_SIZE; x++) {
        for (int y = 0; y < Board::MATRIX_SIZE; y++) {
            int score = SimulateMoveAndCountFlips(board, x, y);
            if (score > bestScore) {
                bestScore = score;
                bestMove = { x, y };
            }
        }
    }

    return bestMove;
}

void AIPlayer::move(Board& board, HWND hWnd) {
    auto move = ChooseBestMove(board);
    if (move.first != -1 && move.second != -1) {
        board.boardState[move.first][move.second] = playerColor;
        FlipPieces(board, move.first, move.second);

        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }
}