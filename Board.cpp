#include "Board.h"
#include "Player.h"

int Board::victory_condition = 0;

Board::Board() {

    Board::board.resize(board_width, std::vector<std::shared_ptr<Object>>
            (board_height, std::make_shared<Empty>()));

    for (unsigned int i(0); i < number_of_mountain; i++) {
        Board::board[mountain_x][side_distance + i] =
                std::make_shared<Mountain>();
    }

}


void Board::enter_a_pawn(std::unique_ptr<Player> &player) {
    //getting set to call const
    std::pair<int, int> my_coordinates{getCoordinates(player)};
    char widget = (player->getSide() == Player_side::RHS) ? 'E' : 'R';
    //by default
    Direction direction = Direction::TOP;
    //once object created set true direction
    player->setCompteur(player->getCompteur() + 1);
    setBoard(my_coordinates.first, my_coordinates.second,
             std::make_shared<Animal>(widget, direction, player->getCompteur(), player->getSide()));

    choice_to_rotate(my_coordinates.first + 1, my_coordinates.second + 1);
}

std::map<int, int> Board::canExit(std::unique_ptr<Player> &player) {
    std::map<int, int> exit_coordinates;
    for (unsigned int i{0}; i < board_width; i++) {
        for (unsigned int j{0}; j < board_height; j++) {
            if ((((i == 0) && ((0 <= j) && (j < board_height - 1)) ||
                  (((i == board_width - 1) &&
                    ((0 <= j) && (j < board_height - 1)))) || ((((0 <= i) && (i <= board_width - 1)) && (j == 0))) ||
                  (((0 <= i) && (i <= board_width - 1)) && (j == board_height - 1))) &&
                 (getObject(i, j)->getSide() == player->getSide()))) {
                exit_coordinates.insert(std::make_pair(i + 1, j + 1));

            }


        }

    }
    return exit_coordinates;
}

void Board::exit(std::unique_ptr<Player> &player) {
    int position_x{0};
    int position_y{0};
    std::map<int, int> coordinates_exit{canExit(player)};
    display();
    auto it = coordinates_exit.begin();
    while (it != coordinates_exit.end()) {
        std::cout << "x: " << it->first << " :: " << "y: " << it->second << std::endl;
        it++;
    }

    while (true) {

        try {
            std::cin >> position_x;
            std::cin >> position_y;
            if ((coordinates_exit.find(position_x) != coordinates_exit.end()) &&
                (coordinates_exit[position_x] == position_y)) {
                board[position_x - 1][position_y - 1] = std::make_shared<Empty>();
                player->setCompteur(player->getCompteur() - 1);
                break;

            } else
                throw std::domain_error("Invalid use of coodinates selection for pawn exit");

/*
             (coordinates_exit.find(position_x) != coordinates_exit.end())
             ?(board[position_x][position_y] = std::make_shared<Empty>()): throw std::domain_error(
                            "Invalid use of coodinates selection for pawn exit" );
*/

        }
        catch (std::exception const &e) {

            std::cerr << "Erreur" << e.what() << std::endl;
        }
    }
}

void Board::move(std::unique_ptr<Player> &player) {

    std::pair<int, int> my_pawn_coordinates = chooseAPawn(player);
    int position_x{my_pawn_coordinates.first};
    int position_y{my_pawn_coordinates.second};
    choice_to_rotate(position_x, position_y);


    std::pair<int, int> my_direction = directionToPair(board[position_x - 1][position_y - 1]->getDirection());
    //if it is out of range ... make empty no increase compteur
    if ((position_x - 1 + my_direction.first < 0)
        || (position_x - 1 + my_direction.first > board_width - 1)
        || (position_y - 1 + my_direction.second > board_height - 1)
        || (position_y - 1 + my_direction.second < 0)) {
        board[position_x - 1][position_y - 1] = std::make_shared<Empty>();
    }
// if nothing in front
    else if (board[position_x - 1 + my_direction.first][position_y - 1 + my_direction.second]->getFront_resistance() ==
             0) {
        std::swap(board[position_x - 1 + my_direction.first][position_y - 1 + my_direction.second],
                  board[position_x - 1][position_y - 1]);
    }
        //part where you have a pawn in front of you
    else {
        movePawnInFront(player, position_x, position_y, my_direction);

    }


}


void Board::rotate(std::unique_ptr<Player> &player) {


    display();
    displayPawnCoordinates(player);
    std::pair<int, int> my_pawn_coordinates = chooseAPawn(player);
    int position_x{my_pawn_coordinates.first};
    int position_y{my_pawn_coordinates.second};

    choice_to_rotate(position_x, position_y);


}

std::pair<int, int> Board::directionToPair(char edirection) {
    {
        switch (edirection) {
            case 'd':
                return std::make_pair(1, 0);
            case 't':
                return std::make_pair(-1, 0);
            case 'r':
                return std::make_pair(0, 1);
            case 'l':
                return std::make_pair(0, -1);
            default:
                break;


        }
    }
}

int Board::directionToInt(char edirection) {
    switch (edirection) {
        case 'd':
            return 3;
        case 't':
            return 1;
        case 'r':
            return 2;
        case 'l':
            return 0;
        default:
            break;

    }
}


void Board::displayPawnCoordinates(std::unique_ptr<Player> &player) {
    for (unsigned int i{0}; i < board_width; i++) {
        for (unsigned int j{0}; j < board_height; j++) {
            (board[i][j]->getSide() == player->getSide()) ? std::cout << "x :" << i + 1 << "y :" << j + 1 << std::endl :
            std::cout << "";

        }
    }
}

std::pair<int, int> Board::getCoordinates(std::unique_ptr<Player> &player) {
    std::string my_position_x{" "};
    std::string my_position_y{" "};

    while (true) {

        display();
        std::cout << "Please enter the coordinates you want to select" << std::endl;
        std::cout << "Position in x: " << std::endl;
        std::cout << "Position in y: " << std::endl;
        try {
            std::cin >> my_position_x;
            std::cin >> my_position_y;

            int position_x = std::stoi(my_position_x);
            int position_y = std::stoi(my_position_y);


            if (((position_x == min_board_width) && ((min_board_height <= position_y) && (position_y <= board_height)))
                ||
                ((position_y == min_board_height) && ((min_board_width <= position_x) && (position_x <= board_width)))
                || ((position_x == board_width) && ((min_board_height <= position_y) && (position_y <= board_height)))
                || ((position_y == board_height) && ((min_board_width <= position_x) && (position_x <= board_width)))) {
                if (board[position_x - 1][position_y - 1]->getFront_resistance() == 0)
                    return std::make_pair(position_x - 1, position_y - 1);
                else {
                    // if there already is a pawn you push him
                    char direction{' '};

                    if ((position_x - 1 == 0) && (0 <= position_y - 1) && (position_y - 1
                                                                           < board_height - 1)) {
                        direction = 'd';
                    } else if ((position_x - 1 == board_width - 1) &&
                               (0 <= position_y - 1) && (position_y - 1 < board_height - 1)) {
                        direction = 't';
                    } else if ((0 <= position_x - 1) && (position_x - 1 <= board_width - 1) &&
                               (position_y - 1 == 0)) {
                        direction = 'r';
                    } else if ((0 <= position_x - 1) && (position_x - 1 <= board_width - 1) &&
                               (position_y - 1 == board_height - 1)) {
                        direction = 'l';

                    }
                    movePawnInFront(player, position_x, position_y, directionToPair(direction));
                    return std::make_pair(position_x - 1, position_y - 1);
                }
            } else
                throw std::domain_error("Invalid use of coodinates selection for pawn entering ");


        }
        catch (std::exception const &e) {
            std::cerr << "Erreur" << e.what() << std::endl;

        }


    }
}

void Board::display() {

    clear();
    std::cout << "******************** MY BOARD  *************************" << std::endl;

    for (unsigned int i(0); i < board_width; i++) {
        for (unsigned int j(0); j < board_height; j++) {


            board[i][j]->display();
            std::cout << " ";

        }
        std::cout << std::endl;
    }
    std::cout << "********************//////*******************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}

std::pair<int, int> Board::chooseAPawn(std::unique_ptr<Player> &player) {
    std::string my_position_x{" "};
    std::string my_position_y{" "};
    int position_x{0};
    int position_y{0};
    display();
    displayPawnCoordinates(player);

    while (true) {
        try {
            std::cin >> my_position_x;
            std::cin >> my_position_y;

            position_x = std::stoi(my_position_x);
            position_y = std::stoi(my_position_y);

            if (board[position_x - 1][position_y - 1]->getSide() == player->getSide())
                break;
            else
                throw std::domain_error("Invalid use of coodinates selection for pawn exit");
        }
        catch (std::exception const &e) {

            std::cerr << "Erreur" << e.what() << std::endl;
        }

    }
    return std::make_pair(position_x, position_y);
}

void Board::choice_to_rotate(int position_x, int position_y) {
    char direction_entry{' '};

    try {
        // while (true){
        std::cout << "Please enter your new direction " << std::endl;
        std::cin >> direction_entry;
        clear();
        switch (direction_entry) {
            case 't' :
                if (board[position_x - 1][position_y - 1]->getDirection() != 't') {
                    board[position_x - 1][position_y - 1]->setEdirection(Direction::TOP);
                    break;
                } else {
                    throw std::domain_error("Invalid entry ");
                }
            case 'd':
                if (board[position_x - 1][position_y - 1]->getDirection() != 'd') {
                    board[position_x - 1][position_y - 1]->setEdirection(Direction::DOWN);
                    break;
                } else {
                    throw std::domain_error("Invalid entry ");
                }

            case 'r':
                if (board[position_x - 1][position_y - 1]->getDirection() != 'r') {
                    board[position_x - 1][position_y - 1]->setEdirection(Direction::RIGHT);
                    break;
                } else {
                    throw std::domain_error("Invalid entry ");
                }

            case 'l' :
                if (board[position_x - 1][position_y - 1]->getDirection() != 'l') {
                    board[position_x - 1][position_y - 1]->setEdirection(Direction::LEFT);
                    break;
                } else {
                    throw std::domain_error("Invalid entry ");
                }

            default:
                throw std::domain_error("Invalid entry ");
        }

        // }
    }
    catch (std::exception const &e) {
        std::cerr << "Erreur" << e.what() << std::endl;

    }


}

void Board::movePawnInFront(std::unique_ptr<Player> &my_player,
                            int position_x, int position_y, std::pair<int, int> my_direction) {


    int x{position_x - 1};
    int y{position_y - 1};
    float total_strenght{board[position_x - 1][position_y - 1]->getFront_resistance()};

    while ((x <= board_width - 1) && (x >= 0) && (y <= board_height - 1) && (y >= 0)) {


        x += my_direction.first;
        y += my_direction.second;
        if (board[x][y]->getSide() != board[position_x - 1][position_y - 1]->getSide()) {
            break;

        }
        total_strenght += board[x][y]->getFront_strenght();

    }
    std::cout << total_strenght << std::endl;

    float total_resistance{0};

    while ((x <= board_width - 1) && (x >= 0) && (y <= board_height - 1) && (y >= 0) &&
           (board[x][y]->getFront_resistance() != 0)) {

        total_resistance += ((directionToInt(board[position_x - 1][position_y - 1]->getDirection()) +
                              directionToInt(board[x][y]->getDirection())) % 2 == 0)
                            ? board[x][y]->getFront_resistance()
                            : board[x][y]->getSide_resistance();


        x += my_direction.first;
        y += my_direction.second;

    }
    std::cout << total_resistance << std::endl;


    if (total_strenght > total_resistance) {
        x = position_x - 1;
        y = position_y - 1;

        while (true) {
            if ((x + my_direction.first >= 0) &&
                (y + my_direction.second >= 0)
                && (x + my_direction.first <= board_width - 1)
                && (y + my_direction.second <= board_height - 1)) {

                if ((board[x + my_direction.first][y + my_direction.second]
                             ->getFront_resistance() != 0)) {
                    x += my_direction.first;
                    y += my_direction.second;

                } else
                    break;

            } else
                break;


        }
        while (true) {
            //if back to move spot
            if ((x == position_x - 1) && (y == position_y - 1)) {
                //if out of reach... exit board
                if ((x + my_direction.first < 0) || (y + my_direction.second < 0)
                    || (x + my_direction.first > board_width - 1)
                    || (y + my_direction.second > board_height - 1)) {
                    board[x][y] = std::make_shared<Empty>();
                    //when we reach this pawn we stop looping
                    break;

                }
                    //else shift
                else {
                    board[x + my_direction.first][y + my_direction.second] = board[x][y];
                    board[x][y] = std::make_shared<Empty>();
                    //when we reach this pawn we stop looping
                    break;
                }

            }
                //if out of reach ... exit board
            else if ((x + my_direction.first < 0) || (y + my_direction.second < 0)
                     || (x + my_direction.first > board_width - 1)
                     || (y + my_direction.second > board_height - 1)) {
                //if the one exiting board is a mountain
                if (board[x][y]->getFront_resistance() == front_resistance_of_mountain) {
                    //how many lhs and rhs next to spot of exit
                    int compteur_of_player_lhs{0};
                    int compteur_of_player_rhs{0};

//allows to detect the spots next to exit moutain  and mark to whom is belongs increments compteur each time
                    if (x - 1 >= 0) {
                        if (board[x - 1][y]->getSide() == Player_side::LHS)
                            compteur_of_player_lhs++;
                        else if (board[x - 1][y]->getSide() == Player_side::RHS)
                            compteur_of_player_rhs++;
                    }
                    if (x + 1 <= board_width - 1) {

                        if (board[x + 1][y]->getSide() == Player_side::LHS)
                            compteur_of_player_lhs++;
                        else if (board[x + 1][y]->getSide() == Player_side::RHS)
                            compteur_of_player_rhs++;
                    }
                    if (y - 1 >= 0) {

                        if (board[x][y - 1]->getSide() == Player_side::LHS)
                            compteur_of_player_lhs++;
                        else if (board[x][y - 1]->getSide() == Player_side::RHS)
                            compteur_of_player_rhs++;
                    }
                    if (y + 1 <= board_height - 1) {

                        if (board[x][y + 1]->getSide() == Player_side::LHS) {
                            compteur_of_player_lhs++;
                        } else if (board[x][y + 1]->getSide() == Player_side::RHS) {
                            compteur_of_player_rhs++;
                        }
                    }

                    if (compteur_of_player_lhs > compteur_of_player_rhs) {
                        setVictory_condition(1);

                    } else if (compteur_of_player_lhs < compteur_of_player_rhs) {
                        setVictory_condition(2);
                    } else {
                        std::cout << "nobody won equal number of pawn next to the exit of mountain !! "
                                  << std::endl;
                    }


                }

                board[x][y] = std::make_shared<Empty>();

            } else {
                board[x + my_direction.first][y + my_direction.second] = board[x][y];
            }
            //goes towards pawn that started the move
            x -= my_direction.first;
            y -= my_direction.second;

        }


    } else {
        std::cout << "Can't push this line your total strenght is : " << total_strenght
                  << "The total resistance is "
                  << total_resistance << std::endl;

    }


}












