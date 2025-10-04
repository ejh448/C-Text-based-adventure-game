#include <iostream>

int main() {
    double position = 100;   // start 100 units up
    double velocity = 0;     // not moving yet
    double gravity  = -0.98; // acceleration (downward)
    double ground   = 0;

    for (int t = 0; t < 1000; t++) {
        velocity += gravity;     // apply gravity
        position += velocity;    // move ball

        if (position <= ground) {
            position = ground;               // stop at ground
            velocity = -velocity * 0.8;      // bounce
        }

        std::cout << "t=" << t << " pos=" << position << " vel=" << velocity << "\n";
    }

    return 0;
}
