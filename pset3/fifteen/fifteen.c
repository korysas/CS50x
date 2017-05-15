/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int size, int gameboard[][size]);
void draw(int size, int gameboard[][size]);
bool move(int tile, int size, int gameboard[][size]);
bool won(void);
bool get_coords(int size, int gameboard[][size], int coords[], int value);
bool check_adjacent(int size, int gameboard[][size], int coords[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    int gameboard[d][d];
    init(d, gameboard);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d, gameboard);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, d, gameboard))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int size, int gameboard[][size])
{
    // value starts at the max value
    int value = size * size - 1;

    // i represents row, j represents element in row
    int i, j;   
    // iterate through rows of gameboard
    for (i = 0; i < size; i++)
    {
        // iterate through each element in the row
        for (j = 0; j < size; j++)
        {
            gameboard[i][j] = value--;
        }
    }

    // switch value of 1 and 2 in order to make to puzzle solvable if odd number of tiles
    if (size % 2 == 0)
    {
        int temp = gameboard[size - 1][size - 2];
        gameboard[size - 1][size - 2] = gameboard[size - 1][size - 3];
        gameboard[size - 1][size - 3] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(int size, int gameboard[][size])
{
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (gameboard[i][j] != 0)
                printf("%d\t", gameboard[i][j]);
            else
                printf("_\t");
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile, int size, int gameboard[][size])
{
    // don't allow the user to move the blank tile
    if (tile == 0)
        return false;

    // get the coordinates of this tile
    int coords[2];
    bool is_found = get_coords(size, gameboard, coords, tile);

    if (!is_found)
        return false;

    // check adjacent coordinates to see if there is empty space
    int coord_to_move[2];
    coord_to_move[0] = coords[0];
    coord_to_move[1] = coords[1];
    bool is_valid_move = check_adjacent(size, gameboard, coord_to_move);

    // if there is empty space, make the swap and signify we have made the move
    if (is_valid_move)
    {
        gameboard[coord_to_move[0]][coord_to_move[1]] = tile;
        gameboard[coords[0]][coords[1]] = 0;
        return true;
    }

    // if no empty space adjacent, it's an illegal move
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    return false;
}

/**
 * Populates the input array with x and y coordinates where the specified value is found
 * returns a boolean to signify if that value was found in the gameboard
 */
bool get_coords(int size, int gameboard[][size], int coords[], int value)
{
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (gameboard[i][j] == value)
            {
                // populate x and y coordinates into coords array
                coords[0] = i;
                coords[1] = j;
                return true;
            }
        }
    }

    return false;
}

/**
 * Checks the coordinate to the left, right, above, and below to see if we can
 * move to one of these spots
 */
bool check_adjacent(int size, int gameboard[][size], int coords[])
{
    int x, y;
    x = coords[0];
    y = coords[1];

    // check to the left
    if (x - 1 >= 0 && gameboard[x - 1][y] == 0)
    {
        coords[0] = x - 1;
        coords[1] = y;
        return true;
    }

    // check above
    if (y - 1 >= 0 && gameboard[x][y - 1] == 0)
    {
        coords[0] = x;
        coords[1] = y - 1;
        return true;
    }

    // check to the right
    if (x + 1 < size && gameboard[x + 1][y] == 0)
    {
        coords[0] = x + 1;
        coords[1] = y;
        return true;
    }

    // check below
    if (y + 1 < size && gameboard[x][y + 1] == 0)
    {
        coords[0] = x;
        coords[1] = y + 1;
        return true;
    }

    return false;
}
