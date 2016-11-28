//
// Created by johann on 28/11/16.
//
#include "utilities .h"

void saveFile(const std::unique_ptr<Board> &my_board,
              const std::unique_ptr<Player> &player_lhs, const std::unique_ptr<Player> &player_rhs) {
    std::string my_string{""};

    std::ofstream my_file;
    my_file.open("my_save_game.txt");

    for (unsigned int i(0); i < board_width; i++) {
        for (unsigned int j(0); j < board_height; j++) {


            if (my_board->getObject(i, j)->getFront_resistance() == 0)

                my_file << "O";
            else if (my_board->getObject(i, j)->getFront_resistance() == 0.9)
                my_file << "M";
            else if(my_board->getObject(i, j)->getFront_resistance() == 1 )
            {
                    my_string+=my_board->getObject(i,j)->getWidget();
                my_string+=my_board->getObject(i,j)->getDirection();
                my_file+=my_board->getObject(i,j)->
                my_file << my_string;
            }



        }
        std::cout << std::endl;
    }
    std::cout<<player_lhs->getCompteur()<<std::endl;
    std::cout<<player_lhs->getName()<<std::endl;
    std::cout<<player_rhs->getCompteur();std::endl;
    std::cout<<player_rhs->getName()<<std::endl;




}