#ifndef __GRID_SCENE_H__
#define __GRID_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Grid.h"

USING_NS_CC;

class GridScene : public Scene {
public:
    virtual bool init();
    static Scene* createScene();
    void FillScene();
    void menuCallback(Ref* sender);
    void buttonCallback(Ref* sender);
private:
    int cellSize = 40;
    int spacing = 1;
    int cellCount = 16;
    Size visibleSize;
    Vec2 origin;
    Grid *grid;
    Menu* layer;
};

#endif // __GRID_SCENE_H__
