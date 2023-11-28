#include "GridScene.h"

USING_NS_CC;

  bool GridScene::init() {
    if (!Scene::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    int width = visibleSize.width * 0.6f;
    int height = visibleSize.height * 0.6f;

    this->setAnchorPoint(Vec2(0, 0));
    auto gameWindow = LayerColor::create(Color4B(0, 0, 0, 255));
    this->addChild(gameWindow);

    auto background = DrawNode::create();
    background->drawSolidRect(Vec2(0, 0),Vec2(width, height),Color4F::BLACK);
    background->setPosition(Vec2(visibleSize.width / 2 - width / 2, visibleSize.height / 2 - height / 2));
    gameWindow->addChild(background);

    layer = Menu::create();
    layer->setPosition(Vec2(visibleSize.width / 2 - width / 2, visibleSize.height / 2 - height / 2));
    gameWindow->addChild(layer);

    auto buttons = Menu::create();
    buttons->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    buttons->setPosition(80, visibleSize.height - 50);
    gameWindow->addChild(buttons);

    auto buttonSprite = Sprite::create("button.png", Rect(0, 0, cellSize * 3, cellSize + cellSize / 2));
    auto menuItem = MenuItemSprite::create(buttonSprite, buttonSprite, CC_CALLBACK_1(GridScene::buttonCallback, this));
    buttons->addChild(menuItem, 1);

    auto hintLabel = Label::createWithSystemFont("RESTART", "Arial", 18);
    hintLabel->setPosition(menuItem->getContentSize().width * 0.5f, menuItem->getContentSize().height * 0.5f + 5);
    hintLabel->enableShadow();
    menuItem->addChild(hintLabel);
    menuItem->setCallback(CC_CALLBACK_1(GridScene::buttonCallback, this));
    
    grid = new Grid;
    grid->FirstInitGrid();
    FillScene();
    return true;
}

 void GridScene::FillScene() {
     for (int i = 0; i < cellCount; ++i) {
         for (int j = 0; j < cellCount; ++j) {
             auto blockSprite = Sprite::create("block.png", Rect(0, 0, cellSize, cellSize));
             switch (grid->GetGrid()[cellCount - i - 1][j]) {
                 case 0:
                     blockSprite->setColor(Color3B(0, 0, 0));
                     break;
                 case 1:
                     blockSprite->setColor(Color3B(255, 0, 0));
                     break;
                 case 2:
                     blockSprite->setColor(Color3B(0, 255, 0));
                     break;
                 case 3:
                     blockSprite->setColor(Color3B(0, 0, 255));
                     break;
                 default:
                     break;
             }
             auto menuItem = MenuItemSprite::create(blockSprite, blockSprite, CC_CALLBACK_1(GridScene::menuCallback, this));
             menuItem->setPosition(Vec2((j + 0.5f) * (cellSize + spacing), (i + 0.5f) * (cellSize + spacing)));
             layer->addChild(menuItem, 1);
         }
     }
 }

void GridScene::menuCallback(Ref* sender) {
    auto item = (MenuItemSprite*)sender;
    int x = item->getPosition().x / (cellSize + spacing);
    int y = item->getPosition().y / (cellSize + spacing);
    if (grid->CheckNeighbours(abs(y - cellCount + 1), x)) {
        layer->cleanup();
        FillScene();
    }
}

void GridScene::buttonCallback(Ref* sender) {
      layer->cleanup();
      grid->FirstInitGrid();
      FillScene();
}


Scene* GridScene::createScene() {
    auto scene = Scene::create();
    auto gridScene = new GridScene();
    gridScene->autorelease();
    if (gridScene->init())
        scene->addChild(gridScene);
    else
        return nullptr;
    return scene;
}

CREATE_FUNC(GridScene);