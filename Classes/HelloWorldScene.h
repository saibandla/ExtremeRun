#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#define PTM_RATIO 32.0
#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"
#include "Box2d/Box2d.h"
#include "SimpleAudioEngine.h"
#include "sqlite3.h"
#include "AppDelegate.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
private:
	CCParallaxNodeExtras *_backgroundNode;
	CCSprite *_cloud1,*_cloud2,*_trees,*_city1,*_city2;
	CCParticleSystem*    m_emitter;
	CCParticleSystem* m_emitter1;

protected:
	cocos2d::CCArray *_projectiles;
	cocos2d::CCArray *_coins;
	cocos2d::CCArray *_targets;
	cocos2d::CCArray *_cars;
	cocos2d::CCArray *_powers;
	HelloWorld()
		:_projectiles(NULL),
		 _coins(NULL),
		 _targets(NULL),
		 _powers(NULL)
		{
		};

public:
    b2World *_world;
    b2Body *_groundBody;
    b2Fixture *_bottomFixture;
    b2Fixture *_ballFixture;
    b2Body *_body;
	CCSprite *_ball;
	b2BodyDef ballBodyDef;
	int flag;
	CCParticleSystem *emitter;
	sqlite3* m_db;
    virtual bool init();
    void partic();
    void particremoved(float dt);
    void partic1();
    void particremoved1(float dt);
    void Bgspeed(CCPoint ss);
    void enteranme();
    void bringRain(float dt);
    void runCar(float dt);
    void runman(string str);
    void addCoins();
    void cht();
    void coinSequence();
    void getscore();
    void mute();
    void volume();
    void powerpack1();
    void flysprite();
    void tick(float dt);
    void mainentery();
    void applicationDidEnterBackground();
    void updatemeters(float dt);
    void makeman();
    void mainmenu();
    void hacked();
    void mainScene();
    void quitscene();
    void reenter();
    void creditcls();
    void closecredit();
    void scoreall();
    void buylife();
    void buylife2();
    void diamond(float dt);
    void movedtoend(CCNode* sender);
    void audio();
    void start();
    void resat();
    void resanim();
    void decjems();
    void closeselect();
    void clo();
    void checksys(float dt);
    void scoredisplay();
    void callpower(float dt);
    void popup(float dt);
    void ccTouchesBegan(cocos2d::CCSet *touches,cocos2d::CCEvent *event);
    void ccTouchesEnded(cocos2d::CCSet *touches,cocos2d::CCEvent *event);
    int _projectilesDestroyed;
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    void update(float dt);
    void help();
    void settingss();
    void spriteMoveFinished(CCNode *sender);
    void goldSpriteMovedFinished(CCNode *sender);
    void carSpriteMovedFinished(CCNode *sender);
    void powerMovedFinished(CCNode *sender);
    CREATE_FUNC(HelloWorld);
    virtual ~HelloWorld();
};

#endif // __HELLOWORLD_SCENE_H__
