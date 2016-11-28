//
// Created by johann on 12/11/16.
//

#ifndef SIAM02_OBJECT_H
#define SIAM02_OBJECT_H

#include "Header.h"


enum class Player_side {
    RHS = 1, LHS = 2, NONE = 3
};

enum class Direction {
    TOP, DOWN, RIGHT, LEFT
};

const float side_resistance_of_mountain = 0.9;
const float front_resistance_of_mountain = 0.9;
const float front_strenght_of_mountain = 0.0;

const float side_resistance_of_animal = 0;
const float front_resistance_of_animal = 1;
const float front_strenght_of_animal = 1;


class Object {
protected:

    float front_strenght;
    float front_resistance;
    float side_resistance;
    //appearance
    char widget;
    //belongs to ...
    Player_side side;

    Object(
            float front_strenght, float front_resistance,
            float side_resistance, char widget, Player_side side = Player_side::NONE);

    Object() = delete;

    virtual  ~Object() {}

public:
    ///GETTER


    float getFront_strenght() const {
        return front_strenght;
    }

    float getFront_resistance() const {
        return front_resistance;
    }

    float getSide_resistance() const {
        return side_resistance;
    }

    char getWidget() const {
        return widget;
    }


    Player_side getSide() const {
        return side;
    }

    virtual char getDirection() { return 'O'; }

    virtual int getNumber() const { return 0; }




///SETTER


    virtual void setEdirection(Direction edirection) {}



    ///DISPLAY

    virtual void display();

};

class Mountain : public Object {
public :
    Mountain();

};

class Empty : public Object {

public :
    Empty();


};

class Animal : public Object {
private:

    Direction edirection;
    int number;

    const char toChar(Direction direction);


public:
    Animal() = delete;

    Animal(char widget,
           Direction edirection, int number, Player_side side);

    void display() override;

    ///GETTER
    Direction getEdirection() const {
        return edirection;
    }

    int getNumber() const override {
        return number;
    }

    char getDirection();




    ///SETTER

    void setEdirection(Direction edirection) {
        Animal::edirection = edirection;
    }
};


#endif //SIAM02_OBJECT_H
