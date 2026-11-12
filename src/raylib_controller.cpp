#include "raylib_controller.hpp"
#include "raylib.h"
#include "board_layout.hpp"

namespace FrogToad {
	void RaylibController::handleInput(BoardModel& model) {

		
        int key = GetKeyPressed();

        if (key >= KEY_ONE && key <= KEY_SEVEN) {
            int move = key - KEY_ONE;
            model.tryMove(move);
        }

        else if (key == KEY_R) {
            model.reset();
        }

        //mouse input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            std::optional<int> cell = BoardLayout::cellAt(GetMousePosition());

            if (cell.has_value()) {

                BoardModel::Cell selectedCell = model.cellAt(*cell);

                if (selectedCell == BoardModel::Cell::Frog ||
                    selectedCell == BoardModel::Cell::Toad) {

                    model.tryMove(*cell);
                }
            }
        }
	}
}
