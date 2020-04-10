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
            cout << "the width and height of the piece: ";
            cin >> width >> height;
            cout << "the shape of piece: ";
            for (i = 0; i < width * height; i++) {
                cin >> shape[i];
            }
        }
};

class Map {
    private:
        // looping index
        int i, j;
    public:
        // variables
        int width;
        int height;
        char *shape = new char[width * height];
        // function for getting the map
        void Get_Info() 
        {
            cout << "the width and height of map: ";
            cin >> width >> height;
            cout << "the shape of map: ";
            for (i = 0; i < width * height; i++) {
                cin >> shape[i];
            }
        }
        // function for printing the map
        void Print_Map()
        {
            cout << "the map:" << endl;
            for (i = 0; i < height; i++) {
                for (j = 0; j < width; j++) {
                    cout << shape[i * width + j];
                }
                cout << endl;
            }
        }
};

int Put_Puzzle_In(Map *map, Piece *puzzle);
int Try(Map *map, Piece *piece, int x, int y);

int main(void)
{
    int num_piece, num_map;     // the number of puzzles and maps
    Piece *piece;               // piece objects
    Map *map;                   // map objects
    int i;                      // looping index
    int k;

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
    // put in puzzle 1
    for (i = 0; i < num_piece; i++) {
        k = Put_Puzzle_In(map, piece + i);
        cout << "puzzle" << i + 1 << " can put? " << k << endl;
        map[0].Print_Map();
    }

    return 0;
}

int Put_Puzzle_In(Map *map, Piece *puzzle)
{
    int x, y;       // cursor
    int check = 0;  // can I put here?

    for (y = 0; y <= map->height - puzzle->height && check == 0; y++) {
        for (x = 0; x <= map->width - puzzle->width && check == 0; x++) {
            check = Try(map, puzzle, x, y);
        } 
    }
    return check;
}

int Try(Map *map, Piece *piece, int x, int y)
{
    int row, col;       // cursor
    int check = 1;      // flag to check puzzle can put in
    char pixel;         // pixel of the map

    for (row = 0; row < piece->height && check == 1; row++) {
        for (col = 0; col < piece->width && check == 1; col++) {
            pixel = map->shape[(row + y) * map->width + (col + x)];
            if (piece->shape[row * piece->width + col] == 'O') {
                if (pixel == 'O' || pixel == 'V') {
                    check = 0;
                }
            }
        }
    }
    if (check) {
        for (row = 0; row < piece->height && check == 1; row++) {
            for (col = 0; col < piece->width && check == 1; col++) {
                if (piece->shape[row * piece->width + col] == 'O') {
                    map->shape[(row + y) * map->width + (col + x)] = 'V';
                }
            }
        }
    }
    return check;
}