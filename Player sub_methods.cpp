//
// Created by johann on 13/11/16.
//

#include "Player sub_methods.h"


void choose_action(std::unique_ptr<Player> &my_player,
                   std::unique_ptr<Board> &board) {
    unsigned int entry{0};
    while (true) {
        try {
            clear();
            std::cout << "******************** MY BOARD  *************************"<<std::endl;
            board->display();
            std::cout <<"********************//////*******************************"<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::cout << "Please " << my_player->getName() << " enter an action" << std::endl;
            std::cout << "1.Enter a pawn" << std::endl;
            std::cout << "2.Exit a pawn" << std::endl;
            std::cout << "3.Move a pawn" << std::endl;
            std::cout << "4.Rotate a pawn " << std::endl;
            std::cout << "5.Forfeit the game " << std::endl;



            std::cin >> entry;
            clear();


            if ((entry == 1) && (my_player->getCompteur() < max_pawn_number)) {
                board->enter_a_pawn(my_player);
                break;
            } else if ((entry == 1) && (my_player->getCompteur() < max_pawn_number > max_pawn_number)) {
                throw std::domain_error("Can't choose to perform this action");

            }
            else if ((entry == 2) && (!board->canExit(my_player).empty())) {
                board->exit(my_player);
                break;
            } else if ((entry == 2) && (board->canExit(my_player).empty())) {
                throw std::domain_error("Can't choose to perform exit action (no pawns in exit position)");
            }
            else if ((entry == 3) && (my_player->getCompteur() > 0)) {
                board->move(my_player);
                break;
            } else if ((entry == 3) && (!my_player->getCompteur() > 0)) {
                throw std::domain_error("Can't choose to perform move action (no pawns on board)");
            }
           else  if ((entry == 4) && (my_player->getCompteur() > 0)) {
                board->rotate(my_player);
                break;
            } else if ((entry == 4) && (!my_player->getCompteur() > 0)) {
                throw std::domain_error("Can't choose to perform rotate action (no pawns on board)");
            }
           else  if ((entry == 5)) {
                (my_player->getSide()==Player_side ::LHS)? Board :: setVictory_condition(1):Board ::setVictory_condition(2);
                break;
            }
             else
                throw std::domain_error("Can't choose to perform rotate action ");


        }
        catch (std::exception const &e) {
            std::cerr << "Erreur" << e.what() << std::endl;


        }
    }

}
