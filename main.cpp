#include "Header.h"
#include "Board.h"
#include "Player.h"
#include "Player sub_methods.h"
#include "utilities .h"

int main() {

    std::unique_ptr<Board> board(new Board());
    std::unique_ptr<Player> p_lhs(new Player(Player_side::LHS));
    std::unique_ptr<Player> p_rhs(new Player(Player_side::RHS));

    while (true) {
//call of choose function for left player
        choose_action(p_lhs, board);
        //if left player concedes or right players exits mountain so right wins
        if (Board::getVictory_condition() == 1) {
            std::cout << "PLayer : " << p_rhs->getName() << " wins!" << std::endl;
            break;
        }

        //call of choose function for right player

        //if right player concedes or left player exits mountain so right wins
/*
        choose_action(p_rhs, board);
        if (Board::getVictory_condition() == 2) {
            std::cout << "PLayer : " << p_lhs->getName() << " wins!" << std::endl;
            break;
        }


    }
    */

        saveFile(board, p_lhs, p_rhs);

        return 0;
    }
}