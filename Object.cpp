//
// Created by johann on 12/11/16.
//

#include "Object.h"

Object::Object(float front_strenght, float front_resistance,
               float side_resistance, char widget,Player_side side ):
        front_strenght(front_strenght),
        front_resistance(front_resistance),
        side_resistance(side_resistance), widget(widget),side(side) {}


Mountain::Mountain() : Object(
        front_strenght_of_mountain,
        front_resistance_of_mountain,
        side_resistance_of_mountain, 'M') {}


Animal::Animal(
        char widget, Direction edirection, int number,Player_side side) : Object(
        front_strenght_of_animal,
        front_resistance_of_animal,
        side_resistance_of_animal, widget,side),
                                                         edirection(edirection),
                                                         number(number) {}

Empty::Empty() : Object(
        0, 0, 0, 'O') {}


void Object::display() {

    std::cout << getWidget();

}

void Animal::display() {
    Object::display();
    std::cout << getNumber() << toChar(getEdirection());


}

char Animal::getDirection() {
    return  toChar(getEdirection());

}

const char Animal ::  toChar(Direction direction) {
    switch (direction) {
        case Direction::TOP:
            return 't';
            break;
        case Direction::DOWN:
            return 'd';
            break;
        case Direction::RIGHT:
            return 'r';
            break;
        case Direction::LEFT:
            return 'l';
            break;
        default:
            std::cout << "Error converting to char " << std::endl;
            break;

    }
}

