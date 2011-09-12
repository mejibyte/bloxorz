Bloxorz
==========

Model
------

### Class Board
    
#### Constants

    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3
    
#### Methods    

    constructor(string board_file): Receives the name of a file where the board is written. This constructor reads that file and initializes a new board based on it.
    
    int getRows(), int getColumns(): Returns the number of rows or columns, respectively.
    
    Cell getCellAt(int row, int col): Returns the cell at position <row, col>.
    
    Tile getTile(): Returns the user's tile.
    
    bool isWinningPosition(): Returns wheter you've won the game or not.
    
    bool isLosingPosition(): Returns wheter you've lost the game or not.
    
    void moveTile(int direction): Moves the tile in the given direction, even if it results in an invalid board (like the tile outside the solid cells or standing straight on a weak cell)
    
### Class Cell
 
#### Methods

    int getRow(), int getColumn(): Returns the row or column of this cell.
    bool isHollow(): Returns true if the tile can't stand up here (no cell).
    bool isWeak(): Returns wether the cell is weak or not.
    bool isWinningHole(): Returns wether this cell is the winning hole or not.

### Tile

#### Methods

    bool isStandingUp()
    bool isLayingDown()
    vector<Cell> getCurrentCells()
    

View
--------

### Class 2DView

#### Methods

    void constructor(Board* board): Initialize a new view for this board.
    
    void refresh(): Refresh the board.
    
## Controller

### Class KeyboardController

     void run(): Runs the game and synchronizes calls between the model and the view as necessary.
     

Main
------

The `main` function of the program will look something like this:

    int main() {
        Controller c = new KeyboardController();
        c.run();
    }

