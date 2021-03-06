#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

//#define  METHOD_1 1
#define  METHOD_2 2
//#define  METHOD_3 3

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto width = visibleSize.width;
	auto height = visibleSize.height;

	//设置原型遮罩头像方法1  START
	//通过设置层级的方法，利用遮罩实现裁剪，遮罩需要为PNG格式，并且存有alpha通道
#ifdef METHOD_1
	auto headBg = Sprite::create("head_bg_1.png");
	auto headIcon = Sprite::create("head.png");
	auto bg = Sprite::create("bg.jpg");

	bg->setPosition(width / 2, height / 2);
	headIcon->setPosition(width / 2, height / 2);
	headBg->setPosition(width / 2, height / 2);

	this->addChild(bg);
	this->addChild(headIcon);
	this->addChild(headBg);
#endif
	//设置原型遮罩头像方法1  END


	//设置原型遮罩头像方法2  START
	//利用ClipNode实现遮罩
#ifdef METHOD_2
	auto headIcon = Sprite::create("head.png");
	auto bg = Sprite::create("bg.jpg");

	bg->setPosition(width / 2, height / 2);
	this->addChild(bg);

	//设置遮罩
	auto stencil = Sprite::create("head_bg.png");
	//设置ClipNode
	auto clipNode = ClippingNode::create();
	//设置裁剪蒙板
	clipNode->setStencil(stencil);
	//设置裁剪模式:底板可见
	clipNode->setInverted(false);
	//设置alpha阈值为0
	clipNode->setAlphaThreshold(0);
	this->addChild(clipNode);

	//设置被裁剪的内容
	clipNode->addChild(headIcon);
	clipNode->setPosition(width / 2, height / 2);

#endif

	//设置原型遮罩头像方法3  START
	//将ClipNode写成一个工具方法，实现遮罩
#ifdef  METHOD_3
	auto clipNode = this->createTextureClip("head.png", "head_bg.png", false, 0.0f);
	clipNode->setPosition(width / 2, height / 2);
	this->addChild(clipNode);
#endif

    return true;
}

//创建一个ClipNode的工具方法，参数:底图路径,遮罩路径,裁剪的模式,alpah阈值
cocos2d::ClippingNode* HelloWorld::createTextureClip(const std::string& imagePath, const std::string& maskPath, const bool inverted, const float alphaThreshold)
{
	auto clipNode = ClippingNode::create();
	auto stencil = Sprite::create(maskPath);
	clipNode->setStencil(stencil);
	clipNode->setInverted(inverted);
	clipNode->setAlphaThreshold(alphaThreshold);
	auto image = Sprite::create(imagePath);
	clipNode->addChild(image);
	return clipNode;
}