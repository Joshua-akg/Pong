#include <iostream>
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
        system("clear");  // or "clear"
        
        for (int i = 0; i < width+2; i++) {
            cout << "▓"; //Hexadecimal character to represent the wall
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
                if (ballX == j && ballY == i) {
                    cout << "O";    //ball
                } else if (plyr1x == j && plyr1y == i) {
                    cout << "█";    //player 1
                } else if (plyr2x == j && plyr2y == i) {
                    cout << "█";    //player 2
                } else 
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
    }    
};

int main() {
    gameEngine g(20, 40);

    g.draw();
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