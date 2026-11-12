#include "board_layout.hpp"
#include "raylib_view.hpp"


namespace FrogToad {
	void RaylibView::draw(const BoardModel& model) {
		ClearBackground(RAYWHITE);

        //title
        DrawText("Toads & Frogs", 20, 20, 30, BLACK);

        //instructions
        DrawText("1..7 = move index; R = restart",
            20, 50, 20, DARKGRAY);

        //cell under mouse
        std::optional<int> hoveredCell = BoardLayout::cellAt(GetMousePosition());

        //board cells
        for (int index{ 0 }; index < BoardModel::BoardSize; index++) {

            //cell rectangle from BoardLayout
            Rectangle cell = BoardLayout::cellRect(index);   

            //cell contents
            BoardModel::Cell contents = model.cellAt(index);

            //piece color
            Color pieceColor = WHITE;

            switch (contents) {

            case BoardModel::Cell::Frog:
                pieceColor = BLUE;
                break;

            case BoardModel::Cell::Toad:
                pieceColor = RED;
                break;

            case BoardModel::Cell::Empty:
                pieceColor = WHITE;
                break;
            }

            // draw piece if cell isn't empty
            if (contents != BoardModel::Cell::Empty) {

                DrawCircle(cell.x + cell.width / 2, cell.y + cell.height / 2, 25, pieceColor);

                DrawCircleLines( cell.x + cell.width / 2, cell.y + cell.height / 2, 25, BLACK);
            }

            // highlight cell under mouse
            if (hoveredCell.has_value()) {

                Rectangle hoveredRect = BoardLayout::cellRect(*hoveredCell);

                DrawRectangleRec(hoveredRect, Fade(GOLD, 0.1f));           
            }

            //cell border
            DrawRectangleLinesEx(cell, 2, BLACK);

            //cell number
            DrawText(TextFormat("%i", index + 1), cell.x + 35, cell.y + cell.height + 5, 15, GRAY);
        }

        
        

       
        if (model.isSolved()) {
            DrawText("Solved! Press R to restart.", 40, 190, 20, GREEN);
        }
        else if (model.state() == BoardModel::GameState::Lost) {
            DrawText("No more possible moves.", 40, 190, 20, RED);
            
        }
        else {
            DrawText("Choose a piece to move.", 40, 190, 20, GRAY);
            
        }
	}

	int RaylibView::windowW() { return 600; }
	int RaylibView::windowH() { return 300; }
}
