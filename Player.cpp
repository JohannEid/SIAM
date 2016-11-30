//
// Created by johann on 12/11/16.
//

#include "Player.h"
#include "Player sub_methods.h"


Player::Player(Player_side side) : compteur(0), side(side) { initName(); }


void Player::initName() {
    std::cout << "Please choose a player name" << std::endl;
    std::cin >> Player::name;
    clear();

}

/*
void Player::choose_action(std::unique_ptr<Board> &board) {
    std::string my_entry{" "};
    while (true) {
        try {
            board->display();

            std::cout << "Please " << getName() << " enter an action" << std::endl;
            std::cout << "**********************************************************" << std::endl;
            std::cout << "1.Enter a pawn" << std::endl;
            std::cout << "2.Exit a pawn" << std::endl;
            std::cout << "3.Move a pawn" << std::endl;
            std::cout << "4.Rotate a pawn " << std::endl;
            std::cout << "5.Forfeit the game " << std::endl;


            std::cin >> my_entry;
            clear();
            int entry = std::stoi(my_entry);
            std::unique_ptr<Player>my_player(this);


            if ((entry == 1) && (getCompteur() < max_pawn_number)) {
                board->enter_a_pawn(my_player);
                break;
            } else if ((entry == 1) && (getCompteur() < max_pawn_number > max_pawn_number)) {
                throw std::domain_error("Can't choose to perform this action");

            } else if ((entry == 2) && (!board->canExit(my_player).empty())) {
                board->exit(my_player);
                break;
            } else if ((entry == 2) && (board->canExit(my_player).empty())) {
                throw std::domain_error("Can't choose to perform exit action (no pawns in exit position)");
            } else if ((entry == 3) && (getCompteur() > 0)) {
                board->move(my_player);
                break;
            } else if ((entry == 3) && (!getCompteur() > 0)) {
                throw std::domain_error("Can't choose to perform move action (no pawns on board)");
            } else if ((entry == 4) && (getCompteur() > 0)) {
                board->rotate(my_player);
                break;
            } else if ((entry == 4) && (!getCompteur() > 0)) {
                throw std::domain_error("Can't choose to perform rotate action (no pawns on board)");
            } else if ((entry == 5)) {
                (getSide() == Player_side::LHS) ? Board::setVictory_condition(1) : Board::setVictory_condition(2);
                break;
            } else
                throw std::domain_error("Can't choose to perform rotate action ");


        }
        catch (std::exception const &e) {
            std::cerr << "Erreur" << e.what() << std::endl;


        }
    }

}

*/

void Player_ai::chooseAction(std::unique_ptr<Board> &board, std::unique_ptr<Player> &player) {
    if ((getCompteur() <= player->getCompteur()) && (getCompteur() < max_pawn_number)) {
        chooseEnterPawn(board, player);
    } else if (getCompteur() > 0) {
        chooseMovePawn(board, player);
    } else {

    }


}

void Player_ai::chooseEnterPawn(std::unique_ptr<Board> &board, std::unique_ptr<Player> &player) {


}

void Player_ai::chooseMovePawn(std::unique_ptr<Board> &board, std::unique_ptr<Player> &player) {

}

void Player_ai::choooseExitPawn(std::unique_ptr<Board> &board, std::unique_ptr<Player> &player) {

}
std::vector <std::pair<int,int>> Player_ai :: mappingOfMountain (std::unique_ptr<Board> &board)
{
    std::vector< std::pair<int,int>> map_of_mountain;
    for (unsigned int i{0}; i < board_width; ++i)
    {
        for (unsigned  int j {0}; j < board_height ; ++j) {
            if(board -> getObject(i,j)->getFront_resistance() == front_resistance_of_mountain)
            {
                map_of_mountain.push_back(std::make_pair(i,j));
            }

        }
    }
    return map_of_mountain;

};
