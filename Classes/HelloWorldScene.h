#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include <vector>
#include <cstdlib>
USING_NS_CC;

class GridScene : public Scene {
public:
    virtual bool init() {
        if (!Scene::init()) {
            return false;
        }

        // Размер сцены
        visibleSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();

        // Размеры ячейки сетки
        this->setAnchorPoint(Vec2(0, 0));
        // Создание слоя
        auto layer = LayerColor::create(Color4B(128, 128, 128, 255), 271, 271);
        layer->setAnchorPoint(Vec2(0, 0));
        layer->setPosition(Vec2(visibleSize.width * 0.2f, visibleSize.height * 0.1f));
        this->addChild(layer);
        std::random_device dev;
        std::mt19937 rng(dev());
        if (!tiles.empty()) tiles.clear();
        tiles.reserve(cellCount * cellCount);
        // Заполнение сцены плитками трех цветов
        for (int i = 0; i < cellCount; ++i) {
            for (int j = 0; j < cellCount; ++j) {
                srand((unsigned) time(NULL));
                std::uniform_int_distribution<std::mt19937::result_type> dist6(1,3);
                int colorIndex = dist6(rng);
                Color3B tileColor;

                // Установка цвета в зависимости от индекса
                switch (colorIndex) {
                    case 1:
                        tileColor = Color3B(255, 0, 0); // Красный
                        break;
                    case 2:
                        tileColor = Color3B(0, 255, 0); // Зеленый
                        break;
                    case 3:
                        tileColor = Color3B(0, 0, 255); // Синий
                        break;
                    default:
                        break;
                }

                auto tile = LayerColor::create(Color4B(tileColor.r, tileColor.g, tileColor.b, 255), (float)cellSize, (float)cellSize);
                tile->setAnchorPoint(Vec2(0, 0));
                tile->setPosition(Vec2( i * (cellSize + spacing), j * (cellSize + spacing)));
                layer->addChild(tile);
                tiles.push_back(tile);
                };
            }
        auto mouseListener = EventListenerMouse::create();
        mouseListener->onMouseDown = CC_CALLBACK_1(GridScene::onMouseDown, this, layer);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
        return true;
    }

    void onMouseDown(Event* event, LayerColor *layer) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        Size screenSize = Director::getInstance()->getWinSize();
        if (mouseEvent) {
            Vec2 mousePos = Director::getInstance()->convertToGL(mouseEvent->getLocationInView());
            for (auto find_tile : tiles) {
                Rect bound = find_tile->getBoundingBox();
                if (bound.containsPoint(Vec2(mousePos.x, mousePos.y))) {
                    CCLOG("Tile Position: X=%f, Y=%f", (mousePos.x - 256) / 17, (mousePos.y - 375) / 17);
                    break;
                }
            }
        }
    }


    static Scene* createScene() {
        return GridScene::create();
    }

private:
    int cellSize = 16;
    int spacing = 1; // Отступ между плитками
    int cellCount = 16;
    Size visibleSize;
    Vec2 origin;
    std::vector<LayerColor*> tiles;

    CREATE_FUNC(GridScene);
};

#endif // __HELLOWORLD_SCENE_H__
