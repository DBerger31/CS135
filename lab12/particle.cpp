
#include <iostream>
using namespace std;

// creates a class called particle
class Particle {
private:
    double x;  // position, 2D coordinates
    double y;
    double vx; // velocity
    double vy;

public:
    // accessor functions for the current position of the particle
    double getX();
    double getY();
    // move the particle
    void move(double dt);

    // Constructor Called to initialize private member variables
    // when a particle object gets created
    Particle(double posx, double posy, double velx, double vely);
    // Default constructor, will assume pos=(0,0), vel=(0,0)
    Particle();
};


int main() {
    // Create a particle object using the constructor
    Particle particle1 (11.0, 12.0,  0.5, -0.4);
    // Create another particle object, but this time
    // using the default constructor
    Particle particle2;

    particle1.move(10.0);
    cout << particle1.getX() << endl;
    cout << particle1.getY() << endl;
}


// Implementation of the class Particle
double Particle::getX() { // gets the x coordinate of the particle
    return x;
}

double Particle::getY() {
    return y;
}

void Particle::move(double dt) {
    x += vx * dt;  y += vy * dt;
}

Particle::Particle(double posx, double posy, double velx, double vely) {
    x = posx;   y = posy;
    vx = velx;  vy = vely;
}

Particle::Particle() : x(0), y(0), vx(0), vy(0) { }
