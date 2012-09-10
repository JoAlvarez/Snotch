#include "gameobjects.h"
GameObjects::GameObjects()
{
}
void GameObjects::setObject(string type, Point ul)
{
    if(type == "box")
        objects.push_back(new Object(type, ul, 50,50,100));
    if(type == "health")
        objects.push_back(new Object(type,ul,25,25,10));
    objects[objects.size()-1]->init();
}
void GameObjects::update()
{
    for(int i = 0; i < objects.size(); i++)
        objects[i]->update();
}
void GameObjects::draw()
{
    for(int i = 0; i < objects.size(); i++)
        objects[i]->draw();
}

