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
public:

    int compteur = 0;
    std::string name = "my_name";
    Player_side side;

public:

    ///CONSTRUCTOR
    Player(Player_side side, std::string name = "default");
    ~Player() {}

    ///INITIALISER
     void initName(std::string name);

    ///METHODS ENTER MOVE EXIT
    //void choose_action(std::unique_ptr<Board> &)

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
    //virtual void choose_action(std::unique_ptr<Board>& board );





};


class Player_ai : public Player
{
private:
    void chooseEnterPawn(std::unique_ptr<Board> &board,std::unique_ptr<Player>& );
    void chooseMovePawn (std::unique_ptr<Board> &board,std::unique_ptr<Player>& );
    void choooseExitPawn (std::unique_ptr<Board> &board,std::unique_ptr<Player>& );
    std::vector <std::pair<int,int>>  mappingOfMountain (std::unique_ptr<Board> &board);





public:

    Player_ai(Player_side side):Player(side,"Ai")
    {}
    void chooseAction(std::unique_ptr<Board> &board,std::unique_ptr<Player>& );





};


#endif //SIAM02_PLAYER_H
