#include <iostream>
#include <conio.h>
#include <time.h>


using namespace std;

enum dir {STOP = 0, 
          LEFT = 1, 
          UPLEFT = 2, 
          DOWNLEFT = 3, 
          RIGHT = 4, 
          UPRIGHT = 5, 
          DOWNRIGHT = 6};

class ball {
    private:
    int x, y;
    int originalX, originalY;
    dir direction;
    
    public:
    ball(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getDirection() {
        return direction;
    }

    void reset() {
        x = originalX;
        y = originalY;
        direction = STOP;
    }

    void changeDir(dir d) {
        direction = d;
    }

    void changeRandomDir() {
        direction = (dir)((rand() % 6) + 1);
    }

    void move() {
        switch (direction) {
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--; y--;
            break;
        case DOWNLEFT:
            x--; y++;
            break;
        case UPRIGHT:
            x++; y--;
            break;
        case DOWNRIGHT:
            x++; y++;
            break;
        default:
            break;
        }
    }

    friend ostream & operator<<(ostream & o, ball c) {
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

class paddle {
private:
    int x, y;
    int originalX, originalY;
    
public:
    paddle() {
        x = 0;
        y = 0; 
    }

    paddle(int xPos, int yPos) : paddle() {
        originalX = xPos;
        originalY = yPos;
        x = xPos;
        y = yPos; 
    }

    void reset() {
        x = originalX; 
        y = originalY;
    }

    inline int getX() {
        return x;
    }

    inline int getY() {
        return y;
    }

    void moveUp() {
        y--;
    }

    void moveDown() {
        y++;
    }

    friend ostream & operator<<(ostream & o, paddle p) {
        o << "Paddle [" << p.x << "," << p.y << "]";
        return o;
    }

};

class gameEngine {
private:
    int height, width;
    int score1, score2;
    char up1, up2, down1, down2;
    bool gameOver;
    ball *pball;
    paddle *p1;
    paddle *p2;

public:
    gameEngine(int h, int w) {
        srand(time(NULL));      //set the seed for the randomiser
        gameOver = false;

        //Set the key bindings for the controls
        up1 = 'w'; down1 = 's';
        up2 = 'i'; down2 = 'k';

        //set the initial scores
        score1 = score2 = 0;
        
        
        height = h;
        width = w;

        pball = new ball(w / 2, h / 2);

        //Create player objects with positions
        p1 = new paddle(1, (h/2) -3);
        p2 = new paddle(w - 2, (h/2) -3);
    }

    ~gameEngine() {
        delete pball, p1, p2;
    }

    void increaseScore(paddle *player) {
        if (player == p1) {
            score1++;
        } else if (player == p2) {
            score2++;
        }

        pball -> reset();
        p1 -> reset();
        p2 -> reset();
    }

    void draw() {
        system("cls");  // or "clear"
        
        for (int i = 0; i < width+2; i++) {
            cout << "▓"; //character to represent the wall
        }
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                //get ball co-ords
                int ballX = pball -> getX();
                int ballY = pball -> getY();

                //get player co-ords
                int plyr1x = p1 -> getX();
                int plyr1y = p1 -> getY();

                int plyr2x = p2 -> getX();
                int plyr2y = p2 -> getY();

                if (j == 0) {
                    cout << "▓";
                }

                //Draw at the corresponding co-ordinates
                //Rearrange else ifs later
                if (ballX == j && ballY == i) {
                    cout << "O";    //ball
                } else if (plyr1x == j && plyr1y == i) {
                    cout << "█";    //player 1
                } else if (plyr2x == j && plyr2y == i) {
                    cout << "█";    //player 2
                }

                //blocks to make up the paddles
                else if (plyr1x == j && plyr1y + 1 == i) {
                    cout << "█";    
                }
                else if (plyr1x == j && plyr1y + 2 == i) {
                    cout << "█";    
                }
                else if (plyr1x == j && plyr1y + 3 == i) {
                    cout << "█";    
                }

                else if (plyr2x == j && plyr2y + 1 == i) {
                    cout << "█";    
                }
                else if (plyr2x == j && plyr2y + 2 == i) {
                    cout << "█";    
                }
                else if (plyr2x == j && plyr2y + 3 == i) {
                    cout << "█";    
                }

                else 
                    cout << " ";

                if (j == width - 1) {
                    cout << "▓";
                }
            }
            cout << endl;
        }        
        
        for (int i = 0; i < width+2; i++) {
            cout << "▓";
        }
        cout << endl;

        cout << "Player 1: " << score1 << endl << "Player 2: " << score2 << endl;
    }    

    void input() {
        pball -> move();

        int ballX = pball -> getX();
        int ballY = pball -> getY();

        //get player co-ords
        int plyr1x = p1 -> getX();
        int plyr1y = p1 -> getY();

        int plyr2x = p2 -> getX();
        int plyr2y = p2 -> getY();

        if (_kbhit()) {     //If keyboard is hit
            char current = _getch();

            //if available,move paddles according to input
            if (current == up1) {
                if (plyr1y > 0) {
                    p1 -> moveUp();
                }
            }

            if (current == up2) {
                if (plyr2y > 0) {
                    p2 -> moveUp();
                }
            }

            if (current == down1) {
                if (plyr1y + 4 < height) {
                    p1 -> moveDown();
                }
            }

            if (current == down2) {
                if (plyr2y + 4 < height) {
                    p2 -> moveDown();
                }
            }

            //If the ball is stopped when pressed, set a random direction
            if (pball -> getDirection() == STOP) {
                pball -> changeRandomDir();
            }

            //if the key pressed is q, game is over
            if (current == 'q') {
                gameOver = true;
            }
        }
    }

    void logic() {
        int ballX = pball -> getX();
        int ballY = pball -> getY();

        //get player co-ords
        int plyr1x = p1 -> getX();
        int plyr1y = p1 -> getY();

        int plyr2x = p2 -> getX();
        int plyr2y = p2 -> getY();

        //Left paddle logic
        for (int i = 0; i < 4; i++) {
            if (ballX == plyr1x + 1) {
                if (ballY == plyr1y + i) {  //if left paddle is hit
                //ball either goes right, upright or downright
                    pball -> changeDir((dir)((rand() % 3)+4)); 
                }
            }
        }

        //Right paddle logic
        for (int i = 0; i < 4; i++) {
            if (ballX == plyr2x - 1) {
                if (ballY == plyr2y + i) {  //if left paddle is hit
                //ball either goes right, upright or downright
                    pball -> changeDir((dir)((rand() % 3)+1)); 
                }
            }
        }

        //Bottom wall logic
        if (ballY == height - 1) {
            pball -> changeDir(pball -> getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        }

        //top wall logic
        if (ballY == 0) {
            pball -> changeDir(pball -> getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        }

        //right wall logic
        if (ballX == width-1) {
            increaseScore(p1);
        }

        //Left wall logic
        if (ballX == 0) {
            increaseScore(p2);
        }
    }

    void run() {
        while (!gameOver) {
            draw();
            input();
            logic();

        }        
    }
};

int main() {
    gameEngine g(20, 40);
    g.run();
    // g.draw();
    // test behaviour

    // paddle p1(0,0);
    // paddle p2(10,0);

    // cout << p1 << endl;
    // cout << p2 << endl;

    // p1.moveUp();
    // p2.moveDown();

    // cout << p1 << endl;
    // cout << p2 << endl;

    // ball b(0, 0);
    // cout << b << endl;
    // b.changeRandomDir();
    // cout << b << endl;
    // b.move();
    // cout << b << endl;

    // b.changeRandomDir();
    // b.move();
    // cout << b << endl;

    return 0;
}