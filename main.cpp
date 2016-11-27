#include "Header.h"
#include "Board.h"
#include "Player.h"
#include "Player sub_methods.h"

int main() {

    std::unique_ptr<Board> board(new Board());
    std::unique_ptr<Player> p_lhs(new Player(Player_side::RHS));
    std::unique_ptr<Player> p_rhs(new Player(Player_side::LHS));

    while (true) {

        choose_action(p_lhs, board);
        if (Board::getVictory_condition() == 2) {
            std::cout << "PLayer : " << p_rhs->getName() << " wins!" << std::endl;
            break;
        }

        board->display();
        choose_action(p_rhs, board);
        if (Board::getVictory_condition() == 1) {
            std::cout << "PLayer : " << p_lhs->getName() << " wins!" << std::endl;
            break;
        }


    }


    return 0;
}