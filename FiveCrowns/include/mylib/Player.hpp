//
//  Player.hpp
//  FiveCrowns
//
//  Created by Max Sealey on 10/14/22.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include <stdlib.h>
#include "Enums.h"

class Player
{
private:
    std::string name;
    int scores[11];
    int standing;
    Color color; // for use in eventual GUI
public:
    // Setter Declarations
    void setName(std::string);
    void setScore(int);
    void setStanding(int);
    void setColor(Color);
    
    // Getter Declarations
    std::string getName() const;
    int* getScores() const;
    int getStanding() const;
    Color getColor() const;
    
    Player();
    
    Player(std::string initName, int initScores[], int initStanding, Color initColor);
    
    ~Player();
};

#endif /* Player_hpp */
