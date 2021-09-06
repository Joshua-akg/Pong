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

        void Reset() {
            x = originalX;
            y = originalY;
            direction = STOP;
        }

        void changeDir(dir d) {
            direction = d;
        }

        void changeRandomDir() {
            direction = (dir)((rand() % 6) + 1)
        }

        void Movement() {
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


};

int main() {


    

    return 0;
}