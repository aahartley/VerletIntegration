#include "Physics.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Verlet!");
    Physics physics(50, 50, 10, 100, 100);
    //Physics physics;
 
   /* Particle* p = new Particle(sf::Vector2f(300.0f, 20.0f));
    physics.particles.push_back(p);
    Particle* p2 = new Particle(sf::Vector2f(330.0f, 20.0f));;
    physics.particles.push_back(p2);
    Particle* p3 = new Particle(sf::Vector2f(300.0f, 30.0f));
    physics.particles.push_back(p3);
    Particle* p4 = new Particle(sf::Vector2f(330.0f, 30.0f));
    physics.particles.push_back(p4);

    Constraint* c = new Constraint(*p, * p2, getDistance(*p, *p2));
    physics.constraints.push_back(c);
    Constraint* c2 = new Constraint( * p2, * p3, getDistance(*p2, *p3));
    physics.constraints.push_back(c2);
    Constraint* c3 = new Constraint( * p3,*p4,getDistance(*p3,*p4));
    physics.constraints.push_back(c3);
    Constraint* c4 = new Constraint( * p4, * p, getDistance(*p4, *p) );
    physics.constraints.push_back(c4);
    Constraint* c5 = new Constraint(*p, *p3, getDistance(*p, *p3));
    physics.constraints.push_back(c5); 
    Constraint* c6 = new Constraint(*p2, *p4, getDistance(*p2, *p4));
    physics.constraints.push_back(c6);*/

    sf::Clock clock;
    float dt;
    sf::Vector2f lastMouseP{ 0,0 };
    sf::Vector2f mouseP {0,0};
    bool dragging = false;
    bool tearing = false;
    window.setFramerateLimit(144);
    while (window.isOpen())
    {
 
        dt = clock.restart().asMilliseconds();
        if (dt > 0) dt = 1.0f / dt;
        //std::cout <<"dt: "<< dt<<'\n';
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // left click...
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                lastMouseP = { (float)mousePos.x,(float)mousePos.y };
                dragging = true;
               // mouseP = { lastMouseP.x,lastMouseP.y };
                std::cout << "last "<<lastMouseP.x << ' ';
            }
       
            if (event.type == sf::Event::MouseButtonReleased){
                dragging = false;
                sf::Vector2i mp = sf::Mouse::getPosition(window);
                mouseP = { (float)mp.x, (float)mp.y };
                std::cout << "curr "<<mouseP.x << '\n';
            }
        }
       
        window.clear();
        //std::cout << lastMouseP.x << ' ' << mouseP.x << '\n';
        //sf::Vector2f mouseSpeed = mouseP - lastMouseP;
        physics.update(dt,lastMouseP, dragging, mouseP);
        for (auto& p : physics.particles) {
           // p->isSelected = isInRadius(p->pos, mouseP, 20.0f);
            //p->Update(dt,physics.drag,physics.gravity,dragging,physics.elasticity,mouseSpeed);
            sf::CircleShape tmp(2.0f);
            tmp.setPosition(p->pos);
            window.draw(tmp);
        }
        for (auto& c: physics.constraints) {
           // c->Update();
            sf::Vertex line[] =
            {
                sf::Vector2f{c->p1.pos.x+2,c->p1.pos.y+2},
                sf::Vector2f{c->p2.pos.x + 2,c->p2.pos.y + 2}
            };
            window.draw(line, 2, sf::Lines);
        }
        window.display();
    }

    return 0;
}