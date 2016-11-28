//
// Created by johann on 28/11/16.
//

#ifndef SIAM02_UTILITIES_H
#define SIAM02_UTILITIES_H

#include "Header.h"
#include "Object.h"
#include "Player.h"
#include "Board.h"

void saveFile(const std::unique_ptr<Board>&,
              const std::unique_ptr<Player>&,
              const std::unique_ptr<Player>& );



#endif //SIAM02_UTILITIES_H
