//
// Created by johann on 12/11/16.
//

#include "Player.h"
#include "Player sub_methods.h"


Player::Player(Player_side side) : compteur(0), side(side) { initName(); }

void Player::initName() {
    std::cout << "Please choose a player name"<< std::endl;
    std::cin >> Player::name;
    clear();

}

///METHODS ENTER MOVE EXIT




