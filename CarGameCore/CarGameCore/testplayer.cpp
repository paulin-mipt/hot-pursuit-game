#include <iostream>
#include <stdlib.h>
#include "CPlayer.h"

using namespace std;

int main(int argc, char * argv[]){
    
    Coordinates initial_coords = Coordinates(0, 0);
    
    Player * p = new Player(initial_coords, true);

    char c;
    Coordinates coords;

    cout << "Make your move (0 to exit): ";
    cin >> c;

    while(c != '0'){
        try {
            p->move(atoi(&c));
            coords = p->getPosition();
            cout << "X: " << coords.x << "\tY: " << coords.y << endl;
        } catch(exception & e){
            cout << e.what() << endl;
        }
        cout << "Your move: ";
        cin >> c;
    }

};
