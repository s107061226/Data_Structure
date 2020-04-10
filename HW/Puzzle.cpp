#include <iostream>
using namespace std;

class Piece {
    private:
        // looping index
        int i;
    public:
        // variables of puzzle's information
        int width;
        int height;
        char *shape = new char[width * height];
        // functions for getting puzzle's information
        void Get_Info() 
        {
            cout << "the width and height of piece " << i + 1 << ": ";
            cin >> width >> height;
            cout << "the shape of piece " << i + 1 << ": ";
            for (i = 0; i < width * height; i++) {
                cin >> shape[i];
            }
        }
};

class Map {
    private:
        // looping index
        int i;
    public:
        // variables
        int width;
        int height;
        char *shape = new char[width * height];
        // function for getting the map
        void Get_Info() 
        {
            cout << "the width and height of map " << i + 1 << ": ";
            cin >> width >> height;
            cout << "the shape of map " << i + 1 << ": ";
            for (i = 0; i < width * height; i++) {
                cin >> shape[i];
            }
        }
};

int main(void)
{
    int num_piece, num_map;     // the number of puzzles and maps
    Piece *piece;               // piece objects
    Map *map;                   // map objects
    int i;                      // looping index

    // get the number of pieces and information of each piece
    cout << "how many picecs? ";
    cin >> num_piece;
    piece = new Piece[num_piece];
    for (i = 0; i < num_piece; i++) {
        piece[i].Get_Info();
    }
    // get the number of maps and information of each piece
    cout << "how many maps? ";
    cin >> num_map;
    map = new Map[num_map];
    for (i = 0; i < num_map; i++) {
        map[i].Get_Info();
    }


    return 0;
}