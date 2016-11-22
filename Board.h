//
// Created by johann on 13/11/16.
//

#ifndef SIAM02_BOARD_H
#define SIAM02_BOARD_H

#include "Object.h"

class Player;

const int min_board_width = 1;
const int min_board_height = 1;
const int board_width = 5;
const int board_height = 5;
const int mountain_x = 2;
const int number_of_mountain = 3;
const int side_distance = 1;

using pointer_to_object = std::shared_ptr<Object>;
using pointer_to_animal = std::shared_ptr<Animal>;



class Board {
private:
    std::vector<std::vector<pointer_to_object>> board;


    std::pair<int,int> directionToPair(char edirection);
    void displayPawnCoordinates(std::unique_ptr<Player>&);
    std::pair<int, int> getCoordinates();
    std::pair<int,int>  chooseAPawn(std::unique_ptr<Player>&);
    int  directionToInt (char edirction);


public:
    Board();

    ///METHODS
    void enter_a_pawn(std::unique_ptr<Player>& );
    ///for exit
    void exit (std::unique_ptr<Player>& player);

    std::map<int,int> canExit(std::unique_ptr<Player>& player);

    ///move
    void move(std::unique_ptr<Player>&);

    ///rotate

    void rotate(std::unique_ptr<Player>&);

    ///display
    void display();



    ///GETTER

    pointer_to_object& getObject(int position_x, int position_y) {
        return board[position_x][position_y];
    }

///SETTER
    void setBoard(const int i, const int j,const std::shared_ptr<Object>& my_object) {
        Board::board[i][j]=my_object;
    }

};


#endif //SIAM02_BOARD_H
