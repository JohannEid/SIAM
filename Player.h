//
// Created by johann on 12/11/16.
//

#ifndef SIAM02_PLAYER_H
#define SIAM02_PLAYER_H

#include "Header.h"
#include "Board.h"
#include "utilities .h"

const int max_pawn_number = 5;

class Player {
private :

    int compteur = 0;
    std::string name;
    Player_side side;

public:

    ///CONSTRUCTOR
    Player(Player_side side);

    ///INITIALISER
    void initName();

    ///METHODS ENTER MOVE EXIT
    //void choose_action(std::unique_ptr<Board> &);

    ///GETTER

    int getCompteur() const {
        return compteur;
    }

    const std::string &getName() const {
        return name;
    }

    Player_side getSide() const {
        return side;
    }

    ///SETTER
    void setCompteur(int compteur) {
        Player::compteur = compteur;
    }




};


class Player_ai : public Player
{



};


#endif //SIAM02_PLAYER_H
