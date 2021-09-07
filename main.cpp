#include <iostream>
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

    

}

int main() {
    // test behaviour
    ball b(0, 0);
    cout << b << endl;
    b.changeRandomDir();
    cout << b << endl;
    b.move();
    cout << b << endl;

    b.changeRandomDir();
    b.move();
    cout << b << endl;

    return 0;
}