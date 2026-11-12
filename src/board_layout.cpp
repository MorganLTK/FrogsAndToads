#include "board_layout.hpp"
#include "board_model.hpp"
#include <cassert> // assert() in cellRect()

namespace FrogToad {
    Rectangle BoardLayout::board() {
        float width = BoardModel::BoardSize * CellSize;

        return {Left, Top, width, CellSize};
    }

    Rectangle BoardLayout::cellRect(int index) {
        // Assert that the index is valid:
        assert(index >= 0 && index < BoardModel::BoardSize);

        float x = Left + (index * CellSize);

        return {x, Top, CellSize, CellSize};
    }

    std::optional<int> BoardLayout::cellAt(Vector2 point) {

        if (!CheckCollisionPointRec(point, board())) {
            return std::nullopt;
        }

        // calculate which cell the point is inside
        for (int index = 0; index < BoardModel::BoardSize; index++) {

            if (CheckCollisionPointRec(point, cellRect(index))) {
                return index;
            }
        }
        return std::nullopt;
    }
}