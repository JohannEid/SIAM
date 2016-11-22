#include "Header.h"
#include "Board.h"
#include "Player.h"
#include "Player sub_methods.h"

int main() {

    std::unique_ptr<Board> board(new Board());
    std::unique_ptr<Player> p_lhs(new Player(Player_side::RHS));
    std::unique_ptr<Player> p_rhs(new Player(Player_side::LHS));

    choose_action(p_lhs,board);
    board->display();
    choose_action(p_rhs,board);
    board->display();
    choose_action(p_lhs,board);
    board->display();
    choose_action(p_rhs,board);
    board->display();
    choose_action(p_lhs,board);
    board->display();
    choose_action(p_rhs,board);
    board->display();
    choose_action(p_lhs,board);
    board->display();
    choose_action(p_rhs,board);
    board->display();








    return 0;
}