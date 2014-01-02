#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"
#include "unistd.h"
#include "iostream.h"
#include "sqlite3.h"
#include "map"
#include "vector"
#include "cocos2d.h"
using namespace std;
#define worldGravity -40.0f
#define jumpImpulse -0.85f*worldGravity
#define playerMass 4.0
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
float volu=1.0;
std::vector<int> scores;
string nale;
CCSprite *off,*on;
int hackvol=0;
bool m_touch=false;
int j=0,k=0,coincount=0,m4=0,scn=0,lives=5,jemscount=6,venstat=0,kalam=0,beatcnt=0,tch1=0,pas=0,rf=0,newentry=1,rc,nb=0;
float runcnt=0.0f,fastness=3.0,bx,by=80.0,flyx=200.0,flyy=80.0;
string strr2,manstate,name123;
CCPoint bgspeed;
CCTextFieldTTF *ga;
CCMenu *pMenu,*plauy,*_GameOvermenu,*buymenu;
CCMenuItemImage *pCloseItem,*paus,*ply,*audio;
CCSprite *sprite,*coinimg,*jem,*_gameover,*buy;
CCLabelTTF* pLabel1,*pLabel2,*pLabel3,*pLabel4;
 char * path;
 string path1;
struct vehicle
{
	int index;
	string v_type;
	int sprite_cnt;
};
struct vehicle vehicles[5];
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool HelloWorld::init()
{
	 CCSize size = CCDirector::sharedDirector()->getWinSize();
	 fprintf(stderr,"size: %f",size.width);
	 if(size.width>1024)
	 {
		 fprintf(stderr,"size: %f",size.height);

		 path1="z10/";
	 }
	 else
	 {
		 flyx=120.0,flyy=80.0;
		 path1="q10/";
	 }
    if ( !CCLayer::init() )
    {
        return false;
    }
    off=CCSprite::create((path1+"sound-off@2x.png").c_str());
    			on=CCSprite::create((path1+"sound-on@2x.png").c_str());
    			fprintf(stderr,"size: jajsjsj");
    			SimpleAudioEngine::sharedEngine()->playBackgroundMusic((path1+"backgroundmusic.wav").c_str(),true);
    				SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7f);
    rc = sqlite3_open_v2("data/database.db", &m_db, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE, NULL);
    fprintf(stderr,"\ncreating database 1");
    if (rc != SQLITE_OK)
    {
    	fprintf(stderr, "Could not open scores db. %d\n", rc);
    }
    if(rc==SQLITE_OK)
    {
    	fprintf(stderr, "created databse %d", rc);
    }
    static const char* createSql ="create table if not exists store(name text,score numeric,coins numeric)";
  	sqlite3_stmt* createStmt;
  	int rc15 = sqlite3_prepare_v2(m_db, createSql, strlen(createSql), &createStmt, NULL);
  	if (rc15 == SQLITE_OK)
  	{
  		fprintf(stderr, "\n Sqlite table created successfully %d\n", rc);
  	}
  	sqlite3_step(createStmt);
  	if( sqlite3_step(createStmt)==SQLITE_DONE)
  	{
  		sqlite3_finalize(createStmt);
  	}
  	sqlite3_finalize(createStmt);
  	int sq=sqlite3_step(createStmt);
  	if(sq==SQLITE_DONE)
  	{
  		fprintf(stderr,"\nupdate statement:%d",sq);
  	}
    sqlite3_close_v2(m_db);
    HelloWorld::mainmenu();
    this->schedule(schedule_selector(HelloWorld::cht));

    return true;
}
struct user
{
	char *key;
};

void HelloWorld::mute()
{
	volu=0.0;
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
}
void HelloWorld::volume()
{
	volu=1.0;
	if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()==false)
				{
					SimpleAudioEngine::sharedEngine()->playBackgroundMusic((path1+"backgroundmusic.wav").c_str(),true);
				}
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}
void HelloWorld::getscore()
{
	int rc7=	sqlite3_open_v2("data/database.db",&m_db,SQLITE_OPEN_READONLY,NULL);
	if(rc7==SQLITE_OK)
	{
		fprintf(stderr,"\ndatabase is opened succesfully");
	}
	static const char* selectSql = "SELECT * FROM store";
	sqlite3_stmt* selectStmt;
	int rc10 = sqlite3_prepare_v2(m_db, selectSql, strlen(selectSql), &selectStmt, NULL);
	if (rc10 == SQLITE_OK)
	{
		fprintf(stderr, "Sqlite select %d\n", rc);
	}
	rc10 = sqlite3_step(selectStmt);
	while (rc10 == SQLITE_ROW)
	{
		const unsigned char *st=sqlite3_column_text(selectStmt,0);
		if((const char*)st==name123)
		{
			newentry=0;
		}
		scores.push_back(sqlite3_column_int(selectStmt, 1));
		rc10 = sqlite3_step(selectStmt);
	}
	sqlite3_finalize(selectStmt);
	sqlite3_close_v2(m_db);
	int highscore=0;
	for(std::vector<int>::iterator scr=scores.begin();scr!=scores.end();scr++)
	{
		if(*scr>highscore)
		{
			highscore=*scr;
		}
	}
	char strhigh[100]={0};
	sprintf(strhigh,"High Score : %d",highscore);
	char displaystr[100];
	sprintf(displaystr,"Total Eggs : %d",m4);

	if(newentry==1)
	{
		rc = sqlite3_open_v2("data/database.db", &m_db, SQLITE_OPEN_READWRITE, NULL);
		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "Could not open scores db. %d\n", rc);
		}
		if(rc==SQLITE_OK)
		{
			fprintf(stderr, "created databse %d", rc);
		}
		char str3[1000]={0};
		std::string st((char *)name123.c_str());
		sprintf(str3,"INSERT INTO store(name,score,coins) values('%s',%d,%d)",st.c_str(),m4,coincount);
		static const char* insertSql =str3;//"INSERT INTO store(name,score) values('sai',10)" ;
		sqlite3_stmt* insertStmt;
		int rc = sqlite3_prepare_v2(m_db, insertSql, strlen(insertSql), &insertStmt, NULL);
		if (rc == SQLITE_OK)
		{
			fprintf(stderr, "\n insertion executed %d\n", rc);
		}
		int   rc5 = sqlite3_bind_text(insertStmt,1,name123.c_str(),st.length(),NULL);
		if (rc5 == SQLITE_OK)
		{
			fprintf(stderr, "\n from Sqlite bind  %d\n", rc5);
		    sqlite3_finalize(insertStmt);
		}
		int   rc0 = sqlite3_bind_int(insertStmt,2,m4);
		if (rc0 == SQLITE_OK)
		{
			fprintf(stderr, "\n from Sqlite bind  %d\n", rc5);
		    sqlite3_finalize(insertStmt);
		}
		int   rc00 = sqlite3_bind_int(insertStmt,3,coincount);
		if (rc00 == SQLITE_OK)
		{
			fprintf(stderr, "\n from Sqlite bind  %d\n", rc5);
		    sqlite3_finalize(insertStmt);
		}
		int rc6 = sqlite3_step(insertStmt);
		if (rc6 == SQLITE_DONE)
		{
			fprintf(stderr, "\nfrom Sqlite insert %d\n", rc6);
		    sqlite3_finalize(insertStmt);
		}
		if(rc6 !=SQLITE_DONE)
		{
					    fprintf(stderr,sqlite3_errmsg(m_db));
		}
		sqlite3_finalize(insertStmt);
		sqlite3_close_v2(m_db);
	}
	else if(newentry==0)
	{
		char str3[1000]={0};
		int rc7=	sqlite3_open_v2("data/database.db",&m_db,SQLITE_OPEN_READONLY,NULL);
		if(rc7==SQLITE_OK)
		{
			fprintf(stderr,"\ndatabase is opened succesfully");
		}
		sprintf(str3,"SELECT score FROM store where name='%s'",name123.c_str());
		static const char* selectSql = str3;
		sqlite3_stmt* selectStmt;
		int rc10 = sqlite3_prepare_v2(m_db, selectSql, strlen(selectSql), &selectStmt, NULL);
		if (rc10 == SQLITE_OK)
		{
			    		     fprintf(stderr, "Sqlite select %d\n", rc);
		}
		rc10 = sqlite3_step(selectStmt);
		int cursc;
		if(rc10==SQLITE_ROW)
		{
			cursc=sqlite3_column_int(selectStmt,0);
		}
		sqlite3_finalize(selectStmt);
		sqlite3_close_v2(m_db);
		if(m4>cursc)
		{
			fprintf(stderr,"\n updating old entery");
		    int rc14=	sqlite3_open_v2("data/database.db",&m_db,SQLITE_OPEN_READWRITE,NULL);
		    if(rc14==SQLITE_OK)
		    {
		    }
		    char str14[1000]={0};
		    sprintf(str14,"UPDATE store SET score=%d,coins=%d WHERE name='%s'",m4,coincount,name123.c_str());
		    static const char* updateSql =str14;
		    sqlite3_stmt* updateStmt;
		    int rc15 = sqlite3_prepare_v2(m_db, updateSql, strlen(updateSql), &updateStmt, NULL);
		    if (rc15 == SQLITE_OK)
		    {
		     	    	     fprintf(stderr, "Sqlite updated successfully %d\n", rc);
		    }
		    sqlite3_bind_int(updateStmt,2,m4);
		    if(sqlite3_bind_int(updateStmt,2,m4)==SQLITE_OK)
		    {
		    	fprintf(stderr,"\nit is not possible 1");
		     	sqlite3_finalize(updateStmt);
		    }
		    sqlite3_step(updateStmt);
		    if( sqlite3_step(updateStmt)==SQLITE_DONE)
		    {
		    	fprintf(stderr,"\nit is not possible 1");
		     	sqlite3_finalize(updateStmt);
		    }
		    sqlite3_finalize(updateStmt);
		    sqlite3_close_v2(m_db);
		}
	}
}
void HelloWorld::mainentery()
{
	const char *name=ga->getString();

	name123=(string)name;
	if(name123.length()!=0)
	{
		ga->detachWithIME();
	}
	HelloWorld::mainScene();
}
void HelloWorld::mainScene()
{
	if(name123.length()!=0)
	{



		rf=0;
		scn=1;
		m_touch=false;
		newentry=1;
		this->removeAllChildren();
		lives=5;
		jemscount=0;
		coincount=0;
		m4=0;
		kalam=0;
		pas=0;
		HelloWorld::start();
		char a[10];
		if(volu>0.0)
					{
						SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7f);
					}
		sprintf(a,"score%d",nb++);
		_projectiles = new CCArray;
		_coins = new CCArray;
	    _powers=new CCArray;
	    _targets=new CCArray;
	    _cars=new CCArray;
	    CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite *heart=CCSprite::create((path1+"heart.png").c_str());
		heart->setPosition(ccp(35,size.height-25));
		this->addChild(heart);
		pLabel3=CCLabelTTF::create("5", "Arial",35.0f);

		if(path1=="z10/")
		{
		pLabel3->setPosition(ccp(85,size.height-25));
		}
		else
		{
			pLabel3->setPosition(ccp(75,size.height-25));
		}
		pLabel3->setAnchorPoint(ccp(0.5,0.5));
		pLabel3->setColor(ccc3(0,0,200));
		this->addChild(pLabel3,1);
		pLabel1 = CCLabelTTF::create("0 m", "Arial",35.0f);
		if(path1=="z10/")
		{
			pLabel1->setPosition(ccp(600,size.height-25));
		}
		else
		{
			pLabel1->setPosition(ccp(300,size.height-25));
		}

		pLabel1->setAnchorPoint(ccp(0.5,0.5));
		pLabel1->setColor(ccc3(0,0,200));
		CCSprite *spritemt=CCSprite::create((path1+"meterbackground.png").c_str());
		spritemt->setPosition(pLabel1->getPosition());
		this->addChild(spritemt,0);
		this->addChild(pLabel1,1);
		coinimg=CCSprite::create((path1+"coin.png").c_str());
		if(path1=="z10/")
				{
			coinimg->setPosition(ccp(1180,size.height-25));
				}
				else
				{
					coinimg->setPosition(ccp(650,size.height-25));
				}

		this->addChild(coinimg);
		pLabel2 = CCLabelTTF::create(" 0", "Arial",35.0f);
		if(path1=="z10/")
				{
			pLabel2->setPosition(ccp(1070,size.height-25));
				}
				else
				{
					pLabel2->setPosition(ccp(580,size.height-25));
				}

		pLabel2->setColor(ccc3(0,0,200));
		this->addChild(pLabel2,1);
		jem=CCSprite::create((path1+"jems.png").c_str());
		if(path1=="z10/")
				{
			jem->setPosition(ccp(900,size.height-25));
				}
				else
				{
					jem->setPosition(ccp(500,size.height-25));
				}

		this->addChild(jem);
		pLabel4 = CCLabelTTF::create(" 0", "Arial",35.0f);
		if(path1=="z10/")
				{
			pLabel4->setPosition(ccp(840,size.height-25));
				}
				else
				{
					pLabel4->setPosition(ccp(460,size.height-25));
				}

		pLabel4->setColor(ccc3(0,0,200));
		this->addChild(pLabel4,1);
		vehicles[0].index=1;
		vehicles[0].v_type="bluecar";
		vehicles[0].sprite_cnt=14;
		vehicles[1].index=2;
		vehicles[1].v_type="gtruck";
		vehicles[1].sprite_cnt=7;
		vehicles[2].index=3;
		vehicles[2].v_type="bmw";
		vehicles[2].sprite_cnt=29;
		vehicles[3].index=4;
		vehicles[3].v_type="schoolbus";
		vehicles[3].sprite_cnt=14;
		vehicles[4].index=5;
		vehicles[4].v_type="ytruck";
		vehicles[4].sprite_cnt=8;
		vehicles[4].index=5;
		vehicles[4].v_type="lorry";
		vehicles[4].sprite_cnt=15;

			if(volu==1.0)
			{
	    pCloseItem = CCMenuItemImage::create(
	    		(path1+"sound-off@2x.png").c_str(),
	    		(path1+"sound-off@2x.png").c_str(),
			                                    this,
			                                    menu_selector(HelloWorld::audio));
			}
			else if(volu==0.0)
			{
			    pCloseItem = CCMenuItemImage::create(
			    		(path1+"sound-on@2x.png").c_str(),
			    		(path1+"sound-on@2x.png").c_str(),
					                                    this,
					                                    menu_selector(HelloWorld::audio));

			}

		paus = CCMenuItemImage::create(
				(path1+"pause.png").c_str(),
				(path1+"pause.png").c_str(),
			                                    this,
			                                    menu_selector(HelloWorld::applicationDidEnterBackground));
		ply = CCMenuItemImage::create(
				(path1+"CloseNormal.png").c_str(),
				(path1+"CloseSelected.png").c_str(),
			                                    this,
			                                    menu_selector(HelloWorld::menuCloseCallback));

		_backgroundNode=CCParallaxNodeExtras::node();
		if(path1=="z10/")
				{
			pCloseItem->setPosition(ccp(size.width - 32, size.height-35));
			paus->setPosition(ccp(size.width-70,60));
				}
				else
				{
					pCloseItem->setPosition(ccp(size.width - 25, size.height-25));
							paus->setPosition(ccp(size.width-38,50));

				}


		ply->setPosition(ccp(size.width-200,50));
		pMenu = CCMenu::create(pCloseItem,NULL);
		pMenu->setTag(303);
		plauy=CCMenu::create(paus,NULL);
		//paus->setTag(1245698);
		plauy->setPosition(CCPointZero);
		this->addChild(plauy,1);
		plauy->setTag(80234);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);
	    this->addChild(_backgroundNode,-9);
	    b2Vec2 gravity = b2Vec2(0.0f, worldGravity);
	   	_world = new b2World(gravity);
	   	b2BodyDef groundBodyDef;
	   	groundBodyDef.position.Set(0,2);
	   	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	   	b2EdgeShape groundEdge;
	   	b2FixtureDef boxShapeDef;
	   	boxShapeDef.shape = &groundEdge;
	   	//wall definitions
	   	groundEdge.Set(b2Vec2(0,0), b2Vec2(size.width/PTM_RATIO, 0));
	   	groundBody->CreateFixture(&boxShapeDef);
	   	groundEdge.Set(b2Vec2(0,0), b2Vec2(0,size.height/PTM_RATIO));
	   	groundBody->CreateFixture(&boxShapeDef);
	   	groundEdge.Set(b2Vec2(0, size.height/PTM_RATIO),
	   	b2Vec2(size.width/PTM_RATIO, size.height/PTM_RATIO));
	   	groundBody->CreateFixture(&boxShapeDef);
	   	groundEdge.Set(b2Vec2(size.width/PTM_RATIO, size.height/PTM_RATIO),
	   	b2Vec2(size.width/PTM_RATIO, 0));
	   	groundBody->CreateFixture(&boxShapeDef);
	    _trees=CCSprite::create((path1+"backcopy.png").c_str());
	    _trees->setTag(665);
	    _city1=CCSprite::create((path1+"backcopy.png").c_str());
	    _city1->setTag(666);
	    _city2=CCSprite::create((path1+"backcopy.png").c_str());
	    _city2->setTag(667);
	     bgspeed=ccp(0.5,0.5);
	    _backgroundNode->addChild(_trees,0,bgspeed,ccp(size.width/2,size.height/2));
	    _backgroundNode->addChild(_city1,0,bgspeed,ccp(0,size.height/2));
	    _backgroundNode->addChild(_city2,0,bgspeed,ccp(_city1->getContentSize().width,size.height/2));
	    _trees->setTag(125);
	   _city1->setTag(126);
	   _city2->setTag(127);
	   HelloWorld::runman("boy ");
	   HelloWorld::runCar(1.0);
	}
}

void HelloWorld::audio()
{
	if(pas==0)
	{
	CCSprite *onn=CCSprite::create((path1+"sound-on@2x.png").c_str());
	CCSprite *offf=CCSprite::create((path1+"sound-off@2x.png").c_str());
if(volu==1.0){
		volu=0.0;
		if(pCloseItem)
		{
		pCloseItem->setNormalImage(onn);
				pCloseItem->setSelectedImage(onn);
		}
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
	}
else
	{
		volu=1.0;
		if(SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()==false)
					{
						SimpleAudioEngine::sharedEngine()->playBackgroundMusic((path1+"backgroundmusic.wav").c_str(),true);
					}
		if(pCloseItem)
		{
		pCloseItem->setNormalImage(offf);
		pCloseItem->setSelectedImage(offf);
		}
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.7);
	}
	}
}
void HelloWorld::enteranme()
{
	//this->schedule(schedule_selector(HelloWorld::cht));
	scn=1;
	if(this->getChildByTag(9091))
	{
		this->removeChildByTag(9091);
	}
	if(this->getChildByTag(9093))
		{
			this->removeChildByTag(9093);
		}
	if(this->getChildByTag(9092))
		{
			this->removeChildByTag(9092);
		}
	if(this->getChildByTag(4879))
	{
		this->removeChildByTag(4879);
		this->removeChildByTag(4879);
	}
	this->removeChildByTag(8129);
	nale="";
	CCSize size=CCDirector::sharedDirector()->getWinSize();
SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
	CCSprite *sprite=CCSprite::create((path1+"enterback.png").c_str());
	sprite->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(sprite,17);
	CCLabelTTF *label=CCLabelTTF::create("Enter Name: ","Arial",35.0);


	label->setColor(ccc3(225,225,225));
	this->addChild(label,18);
	ga=CCTextFieldTTF::textFieldWithPlaceHolder("",CCSize(400,50),kCCTextAlignmentLeft,"Arial",35.0);

	ga->setColor(ccc3(225,225,225));
	ga->setTag(89632);
	ga->attachWithIME();
	this->addChild(ga,18);
	CCMenuItemImage *ok=CCMenuItemImage::create((path1+"ok.png").c_str(),(path1+"ok.png").c_str(),this,menu_selector(HelloWorld::mainentery));

	CCMenuItemImage *cancle=CCMenuItemImage::create((path1+"cancle.png").c_str(),(path1+"cancle.png").c_str(),this,menu_selector(HelloWorld::mainmenu));

	CCMenu *menu=CCMenu::create(ok,cancle,NULL);
	menu->setPosition(CCPointZero);
	if(path1=="z10/")
				{
			label->setPosition(ccp(size.width/2-label->getContentSize().width-125,size.height/2+170));
			ga->setPosition(ccp(size.width/2-20,size.height/2-10+170));
			ok->setPosition(ccp(900,450));
			cancle->setPosition(ccp(650,450));
				}
				else
				{
					label->setPosition(ccp(size.width/2-label->getContentSize().width,size.height/2+170));
					ga->setPosition(ccp(size.width/2+120,size.height/2-10+170));
								ok->setPosition(ccp(size.width/2-150,350));
								cancle->setPosition(ccp(size.width/2+150,350));
				}
	this->addChild(menu,18);
	ga->setString("");

}

void HelloWorld::cht()
{
	fprintf(stderr,"\nhaibhargav");
	if(this->getChildByTag(89632))
	{

	if(ga->getString()!=NULL)
	{
	string str=(string)(ga->getString());
	if(str.length()==10)
	{
		nale=(string)(ga->getString());
	}
	if(str.length()>10)
	{

		//str.push_back('\b');
		ga->setString(nale.c_str());

	}
	else
	{
		//ga->attachWithIME();
	}

	}
}}
void HelloWorld::hacked()
{
	fprintf(stderr,"shhhs");
	CCDirector::sharedDirector()->resume();
	this->schedule(schedule_selector(HelloWorld::cht));
}
void HelloWorld::mainmenu()
{

	if(this->getChildByTag(89632))
			{
			ga->detachWithIME();
			//this->unschedule(schedule_selector(HelloWorld::cht));
			}
	if(scn==1)
	{

		this->stopAllActions();
		this->removeAllChildren();
		this->unscheduleUpdate();
		this->unscheduleAllSelectors();
	//	this->schedule(schedule_selector(HelloWorld::cht));

		fprintf(stderr,"i hack u");
		HelloWorld::hacked();
		//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic((path1+"backgroundmusic.wav").c_str(),true);
	if(volu>0.0)
	{

		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7f);
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
	}

	if(hackvol==1)
	{

	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSprite *background=CCSprite::create((path1+"homescreen.png").c_str());
	background->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(background,-1);
	CCSprite *tra1=CCSprite::create((path1+"trans.png").c_str());
	tra1->setPosition(ccp(150,visibleSize.height-250));
	this->addChild(tra1,0);
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			(path1+"5.png").c_str(),
			(path1+"5.png").c_str(),
															this,
															menu_selector(HelloWorld::enteranme));

	CCSprite *tra2=CCSprite::create((path1+"trans.png").c_str());
	tra2->setPosition(ccp(150,visibleSize.height-350));
	this->addChild(tra2,0);
	CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
			(path1+"4.png").c_str(),
			(path1+"4.png").c_str(),
															this,
															menu_selector(HelloWorld::help));

	CCSprite *tra3=CCSprite::create((path1+"trans.png").c_str());
	tra3->setPosition(ccp(150,visibleSize.height-450));
	this->addChild(tra3,0);
	CCMenuItemImage *pCloseItem3 = CCMenuItemImage::create(
			(path1+"3.png").c_str(),
			(path1+"3.png").c_str(),
	               	                                        this,
	               	                                        menu_selector(HelloWorld::settingss));

	CCSprite *tra4=CCSprite::create((path1+"trans.png").c_str());
	tra4->setPosition(ccp(visibleSize.width-200,visibleSize.height-400));
	this->addChild(tra4,0);
	CCMenuItemImage *pCloseItem4 = CCMenuItemImage::create(
			(path1+"2.png").c_str(),
			(path1+"2.png").c_str(),
	                              	                        this,
	                              	                        menu_selector(HelloWorld::menuCloseCallback));

	CCMenuItemImage *pCloseItem5 = CCMenuItemImage::create(
			(path1+"6.png").c_str(),
			(path1+"6.png").c_str(),
	                              	                        this,
	                              	                        menu_selector(HelloWorld::creditcls));

	CCMenu* pMenu = CCMenu::create(pCloseItem,pCloseItem1,pCloseItem3,pCloseItem4,pCloseItem5, NULL);
	pMenu->setPosition(CCPointZero);
	pMenu->setTag(8129);
	this->addChild(pMenu, 1);
	if(path1=="z10/")
			{
		pCloseItem->setPosition(ccp(200,visibleSize.height-250));
		pCloseItem1->setPosition(ccp(200,visibleSize.height-400));
		pCloseItem3->setPosition(ccp(200,visibleSize.height-550));
		pCloseItem4->setPosition(ccp(visibleSize.width-150,visibleSize.height-400));
		pCloseItem5->setPosition(ccp(visibleSize.width/2,100));
			}
			else
			{
				pCloseItem->setPosition(ccp(100,visibleSize.height-250));
						pCloseItem1->setPosition(ccp(100,visibleSize.height-400));
						pCloseItem3->setPosition(ccp(100,visibleSize.height-550));
						pCloseItem4->setPosition(ccp(visibleSize.width-100,visibleSize.height-400));
						pCloseItem5->setPosition(ccp(visibleSize.width/2,100));
			}

	scn=0;
}
void HelloWorld::creditcls()
{
	if(this->getChildByTag(9091))
		{
			this->removeChildByTag(9091);
		}
		if(this->getChildByTag(9093))
			{
				this->removeChildByTag(9093);
			}
		if(this->getChildByTag(9092))
			{
				this->removeChildByTag(9092);
			}
		if(this->getChildByTag(4879))
		{

		}
		else
		{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *credit=CCSprite::create((path1+"creitsscreen1.png").c_str());
	credit->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(credit,400);
	credit->setTag(4879);
	CCMenuItemImage *cls=CCMenuItemImage::create((path1+"buycls2.png").c_str(),(path1+"buycls2").c_str(),this,menu_selector(HelloWorld::closecredit));
	if(path1=="z10/")
			{
		cls->setPosition(ccp(1150,710));
			}
			else
			{
				cls->setPosition(ccp(700,700));
			}

	CCMenu *cls1=CCMenu::create(cls,NULL);
	cls1->setPosition(CCPointZero);
	this->addChild(cls1,402);
	cls1->setTag(4879);
		}
}
void HelloWorld::closecredit()
{
	for(int i=1;i<=2;i++)
	{
		this->removeChildByTag(4879);
	}
}
void HelloWorld::help()
{
	if(this->getChildByTag(9092))
	{
		CCSprite *sp=dynamic_cast<CCSprite*>(this->getChildByTag(9092));
		sp->runAction(CCSequence::create(CCFadeOut::create(2.5),NULL));
		this->removeChild(sp);
	}
	if(this->getChildByTag(9093))
	{
		this->removeChildByTag(9093,true);
	}
	if(this->getChildByTag(4879))
		{
			this->removeChildByTag(4879);
			this->removeChildByTag(4879);
		}
	if(this->getChildByTag(9091))
	{

	}
	else
	{
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *sprite=CCSprite::create((path1+"help.png").c_str());
	sprite->setPosition(ccp(visibleSize.width/2+50,visibleSize.height/2));
	sprite->runAction(CCSequence::create(CCFadeIn::create(1.5),NULL));
	sprite->setTag(9091);
	this->addChild(sprite,10);
	}
}
void HelloWorld::settingss()
{
	if(this->getChildByTag(9091))
	{
		CCSprite *sp=dynamic_cast<CCSprite*>(this->getChildByTag(9091));
		sp->runAction(CCSequence::create(CCFadeOut::create(2.5),NULL));
		this->removeChild(sp);
	}
	if(this->getChildByTag(4879))
		{
			this->removeChildByTag(4879);
			this->removeChildByTag(4879);
		}
	if(this->getChildByTag(9092))
	{

	}
	else
	{
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *sprite=CCSprite::create((path1+"settings.png").c_str());
	sprite->setPosition(ccp(visibleSize.width/2+50,visibleSize.height/2));
	sprite->runAction(CCSequence::create(CCFadeIn::create(1.5),NULL));
	sprite->setTag(9092);
	CCMenuItemImage *on = CCMenuItemImage::create(
			(path1+"onnorm.png").c_str(),
			(path1+"onclick.png").c_str(),
				    	                                this,
				    	                                menu_selector(HelloWorld::volume));

	CCMenuItemImage *off = CCMenuItemImage::create(
			(path1+"offnorm.png").c_str(),
			(path1+"offclick.png").c_str(),
				    	                                this,
				    	                                menu_selector(HelloWorld::mute));

	if(path1=="z10/")
			{
		on->setPosition(ccp(650,300));
		off->setPosition(ccp(800,300));
			}
			else
			{
				on->setPosition(ccp(400,300));
						off->setPosition(ccp(500,300));
			}
	CCMenu *onoff = CCMenu::create(on,off, NULL);
	onoff->setPosition(CCPointZero);
	onoff->setTag(9093);
	this->addChild(onoff, 41);
	this->addChild(sprite,10);
	}
}
void HelloWorld::updatemeters(float dt)
{
	m4+=1;
	char str09[100];
	beatcnt++;
	std::string m="m";
	sprintf(str09,("%d "+m).c_str(),m4);
	pLabel1->setString(str09);
}
void HelloWorld::quitscene()
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCSprite *conf=CCSprite::create((path1+"arb.png").c_str());
	conf->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(conf,20000000);
	conf->setTag(63589);
	if(volu>0.0)
	{
		hackvol=1;
	}
	else
	{
		hackvol=0;
	}
	CCMenuItemImage *yes=CCMenuItemImage::create((path1+"ayes.png").c_str(),(path1+"ayes.png").c_str(),this,menu_selector(HelloWorld::mainmenu));

	CCMenuItemImage *no=CCMenuItemImage::create((path1+"ano.png").c_str(),(path1+"ano.png").c_str(),this,menu_selector(HelloWorld::reenter));

	if(path1=="z10/")
			{
		yes->setPosition(ccp(300,410));
		no->setPosition(ccp(1100,365));
			}
			else
			{
				yes->setPosition(ccp(200,410));
						no->setPosition(ccp(600,365));
			}
	CCMenu *menu=CCMenu::create(yes,no,NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu,20000002);
	menu->setTag(63589);
	scn=1;
}
void HelloWorld::reenter()
{
	while(this->getChildByTag(63589))
	{
		this->removeChildByTag(63589);
	}

}
void HelloWorld::applicationDidEnterBackground()
{
	if(this->getChildByTag(696))
	{
		this->removeChildByTag(696);
	}
	CCSprite *pau=CCSprite::create((path1+"pause.png").c_str());
	CCSprite *ply=CCSprite::create((path1+"play.png").c_str());
	CCMenuItemImage *hacv=CCMenuItemImage::create((path1+"quitbutton1.png").c_str(),(path1+"quitbutton.png").c_str(),this,menu_selector(HelloWorld::quitscene));
	if(path1=="z10/")
			{
		hacv->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-200,50));
			}
			else
			{
				hacv->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-120,50));
			}

	CCMenu *menuquit=CCMenu::create(hacv, NULL);
	menuquit->setPosition(CCPointZero);
	menuquit->setTag(6321);
	if(pas==0)
	{
		paus->setNormalImage(ply);
		paus->setSelectedImage(ply);
		this->addChild(menuquit,2);
		if(this->getChildByTag(6321))
		{
  			CCDirector::sharedDirector()->pause();
  			this->setTouchEnabled(false);
  			SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0);
  			SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0);
  			pas=1;
		}
	}
	else if(pas==1)
	{
		pas=0;
		paus->setNormalImage(pau);
		paus->setSelectedImage(pau);
		this->removeChildByTag(6321);

		CCDirector::sharedDirector()->resume();
		CCDirector::sharedDirector()->startAnimation();
		this->setTouchEnabled(true);
		if(volu==1.0)
		{
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);
		}

	}
}
void HelloWorld::start()
{
	this->unscheduleUpdate();
	this->unscheduleAllSelectors();
	this->schedule(schedule_selector(HelloWorld::cht));
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCSpriteFrameCache *cache1=CCSpriteFrameCache::sharedSpriteFrameCache();
	cache1->addSpriteFramesWithFile((path1+"countdwn.plist").c_str());
	CCSpriteBatchNode *spritesheet1=CCSpriteBatchNode::create((path1+"countdwn.png").c_str());
	spritesheet1->setTag(404);
	this->addChild(spritesheet1);
	CCSprite *sprite1=CCSprite::createWithSpriteFrameName("1.png");
	sprite1->setPosition(ccp(size.width/2,size.height/2));
	CCArray *animFrames1=CCArray::createWithCapacity(4);
	char str1[100]={0};
	for(int k=1;k<=4;k++)
	{
		sprintf(str1,("%d.png"),k);
	    CCSpriteFrame *frame1=cache1->spriteFrameByName(str1);
	    animFrames1->addObject(frame1);
	}
	sprite1->setTag(303);
	CCAnimation *animation1=CCAnimation::createWithSpriteFrames(animFrames1,0.3f);
	sprite1->runAction(CCSequence::create(
	CCRepeat::create(CCAnimate::create(animation1),1),
	CCFadeOut::create(1.0),
	CCCallFuncN::create(this,callfuncN_selector(HelloWorld::resanim)),NULL));
	spritesheet1->addChild(sprite1,1);
}
void HelloWorld::resanim()
{
	this->scheduleUpdate();
	HelloWorld::callpower(30.0);
	this->schedule(schedule_selector(HelloWorld::bringRain),4.0);
	this->schedule(schedule_selector(HelloWorld::runCar),6.0);
	this->schedule(schedule_selector(HelloWorld::addCoins),20.0);
	this->schedule(schedule_selector(HelloWorld::coinSequence),15.0);
	this->schedule(schedule_selector(HelloWorld::updatemeters),0.10);
	this->schedule(schedule_selector(HelloWorld::tick));
	this->schedule(schedule_selector(HelloWorld::checksys),1.0);
	this->schedule(schedule_selector(HelloWorld::popup),200.0);
	this->schedule(schedule_selector(HelloWorld::diamond),23.0);

	this->setTouchEnabled(true);
}
void HelloWorld::callpower(float dt)
{
	if(strr2=="boy")
	{
	this->schedule(schedule_selector(HelloWorld::powerpack1),dt);
	}

}
void HelloWorld::popup(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *run;

		run=CCSprite::create((path1+"run.png").c_str());
		if(path1=="z10/")
				{
			run->setPosition(ccp(850,size.height-150));
				}
				else
				{
					run->setPosition(ccp(400,size.height-80));
				}

		this->addChild(run,69);
		run->runAction(CCSequence::create(CCFadeIn::create(1.0),CCFadeOut::create(3.0),NULL));


}
void HelloWorld::scoreall()
{
	for(int i=1;i<=5;i++)
	{
		this->removeChildByTag(48923);
	}


			if(this->getChildByTag(101))
				{
					dynamic_cast<CCSprite*>(this->getChildByTag(101))->setVisible(false);
				}
			pLabel1->setVisible(false);
				pLabel2->setVisible(false);
				pLabel4->setVisible(false);
				coinimg->setVisible(false);
				jem->setVisible(false);
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	int rc7=	sqlite3_open_v2("data/database.db",&m_db,SQLITE_OPEN_READONLY,NULL);
	if(rc7==SQLITE_OK)
	{
		fprintf(stderr,"\ndatabase is opened succesfully");
	}
	static const char* selectSql = "SELECT * FROM store order by score DESC limit 5";
	sqlite3_stmt* selectStmt;
	int rc10 = sqlite3_prepare_v2(m_db, selectSql, strlen(selectSql), &selectStmt, NULL);
	if (rc10 == SQLITE_OK)
	{
		fprintf(stderr, "Sqlite select %d\n", rc);
	}
	rc10 = sqlite3_step(selectStmt);
	CCSprite *bah=CCSprite::create((path1+"enterback2.png").c_str());
	bah->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(bah,100000000);
	bah->setTag(9877);
	if(path1=="z10/")
			{
		CCLabelTTF *score=CCLabelTTF::create("  Rank     NAME                       SCORE  COINS ","Arial",45.0);
			score->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2-100+50,CCDirector::sharedDirector()->getWinSize().height-300));
			this->addChild(score,100000001);
			score->setTag(9877);
			CCLabelTTF *ansscore,*ansscore1,*ansscore2,*ansscore3;
			char ar1[100],ar2[100],ar3[100],ar4[100];
			int i=1;
			while (rc10 == SQLITE_ROW)
			{
				sprintf(ar1,"%d",i);
				sprintf(ar2,"%s",(const char *)sqlite3_column_text(selectStmt,0));
				sprintf(ar3,"%d",sqlite3_column_int(selectStmt, 1));
				sprintf(ar4,"%d",sqlite3_column_int(selectStmt, 2));
				ansscore=CCLabelTTF::create("","Arial",35.0);
				ansscore->setString(ar1);
				ansscore->setPosition(ccp(150,(CCDirector::sharedDirector()->getWinSize().height-300)-(i*60)));
				ansscore->setTag(9877);
				this->addChild(ansscore,100000001);
				ansscore1=CCLabelTTF::create("","Arial",35.0,CCSize(500,50),kCCTextAlignmentLeft);
				ansscore1->setString(ar2);
				ansscore1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2-90,(CCDirector::sharedDirector()->getWinSize().height-300)-(i*60)));
				ansscore1->setTag(9877);
				this->addChild(ansscore1,100000001);
				ansscore2=CCLabelTTF::create("","Arial",35.0);
				ansscore2->setString(ar3);
				ansscore2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+220,(CCDirector::sharedDirector()->getWinSize().height-300)-(i*60)));
				ansscore2->setTag(9877);
				this->addChild(ansscore2,100000001);
				ansscore3=CCLabelTTF::create("","Arial",35.0);
				ansscore3->setString(ar4);
				ansscore3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+400,(CCDirector::sharedDirector()->getWinSize().height-300)-(i*60)));
				ansscore3->setTag(9877);
				this->addChild(ansscore3,100000001);
				fprintf(stderr,"\t%d\n",(sqlite3_column_int(selectStmt, 1)));
				const unsigned char *st=sqlite3_column_text(selectStmt,0);
				if((const char*)st==name123)
				{
					newentry=0;
				}
				i++;
				rc10 = sqlite3_step(selectStmt);
			}
			sqlite3_finalize(selectStmt);
			sqlite3_close_v2(m_db);
			CCMenuItemImage *close=CCMenuItemImage::create((path1+"close.png").c_str(),(path1+"close.png").c_str(),this,menu_selector(HelloWorld::clo));
			close->setPosition(ccp(size.width/2,100));
			CCMenu *clsmenu=CCMenu::create(close,NULL);
				clsmenu->setPosition(CCPointZero);
				clsmenu->setTag(9877);
				this->addChild(clsmenu,100000001);
			}
			else
			{
				CCLabelTTF *score=CCLabelTTF::create("    Rank    NAME        SCORE    COINS ","Arial",35.0);
					score->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2-100+50,CCDirector::sharedDirector()->getWinSize().height-200));
					this->addChild(score,100000001);
					score->setTag(9877);
					CCLabelTTF *ansscore,*ansscore1,*ansscore2,*ansscore3;
					char ar1[100],ar2[100],ar3[100],ar4[100];
					int i=1;
					while (rc10 == SQLITE_ROW)
					{
						sprintf(ar1,"%d",i);
						sprintf(ar2,"%s",(const char *)sqlite3_column_text(selectStmt,0));
						sprintf(ar3,"%d",sqlite3_column_int(selectStmt, 1));
						sprintf(ar4,"%d",sqlite3_column_int(selectStmt, 2));
						ansscore=CCLabelTTF::create("","Arial",30.0);
						ansscore->setString(ar1);
						ansscore->setPosition(ccp(50,(CCDirector::sharedDirector()->getWinSize().height-200)-(i*60)));
						ansscore->setTag(9877);
						this->addChild(ansscore,100000001);
						ansscore1=CCLabelTTF::create("","Arial",30.0,CCSize(250,50),kCCTextAlignmentLeft);
						ansscore1->setString(ar2);
						ansscore1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2-65,(CCDirector::sharedDirector()->getWinSize().height-200)-(i*60)));
						ansscore1->setTag(9877);
						this->addChild(ansscore1,100000001);
						ansscore2=CCLabelTTF::create("","Arial",30.0);
						ansscore2->setString(ar3);
						ansscore2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+55,(CCDirector::sharedDirector()->getWinSize().height-200)-(i*60)));
						ansscore2->setTag(9877);
						this->addChild(ansscore2,100000001);
						ansscore3=CCLabelTTF::create("","Arial",30.0);
						ansscore3->setString(ar4);
						ansscore3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+250,(CCDirector::sharedDirector()->getWinSize().height-200)-(i*60)));
						ansscore3->setTag(9877);
						this->addChild(ansscore3,100000001);
						fprintf(stderr,"\t%d\n",(sqlite3_column_int(selectStmt, 1)));
						const unsigned char *st=sqlite3_column_text(selectStmt,0);
						if((const char*)st==name123)
						{
							newentry=0;
						}
						i++;
						rc10 = sqlite3_step(selectStmt);
					}
					sqlite3_finalize(selectStmt);
					sqlite3_close_v2(m_db);
					CCMenuItemImage *close=CCMenuItemImage::create((path1+"close.png").c_str(),(path1+"close.png").c_str(),this,menu_selector(HelloWorld::clo));
					close->setPosition(ccp(size.width/2,100));
					CCMenu *clsmenu=CCMenu::create(close,NULL);
						clsmenu->setPosition(CCPointZero);
						clsmenu->setTag(9877);
						this->addChild(clsmenu,100000001);

			}


}
void HelloWorld::clo()
{
	for(int i=1;i<=23;i++)
	{
		this->removeChildByTag(9877);
	}
	HelloWorld::scoredisplay();
}
void HelloWorld::checksys(float dt)
{
	if(j==1)
	{
		b2Vec2 v=_body->GetLinearVelocity();
		if(v.y==0.0f)
		{
			runcnt=0;
			if(k==0)
			{
				if(strr2!="bboyf ")
				{
					HelloWorld::runman(manstate);
				}
			}
		}
		else
		{
			runcnt+=0.5;
		}
	}
	if(coincount>=1000)
		{
			if(coincount%1000==0)
			{
				jemscount+=3;
			}
		}
}
void HelloWorld::tick(float dt)
{
	CCSize size1 = CCDirector::sharedDirector()->getWinSize();

	if(sprite)
	{
		by=sprite->getPosition().y;
		bx=sprite->getPosition().x;
	}
	if(m4>=500)
	{
		if(m4%500==0)
		{
			CCSprite *scr=CCSprite::create((path1+"score.png").c_str());
			scr->setPosition(ccp(size1.width/2,size1.height-150));
			this->addChild(scr,166);
			scr->runAction(CCSequence::create(CCFadeIn::create(0.1),CCFadeOut::create(1.0),CCCallFuncN::create(this,callfuncN_selector(HelloWorld::movedtoend)),NULL));
			CCLabelTTF *scrlabel=CCLabelTTF::create("", "Arial",45.0f);
			scrlabel->setPosition(ccp(size1.width/2+70,size1.height-160));
			this->addChild(scrlabel,170);
			scrlabel->setTag(15642);
			char ap[1000];
			sprintf(ap,"%d m",m4);
			scrlabel->setString(ap);
			scrlabel->setColor(ccc3(0,0,0));
		}
	}
	if(coincount>=800)
	{
		if(coincount%800==0)
		{
CCSprite *collect=CCSprite::create((path1+"collect.png").c_str());
if(path1=="z10/")
		{
	collect->setPosition(ccp(800,size1.height-100));
		}
		else
		{
			collect->setPosition(ccp(400,size1.height-70));
		}

				this->addChild(collect,69);
				collect->runAction(CCSequence::create(CCFadeIn::create(1.0),CCFadeOut::create(3.0),NULL));
				//collc=1;
		}
	}

	_world->Step(dt, 10, 10);
	for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite *ballData = (CCSprite *)b->GetUserData();
	   	    ballData->setPosition(ccp(b->GetPosition().x * PTM_RATIO,b->GetPosition().y * PTM_RATIO));
	   	    if(ballData->getTag()==3)
	   	    {
	   	    	ballData->setPosition(ccp((b->GetPosition().x+60.0f),b->GetPosition().y));
	   	    }
		}
    }
	if(j==1)
	{
		b2Vec2 v=_body->GetLinearVelocity();
		if(v.y==0.0f)
		{
			runcnt=0;
			if(k==0)
			{
				if(strr2!="bboyf ")
				{
					HelloWorld::runman(manstate);
				}
			}
		}
	}
	if(runcnt==1500.0)
	{
		jemscount+=10;
		runcnt=0.0f;
	}
	CCSprite *bspr;
	CCObject* it = NULL;
	CCObject* jt = NULL;
	CCObject* kt = NULL;
	CCObject* lt = NULL;
	CCRect rec2;
	if(this->getChildByTag(31)||this->getChildByTag(32))
	{
		if(j==0&&k==1)
		{
			bspr=dynamic_cast<CCSprite*>(this->getChildByTag(31)->getChildByTag(101));
			rec2=CCRectMake(
							bspr->getPosition().x - (bspr->getContentSize().width/2),
			 				bspr->getPosition().y - (bspr->getContentSize().height/2),
			 				bspr->getContentSize().width,
			 				bspr->getContentSize().height);
		}
		else if(j==1&&k==0)
		{
			bspr=dynamic_cast<CCSprite*>(this->getChildByTag(32)->getChildByTag(101));
			rec2=CCRectMake(
							bspr->getPosition().x - (bspr->getContentSize().width/2),
							bspr->getPosition().y - (bspr->getContentSize().height/2),
							bspr->getContentSize().width,
							bspr->getContentSize().height);
		}
	}
	if(this->_coins->count()!=0)
	{
		CCARRAY_FOREACH(_coins, it)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(it);
			CCRect rec1 = CCRectMake(
							target->getPosition().x - (target->getContentSize().width/2),
							target->getPosition().y - (target->getContentSize().height/2),
							target->getContentSize().width-10,
							target->getContentSize().height-10);
			if (rec2.intersectsRect(rec1))
			{
				target->setVisible(false);
				if(volu!=0.0)
				{
			    SimpleAudioEngine::sharedEngine()->playEffect((path1+"coin.wav").c_str(),false);
			    SimpleAudioEngine::sharedEngine()->setEffectsVolume(volu);
				}

			    this->removeChild(target,true);
			    _coins->removeObject(target,true);
			    coincount++;
			    char str09[100];
			    std::string m="";
			    sprintf(str09,(" %d"),coincount);
			    pLabel2->setString(str09);
			}
		}
	}
	if(_powers->count()!=0)
	{
		CCARRAY_FOREACH(_powers, jt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(jt);
			CCRect rec1 = CCRectMake(
			target->getPosition().x - (target->getContentSize().width/2),
			target->getPosition().y - (target->getContentSize().height/2),
			target->getContentSize().width-10,
			target->getContentSize().height-10);
			if (rec2.intersectsRect(rec1))
			{
				flyx=bspr->getPosition().x;
				flyy=target->getPosition().y;
				target->setVisible(false);
				if(target->getTag()==5)
				{
					if(volu!=0.0)
					{
					SimpleAudioEngine::sharedEngine()->playEffect((path1+"powerup.wav").c_str(),false);
					SimpleAudioEngine::sharedEngine()->setEffectsVolume(volu);
					}
					strr2="rboyf ";
					manstate="rboy ";
					HelloWorld::flysprite();
					HelloWorld::partic1();
					bgspeed=ccp(0.7,0.7);
					fastness=5.0;
				}
				if(target->getTag()==55)
				{
					if(volu!=0.0)
					{
					SimpleAudioEngine::sharedEngine()->playEffect((path1+"powerup.wav").c_str(),false);
					SimpleAudioEngine::sharedEngine()->setEffectsVolume(volu);
					}
					strr2="gboyf ";
					manstate="gboy ";
					HelloWorld::flysprite();
					HelloWorld::partic1();
					bgspeed=ccp(0.7,0.7);
					fastness=5.0;
				}
				if(target->getTag()==555)
				{
					if(volu!=0.0)
					{
					SimpleAudioEngine::sharedEngine()->playEffect((path1+"diamond.wav").c_str(),false);
					SimpleAudioEngine::sharedEngine()->setEffectsVolume(volu);
					}
					jemscount+=1;
				}
				if(target->getTag()==5555)
				{
					if(volu!=0.0)
					{
					SimpleAudioEngine::sharedEngine()->playEffect((path1+"powerup.wav").c_str(),false);
					SimpleAudioEngine::sharedEngine()->setEffectsVolume(volu);
					}
					strr2="bboyf ";
					manstate="bboy ";
					HelloWorld::flysprite();
					HelloWorld::partic1();
					bgspeed=ccp(0.7,0.7);
					fastness=5.0;
				}
				this->removeChild(target,true);
				_powers->removeObject(target,true);
				this->unschedule(schedule_selector(HelloWorld::powerpack1));
			}
		}
	}
	if(_targets->count()!=0)
	{
		CCARRAY_FOREACH(_targets, kt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(kt);
			CCRect rec1 = CCRectMake(
									target->getPosition().x - (target->getContentSize().width/2),
									target->getPosition().y - (target->getContentSize().height/2),
									target->getContentSize().width-10,
									target->getContentSize().height-10);
			if (rec2.intersectsRect(rec1))
			{
				beatcnt=0;

				HelloWorld::callpower(4.0);
				target->setVisible(false);
				this->removeChild(target,true);
				_targets->removeObject(target,true);

				CCSprite* impact=CCSprite::create((path1+"impact.png").c_str());
				impact->setPosition(ccp(640,384));
				this->addChild(impact,555);
				impact->setTag(696);
				impact->runAction(CCSequence::create(
										CCFadeIn::create(0.1),CCFadeOut::create(0.1),
										CCCallFuncN::create(this,callfuncN_selector(HelloWorld::resat)),NULL));
				if(strr2!="boy")
				{
				this->schedule(schedule_selector(HelloWorld::powerpack1),6.0);
				if(volu!=0.0)
				{
					SimpleAudioEngine::sharedEngine()->playEffect((path1+"PowerDown.wav").c_str(),false);
				}

					fastness=3.0;
					HelloWorld::runman("boy ");
				}
				else
				{
					bspr->runAction(CCSequence::create(
							CCFadeOut::create(0.3),CCFadeIn::create(0.3),
						 	CCFadeOut::create(0.3),CCFadeIn::create(0.3),
						 	CCFadeOut::create(0.3),CCFadeIn::create(0.3),
						 	CCCallFuncN::create(this,callfuncN_selector(HelloWorld::makeman)),NULL));
					lives--;
					char str09[100];
					sprintf(str09,(" %d"),lives);
					pLabel3->setString(str09);
				}
			}
		}
	}
	if(_cars->count()!=0)
	{
		CCARRAY_FOREACH(_cars, lt)
		{
			CCSprite *target = dynamic_cast<CCSprite*>(lt);
			CCRect rec1 = CCRectMake(
								 target->getPosition().x - (target->getContentSize().width/2),
								 target->getPosition().y - (target->getContentSize().height/3),
								 target->getContentSize().width-60,
								 target->getContentSize().height-50);
			if (rec2.intersectsRect(rec1))
			{
				target->setVisible(false);
				CCPoint loc=target->getPosition();
				_cars->removeObject(target,true);
				this->removeChild(target,true);
				if(strr2!="boy")
				{
					if(volu!=0.0)
					{
					SimpleAudioEngine::sharedEngine()->playEffect((path1+"Explosion.wav").c_str());
					}
					CCSprite *destroy=CCSprite::create((path1+"11.png").c_str());
					destroy->setPosition(loc);
					destroy->runAction(CCSequence::create(CCFadeIn::create(0.2),CCFadeOut::create(1.3),NULL));
					this->addChild(destroy,10);
				}
				else
				{
					bspr->runAction(CCSequence::create(
											CCFadeOut::create(0.3),CCFadeIn::create(0.3),
										    CCFadeOut::create(0.3),CCFadeIn::create(0.3),
										    CCFadeOut::create(0.3),CCFadeIn::create(0.3),
										    CCCallFuncN::create(this,callfuncN_selector(HelloWorld::makeman)),NULL));
					lives--;
					char str09[100];
					sprintf(str09,(" %d"),lives);
					pLabel3->setString(str09);
				}

			}
		}
	}
	char str89[100];
	if(jemscount>=0)
	{
		sprintf(str89,(" %d"),jemscount);
		pLabel4->setString(str89);
		char str09[100];
		sprintf(str09,(" %d"),lives);
		pLabel3->setString(str09);
	}
////////////////////////////////////////////////////////////////////////////
	if(beatcnt>100)
	{
		HelloWorld::callpower(25);
	}
		///////////////////////game over///////////////////////////
	if(lives>1)
	{
		venstat=0;
	}
	if(lives==1)
	{
		if(jemscount>=7)
		{
			if(venstat==0)
			{
				HelloWorld::buylife();
			}
		}
	}
	if(lives<=0)
	{
		if(jemscount<7)
		{
			this->unscheduleUpdate();
			this->unscheduleAllSelectors();

			this->stopAllActions();
			_gameover=CCSprite::create((path1+"gameover.png").c_str());
			_gameover->setPosition(ccp(size1.width/2,size1.height/2));
			this->addChild(_gameover,42);
			_gameover->runAction(CCSequence::create(CCFadeOut::create(2.0),
			CCCallFuncN::create(this,callfuncN_selector(HelloWorld::scoredisplay)),NULL));
		}
		else if(jemscount>=7)
		{
			if(kalam==0)
			{
				this->unscheduleUpdate();
				this->unscheduleAllSelectors();
			//	this->stopAllActions();
				HelloWorld::buylife2();
			}
		}
	}
}
void HelloWorld::resat()
{
	if(getChildByTag(696))
	{
		this->removeChildByTag(696);
	}
}
void HelloWorld::scoredisplay()
{
	HelloWorld::getscore();
	this->setTouchEnabled(false);


	if(this->getChildByTag(101))
	{
		dynamic_cast<CCSprite*>(this->getChildByTag(101))->setVisible(false);
	}
	this->removeChildByTag(80234);
				this->removeChildByTag(303);
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	if(kalam==2)
	{
		this->unscheduleUpdate();
		this->unscheduleAllSelectors();
		this->stopAllActions();
		_gameover=CCSprite::create((path1+"gameover.png").c_str());
		_gameover->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(_gameover,42);
		_gameover->runAction(CCSequence::create(CCFadeOut::create(15.0),NULL));
	}
	CCSprite *score=CCSprite::create((path1+"scoreboard.png").c_str());
	score->setTag(48923);
	score->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(score,43);
	pLabel1->setVisible(false);
	pLabel2->setVisible(false);
	pLabel4->setVisible(false);
	coinimg->setVisible(false);
	jem->setVisible(false);
	score->runAction(CCFadeIn::create(0.5));
	if(path1=="z10/")
			{
		char met[1000];
			sprintf(met,"%d",m4);
			CCLabelTTF *meters = CCLabelTTF::create(met, "Arial",35.0f);
			meters->setPosition(ccp(690,size.height-213));
			meters->setTag(48923);
			meters->setAnchorPoint(ccp(0.5,0.5));
			this->addChild(meters,44);
			char coinss[1000];
			sprintf(coinss,"%d",coincount);
			CCLabelTTF *coinst = CCLabelTTF::create(coinss, "Arial",35.0f);
			coinst->setPosition(ccp(690,size.height-276));
			coinst->setTag(48923);
			coinst->setAnchorPoint(ccp(0.5,0.5));
			this->addChild(coinst,44);
			char gems[1000];
			sprintf(gems,"%d",jemscount);
			CCLabelTTF *gemst = CCLabelTTF::create(gems, "Arial",35.0f);
			gemst->setPosition(ccp(690,size.height-339));
			gemst->setAnchorPoint(ccp(0.5,0.5));
			gemst->setTag(48923);
			this->addChild(gemst,44);
			CCMenuItemImage *playagain = CCMenuItemImage::create(
					(path1+"palyagain.png").c_str(),
					(path1+"palyagain.png").c_str(),
				    	                                        this,
				    	                                        menu_selector(HelloWorld::mainScene));
			playagain->setPosition(ccp(400,270));
			CCMenuItemImage *mainmenu = CCMenuItemImage::create(
					(path1+"mainmenu.png").c_str(),
					(path1+"mainmenu.png").c_str(),
					    	                                        this,
					    	                                        menu_selector(HelloWorld::mainmenu));
			mainmenu->setPosition(ccp(900,270));
			CCMenuItemImage *viewall = CCMenuItemImage::create(
					(path1+"viewall.png").c_str(),
					(path1+"viewall.png").c_str(),
						    	                                        this,
						    	                                        menu_selector(HelloWorld::scoreall));
			viewall->setPosition(ccp(650,100));
			CCMenu *scoreloop = CCMenu::create(playagain,mainmenu,viewall, NULL);
				scoreloop->setPosition(CCPointZero);
				scoreloop->setTag(48923);
				this->addChild(scoreloop, 44);

			}
			else
			{
				char met[1000];
					sprintf(met,"%d",m4);
					CCLabelTTF *meters = CCLabelTTF::create(met, "Arial",35.0f);
					meters->setPosition(ccp(size.width/2+50,size.height-183));
					meters->setTag(48923);
					meters->setAnchorPoint(ccp(0.5,0.5));
					this->addChild(meters,44);
					char coinss[1000];
					sprintf(coinss,"%d",coincount);
					CCLabelTTF *coinst = CCLabelTTF::create(coinss, "Arial",35.0f);
					coinst->setPosition(ccp(size.width/2+50,size.height-246));
					coinst->setTag(48923);
					coinst->setAnchorPoint(ccp(0.5,0.5));
					this->addChild(coinst,44);
					char gems[1000];
					sprintf(gems,"%d",jemscount);
					CCLabelTTF *gemst = CCLabelTTF::create(gems, "Arial",35.0f);
					gemst->setPosition(ccp(size.width/2+50,size.height-309));
					gemst->setAnchorPoint(ccp(0.5,0.5));
					gemst->setTag(48923);
					this->addChild(gemst,44);
					CCMenuItemImage *playagain = CCMenuItemImage::create(
							(path1+"palyagain.png").c_str(),
									(path1+"palyagain.png").c_str(),
						    	                                        this,
						    	                                        menu_selector(HelloWorld::mainScene));
					playagain->setPosition(ccp(200,270));
					CCMenuItemImage *mainmenu = CCMenuItemImage::create(
							(path1+"mainmenu.png").c_str(),
							(path1+"mainmenu.png").c_str(),
							    	                                        this,
							    	                                        menu_selector(HelloWorld::mainmenu));
					mainmenu->setPosition(ccp(550,270));
					CCMenuItemImage *viewall = CCMenuItemImage::create(
							(path1+"viewall.png").c_str(),
							(path1+"viewall.png").c_str(),
								    	                                        this,
								    	                                        menu_selector(HelloWorld::scoreall));
					viewall->setPosition(ccp(size.width/2,100));
					CCMenu *scoreloop = CCMenu::create(playagain,mainmenu,viewall, NULL);
						scoreloop->setPosition(CCPointZero);
						scoreloop->setTag(48923);
						this->addChild(scoreloop, 44);

			}


	scn=1;
}
void HelloWorld::buylife()
{
	this->removeChildByTag(80234);
						this->removeChildByTag(303);
//	if(lives==0)
//	{
//		venstat=0;
//		kalam=1;
//		if(this->getChildByTag(696))
//				{
//					this->removeChildByTag(696);
//				}
//
//			CCSize size=CCDirector::sharedDirector()->getWinSize();
//		CCDirector::sharedDirector()->stopAnimation();
//		CCDirector::sharedDirector()->pause();
//
//		buy=CCSprite::create("buy1.png");
//		buy->setPosition(ccp(size.width/2,size.height/2));
//		this->addChild(buy,40);
//		CCMenuItemImage *usejems = CCMenuItemImage::create(
//			    	                                        "buyuse.png",
//			    	                                        "buyuse2.png",
//			    	                                        this,
//			    	                                        menu_selector(HelloWorld::decjems));
//		usejems->setPosition(ccp(850,200));
//		CCMenuItemImage *buyclose = CCMenuItemImage::create(
//			    	                                        "buycls.png",
//			    	                                        "buycls2.png",
//			    	                                        this,
//			    	                                        menu_selector(HelloWorld::scoredisplay));
//		buyclose->setPosition(ccp(920,600));
//		buymenu = CCMenu::create(usejems,buyclose, NULL);
//		buymenu->setPosition(CCPointZero);
//			    	    this->addChild(buymenu, 41);
//	}
	venstat=1;
	if(this->getChildByTag(696))
			{
				this->removeChildByTag(696);
			}
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->pause();
	buy=CCSprite::create((path1+"buy1.png").c_str());
	buy->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(buy,40);
	CCMenuItemImage *usejems = CCMenuItemImage::create(
			(path1+"buyuse.png").c_str(),
			(path1+"buyuse2.png").c_str(),
	    	                                        this,
	    	                                        menu_selector(HelloWorld::decjems));

	CCMenuItemImage *buyclose = CCMenuItemImage::create(
			(path1+"buycls.png").c_str(),
			(path1+"buycls2.png").c_str(),
	    	                                        this,
	    	                                        menu_selector(HelloWorld::closeselect));
	if(path1=="z10/")
				{
			usejems->setPosition(ccp(850,200));
			buyclose->setPosition(ccp(920,600));
				}
				else
				{
					usejems->setPosition(ccp(480,213));
							buyclose->setPosition(ccp(650,600));
				}
	buymenu = CCMenu::create(usejems,buyclose, NULL);
	buymenu->setPosition(CCPointZero);
	this->addChild(buymenu, 41);
}
void HelloWorld::buylife2()
{
	venstat=0;
	kalam=1;
	this->removeChildByTag(80234);
						this->removeChildByTag(303);
	if(this->getChildByTag(696))
			{
				this->removeChildByTag(696);
			}

	CCSize size=CCDirector::sharedDirector()->getWinSize();
	CCDirector::sharedDirector()->stopAnimation();
	CCDirector::sharedDirector()->pause();

	buy=CCSprite::create((path1+"buy2.png").c_str());
	buy->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(buy,40);
	CCMenuItemImage *usejems = CCMenuItemImage::create(
			(path1+"buyuse.png").c_str(),
			(path1+"buyuse2.png").c_str(),
			    	                                        this,
			    	                                        menu_selector(HelloWorld::decjems));

	CCMenuItemImage *buyclose = CCMenuItemImage::create(
			(path1+"buycls.png").c_str(),
			(path1+"buycls2.png").c_str(),
			    	                                        this,
			    	                                        menu_selector(HelloWorld::closeselect));
	if(path1=="z10/")
				{
			usejems->setPosition(ccp(850,200));
			buyclose->setPosition(ccp(920,600));
				}
				else
				{
					usejems->setPosition(ccp(480,213));
							buyclose->setPosition(ccp(650,600));
				}
	buymenu = CCMenu::create(usejems,buyclose, NULL);
	buymenu->setPosition(CCPointZero);
	this->addChild(buymenu, 41);
	//this->removeChildByTag(80234);
}
void HelloWorld::closeselect()
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	if(lives<=0)
	{
		kalam=2;
		CCDirector::sharedDirector()->resume();
		CCDirector::sharedDirector()->startAnimation();
		HelloWorld::scoredisplay();
	}
	else
	{
	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->startAnimation();

	buy->runAction(CCSequence::create(CCFadeOut::create(0.5),NULL));
	this->removeChild(buy);
	this->removeChild(buymenu);
	if(volu==1.0)
				{
		    pCloseItem = CCMenuItemImage::create(
		    		(path1+"sound-off@2x.png").c_str(),
		    		(path1+"sound-off@2x.png").c_str(),
				                                    this,
				                                    menu_selector(HelloWorld::audio));
				}
				if(volu==0.0)
				{
				    pCloseItem = CCMenuItemImage::create(
				    		(path1+"sound-on@2x.png").c_str(),
				    		(path1+"sound-on@2x.png").c_str(),
						                                    this,
						                                    menu_selector(HelloWorld::audio));

				}

			paus = CCMenuItemImage::create(
					(path1+"pause.png").c_str(),
					(path1+"pause.png").c_str(),
				                                    this,
				                                    menu_selector(HelloWorld::applicationDidEnterBackground));



			if(path1=="z10/")
					{
				pCloseItem->setPosition(ccp(size.width - 32, size.height-35));
							paus->setPosition(ccp(size.width-70,60));
					}
					else
					{
						pCloseItem->setPosition(ccp(size.width - 25, size.height-25));
								paus->setPosition(ccp(size.width-38,50));
					}

			pMenu = CCMenu::create(pCloseItem,NULL);
			pMenu->setTag(303);
			plauy=CCMenu::create(paus,NULL);
			//paus->setTag(1245698);
			plauy->setPosition(CCPointZero);
			this->addChild(plauy,1);
			plauy->setTag(80234);
			pMenu->setPosition(CCPointZero);
			this->addChild(pMenu, 1);
	}


}
void HelloWorld::decjems()
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	if(lives==0)
	{
//		paus = CCMenuItemImage::create(
//									"pause.png",
//									"play.png",
//									this,
//									menu_selector(HelloWorld::applicationDidEnterBackground));
//		paus->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-100,50));
//		CCMenu *plauy=CCMenu::create(paus,NULL);
//		plauy->setPosition(CCPointZero);
//		this->addChild(plauy,1);
//		plauy->setTag(80234);
		CCDirector::sharedDirector()->resume();
						CCDirector::sharedDirector()->startAnimation();


				if(jemscount>=7)
				{
				jemscount-=7;
				}
				lives=5;


		this->scheduleUpdate();
							HelloWorld::resanim();
		buy->runAction(CCSequence::create(CCFadeOut::create(0.5),NULL));
		this->removeChild(buy);
		this->removeChild(buymenu);
		if(volu==1.0)
							{
					    pCloseItem = CCMenuItemImage::create(
					    		(path1+"sound-off@2x.png").c_str(),
					    		(path1+"sound-off@2x.png").c_str(),
							                                    this,
							                                    menu_selector(HelloWorld::audio));
							}
							if(volu==0.0)
							{
							    pCloseItem = CCMenuItemImage::create(
							    		(path1+"sound-on@2x.png").c_str(),
							    		(path1+"sound-on@2x.png").c_str(),
									                                    this,
									                                    menu_selector(HelloWorld::audio));

							}

						paus = CCMenuItemImage::create(
								(path1+"pause.png").c_str(),
								(path1+"pause.png").c_str(),
							                                    this,
							                                    menu_selector(HelloWorld::applicationDidEnterBackground));



						if(path1=="z10/")
											{
										pCloseItem->setPosition(ccp(size.width - 32, size.height-35));
													paus->setPosition(ccp(size.width-70,60));
											}
											else
											{
												pCloseItem->setPosition(ccp(size.width - 25, size.height-25));
														paus->setPosition(ccp(size.width-38,50));
											}
						pMenu = CCMenu::create(pCloseItem,NULL);
						pMenu->setTag(303);
						plauy=CCMenu::create(paus,NULL);
						//paus->setTag(1245698);
						plauy->setPosition(CCPointZero);
						this->addChild(plauy,1);
						plauy->setTag(80234);
						pMenu->setPosition(CCPointZero);
						this->addChild(pMenu, 1);

//		this->addChild(plauy,1);
//		this->addChild(pMenu, 1);
	}
	else
	{

	CCDirector::sharedDirector()->resume();
	CCDirector::sharedDirector()->startAnimation();
	this->scheduleUpdate();
								HelloWorld::resanim();
	jemscount-=7;
	lives=5;
	buy->runAction(CCSequence::create(CCFadeOut::create(0.5),NULL));
	this->removeChild(buy);
	this->removeChild(buymenu);
	if(volu==1.0)
					{
			    pCloseItem = CCMenuItemImage::create(
			    		(path1+"sound-off@2x.png").c_str(),
			    		(path1+"sound-off@2x.png").c_str(),
					                                    this,
					                                    menu_selector(HelloWorld::audio));
					}
					if(volu==0.0)
					{
					    pCloseItem = CCMenuItemImage::create(
					    		(path1+"sound-on@2x.png").c_str(),
					    		(path1+"sound-on@2x.png").c_str(),
							                                    this,
							                                    menu_selector(HelloWorld::audio));

					}

				paus = CCMenuItemImage::create(
						(path1+"pause.png").c_str(),
						(path1+"pause.png").c_str(),
					                                    this,
					                                    menu_selector(HelloWorld::applicationDidEnterBackground));


				if(path1=="z10/")
									{
								pCloseItem->setPosition(ccp(size.width - 32, size.height-35));
											paus->setPosition(ccp(size.width-70,60));
									}
									else
									{
										pCloseItem->setPosition(ccp(size.width - 25, size.height-25));
												paus->setPosition(ccp(size.width-38,50));
									}
				pMenu = CCMenu::create(pCloseItem,NULL);
				pMenu->setTag(303);
				plauy=CCMenu::create(paus,NULL);
				//paus->setTag(1245698);
				plauy->setPosition(CCPointZero);
				this->addChild(plauy,1);
				plauy->setTag(80234);
				pMenu->setPosition(CCPointZero);
				this->addChild(pMenu, 1);

//	this->addChild(plauy,1);
//	this->addChild(pMenu, 1);
	}


}
void HelloWorld::makeman()
{
	HelloWorld::runman("boy ");
}
void HelloWorld::diamond(float dt)
{
	int ra=rand()%250+300;
	CCSprite *sprite123;
	if(path1=="z10/")
			{
		sprite123=CCSprite::create((path1+"jems.png").c_str(),CCRectMake(0,0,70,50));
			}
			else
			{
				sprite123=CCSprite::create((path1+"jems.png").c_str(),CCRectMake(0,0,50,40));
			}

	sprite123->setPosition(ccp(1024,ra));
	CCPoint realDest=ccp(-10,ra);
	sprite123->setTag(555);
	this->addChild(sprite123);
	sprite123->runAction(CCSequence::create(CCMoveTo::create(1.0,realDest),CCCallFuncN::create(this,callfuncN_selector(HelloWorld::powerMovedFinished)),NULL));
	_powers->addObject(sprite123);
}
void HelloWorld::powerpack1()
{
	int realx=1024;
	int realy=150;
	std::vector<std::string> power;
	power.push_back((path1+"helmate.png").c_str());
	power.push_back((path1+"hulk.png").c_str());
	power.push_back((path1+"jetpack.png").c_str());
	int rang=rand()%3;
	int ra=rand()%250+300;
	CCSprite *sprite;
	if(path1=="z10/")
			{
		sprite=CCSprite::create(power.at(rang).c_str(),CCRectMake(0,0,50,50));
			}
			else
			{
				sprite=CCSprite::create(power.at(rang).c_str(),CCRectMake(0,0,40,40));
			}

	sprite->setPosition(ccp(1024,ra));
	this->addChild(sprite);
	CCPoint realDest=ccp(-10,ra);
	int offRealx=realx-sprite->getPosition().x;
	int offRealy=realy-sprite->getPosition().y;
	float length=1024;
	float velocity= 480/2.2;
	float realMoveDuration=length/velocity;
	sprite->runAction(CCSequence::create(
	CCMoveTo::create(realMoveDuration,realDest),
	CCCallFuncN::create(this,callfuncN_selector(HelloWorld::powerMovedFinished)),NULL));
	if(rang==0)
		sprite->setTag(5);
	if(rang==1)
		sprite->setTag(55);
	if(rang==2)
		sprite->setTag(5555);
	_powers->addObject(sprite);
	_powers->addObject(sprite);
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	this->unscheduleAllSelectors();
	CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->end();
    exit(0);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void HelloWorld::update(float dt)
{
	CCPoint backgroundScrollVert=ccp(-1248,0);
	_backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(),ccpMult(backgroundScrollVert,dt)));
	CCArray *_backgroundSprites=CCArray::createWithCapacity(4);
	_backgroundSprites->addObject(_city1);
	_backgroundSprites->addObject(_city1);
	_backgroundSprites->addObject(_city2);
	_backgroundSprites->addObject(_city2);
	unsigned int i;
	for(i=0;i<_backgroundSprites->count();i++)
	{
		CCSprite *backgroundSprite=(CCSprite *)_backgroundSprites->objectAtIndex(i);
		float xPosition=_backgroundNode->convertToWorldSpace(backgroundSprite->getPosition()).x;
		float size=backgroundSprite->getContentSize().width;
		if(xPosition< -size*0.5)
		{
			_backgroundNode->incrementOffset(ccp(backgroundSprite->getContentSize().width*1,0),backgroundSprite);
		}
	}
}
void HelloWorld::bringRain(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	std::vector<std::string> project;
	project.push_back((path1+"missile.png").c_str());
	project.push_back((path1+"missile2.png").c_str());
	float by1;
	by1=by;
	int ra=rand()%100 + 150;
	int realx=1024;
	int realy=150;
	int randtr=rand()%project.size();
	CCSprite *tart=CCSprite::create(project.at(randtr).c_str());
	tart->setPosition(ccp(1024,by1));
	this->addChild(tart);
	CCPoint realDest=ccp(-10,by1);
	int offRealx=realx-tart->getPosition().x;
	int offRealy=realy-tart->getPosition().y;
	float length=1024;
	float velocity= 480/0.7;
	float realMoveDuration=length/velocity;
	tart->runAction(CCSequence::create(
	CCMoveTo::create(1.2,realDest),
	CCCallFuncN::create(this,callfuncN_selector(HelloWorld::spriteMoveFinished)),NULL));
	tart->setTag(2);
	_targets->addObject(tart);
}
void HelloWorld::addCoins()
{
	int ra= rand() % 150 + 450;
	int realx=1024;
	int realy=150;
	int rad=rand()%10+7;
	CCSpriteBatchNode *coinSet=CCSpriteBatchNode::create((path1+"gold.png").c_str(),10);
	this->addChild(coinSet);
	for(int i=0;i<rad;i++)
	{
		for(int j=0;j<4;j++)
		{
			CCSprite *coinSprite =CCSprite::create((path1+"gold.png").c_str(),CCRectMake(0,0,50,50));
			coinSprite->setPosition(ccp(1000+(i*60),ra-(60*j)));
			coinSet->addChild(coinSprite);
			CCPoint realDest=ccp(-20,ra+(60*j));
			int offRealx=realx-(coinSprite)->getPosition().x;
			int offRealy=realy-(coinSprite)->getPosition().y;
			float length=1024+(i*60);
			float velocity= 480/1.6;
			float realMoveDuration=length/velocity;
			(coinSprite)->runAction(CCSequence::create(
					CCMoveTo::create(realMoveDuration,realDest),
					CCCallFuncN::create(this,callfuncN_selector(HelloWorld::goldSpriteMovedFinished)),NULL));
			(coinSprite)->setTag(3);
			_coins->addObject((coinSprite));
		}
	}
}
void HelloWorld::coinSequence()
{
	int ra= 150;
			int realx=1024;
			int realy=150;
			int rad=rand()%10;
	CCSpriteBatchNode *coinSet=CCSpriteBatchNode::create((path1+"gold.png").c_str(),10);
	this->addChild(coinSet);
	for(int i=1;i<=5;i++)
	{
		CCSprite *coinSprite =CCSprite::create((path1+"gold.png").c_str(),CCRectMake(0,0,50,50));
		CCSprite *coinSprite1 =CCSprite::create((path1+"gold.png").c_str(),CCRectMake(0,0,50,50));
		coinSprite->setPosition(ccp(1000+(i*60),ra+(60*i)));
		coinSprite1->setPosition(ccp(1000+(i*60)+60,ra+(60*i)));
		coinSet->addChild(coinSprite);
		coinSet->addChild(coinSprite1);
		CCPoint realDest=ccp(-20,ra+(60*i));
		int offRealx=realx-(coinSprite)->getPosition().x;
		int offRealy=realy-(coinSprite)->getPosition().y;
		int offRealx1=realx-(coinSprite1)->getPosition().x;
		int offRealy1=realy-(coinSprite1)->getPosition().y;
		float length=1024+(i*60);
		float velocity= 480/1.6;
		float realMoveDuration=length/velocity;
		float length1=1024+(i*60)+60;
		float velocity1= 480/1.6;
		float realMoveDuration1=length1/velocity1;
		(coinSprite)->runAction(CCSequence::create(
		CCMoveTo::create(realMoveDuration,realDest),
		CCCallFuncN::create(this,callfuncN_selector(HelloWorld::goldSpriteMovedFinished)),NULL));
		(coinSprite)->setTag(3);
		_coins->addObject((coinSprite));
		(coinSprite1)->runAction(CCSequence::create(
				 				CCMoveTo::create(realMoveDuration1,realDest),
				 				CCCallFuncN::create(this,callfuncN_selector(HelloWorld::goldSpriteMovedFinished)),NULL));
		(coinSprite1)->setTag(3);
		_coins->addObject((coinSprite1));
	}
}
void HelloWorld::spriteMoveFinished(CCNode *sender)
{
	CCSprite *sprite=(CCSprite*)sender;
	this->removeChild(sprite,true);
	if(sprite->getTag()==2)
	{
		_targets->removeObject(sprite,true);
	}
}
void HelloWorld::movedtoend(CCNode *sender)
{

	this->removeChildByTag(15642,true);


}
void HelloWorld::powerMovedFinished(CCNode *sender)
{
	CCSprite *sprite=(CCSprite*)sender;
	this->removeChild(sprite,true);
	if(sprite->getTag()==5)
	{
		_powers->removeObject(sprite,true);
	}
	if(sprite->getTag()==55)
		{
			_powers->removeObject(sprite,true);
		}
	if(sprite->getTag()==555)
		{
			_powers->removeObject(sprite,true);
		}
	if(sprite->getTag()==5555)
		{
			_powers->removeObject(sprite,true);
		}
}
void HelloWorld::goldSpriteMovedFinished(CCNode *sender)
{
	CCSprite *sprite=(CCSprite*)sender;
	this->removeChild(sprite,true);
	if(sprite->getTag()==3)
	{
		_coins->removeObject(sprite,true);
	}
}
void HelloWorld::carSpriteMovedFinished(CCNode *sender)
{
	CCSprite *sprite=(CCSprite*)sender;
	this->removeChild(sprite,true);
	if(sprite->getTag()==14)
	{
		_coins->removeObject(sprite,true);
	}
}

struct man
{
	int index;
	string v_type;
	int sprite_cnt;
};
HelloWorld::~HelloWorld()
{

	if(_projectiles)
	{
		_projectiles->release();
		_projectiles = NULL;
	}
	if(_cars)
		{
		_cars->release();
		_cars = NULL;
		}
	if(_coins)
	{
		_coins->release();
		_coins=NULL;
	}
	if(_powers)
	{
		_powers->release();
		_powers=NULL;
	}
	if(_targets)
			{
		_targets->release();
		_targets = NULL;
			}

}
void HelloWorld::runCar(float dt)
{

	int randtr=rand()% 5;
	CCSpriteFrameCache *cache1=CCSpriteFrameCache::sharedSpriteFrameCache();
    cache1->addSpriteFramesWithFile((path1+"cars.plist").c_str());
    CCSpriteBatchNode *spritesheet1=CCSpriteBatchNode::create((path1+"cars.png").c_str());
    this->addChild(spritesheet1);
    std::string vechicleString = vehicles[randtr].v_type;
    CCSprite *sprite1=CCSprite::createWithSpriteFrameName((vechicleString+ " (1).png").c_str());
    sprite1->setPosition(ccp(1280,80));
    CCArray *animFrames1=CCArray::createWithCapacity(vehicles[randtr].sprite_cnt);
    char str1[100]={0};
    for(int k=1;k<=vehicles[randtr].sprite_cnt;k++)
    {
       	sprintf(str1,(vechicleString+" (%d).png").c_str(),k);
       	CCSpriteFrame *frame1=cache1->spriteFrameByName(str1);
     	animFrames1->addObject(frame1);
    }
    sprite1->setTag(14);
    CCAnimation *animation1=CCAnimation::createWithSpriteFrames(animFrames1,0.01f);
    sprite1->runAction(CCRepeatForever::create(CCAnimate::create(animation1)));
    spritesheet1->addChild(sprite1,1);
    _cars->addObject(sprite1);
    if(rf==1)
    	{
    (sprite1)->runAction(CCSequence::create(
    		CCMoveTo::create(2.5,ccp(-250,80)),
    		CCCallFuncN::create(this,callfuncN_selector(HelloWorld::carSpriteMovedFinished)),NULL));
	}
    if(rf==0)
    {
    	(sprite1)->runAction(CCSequence::create(
    	    		CCFadeOut::create(0.05),
    	    		CCCallFuncN::create(this,callfuncN_selector(HelloWorld::carSpriteMovedFinished)),NULL));
    }
	rf=1;
}
void HelloWorld::runman(string str1)
{

	k=1;j=0;
	manstate=str1;
	runcnt=0;
	if(path1=="z10/")
			{
		flyx=200;
			flyy=80;
			}
			else
			{
				flyx=120;
					flyy=80;
			}

	if(this->getChildByTag(31))
	{
		this->removeChildByTag(31);
	}
	if(this->getChildByTag(32))
	{
		this->removeChildByTag(32);
	}
	if(this->getChildByTag(114))
	{
		this->removeChildByTag(114);
	}
	if(this->getChildByTag(101))
	{
		this->removeChildByTag(101);
	}
	CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	//cache->release();
    cache->addSpriteFramesWithFile((path1+"boysprite1.plist").c_str());

    CCSpriteBatchNode *spritesheet=CCSpriteBatchNode::create((path1+"boysprite1.png").c_str());
    spritesheet->setTag(31);
    this->addChild(spritesheet);
    CCSprite *sprite=CCSprite::createWithSpriteFrameName((str1+ "(1).png").c_str());
    if(path1=="z10/")
    		{
    	sprite->setPosition(ccp(200,80));
    		}
    		else
    		{
    			sprite->setPosition(ccp(120,80));
    		}


    CCArray *animFrames=CCArray::createWithCapacity(24);
    char str[100]={0};
    for(int k=1;k<=24;k++)
    {
    	sprintf(str,(str1+"(%d).png").c_str(),k);
    	CCSpriteFrame *frame=cache->spriteFrameByName(str);
    	animFrames->addObject(frame);
	}

	CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,0.04f);
	sprite->setTag(101);
	sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	spritesheet->addChild(sprite,1);
	_projectiles->addObject(sprite);
	fprintf(stderr,"entered");
    string str2;
   	if(str1=="boy ")
   	{
   		strr2="boy";
   	}
   	if(str1=="bboy ")
   	{
   		strr2="bboyf ";
   	}
   	if(str1=="rboy ")
   	{
   		strr2="rboyf ";
   	}
   	if(str1=="gboy ")
   	{
   		strr2="gboyf ";
   	}


}
//////////////////////////////////////
//JUMPING
//////////////////////////////
void HelloWorld::flysprite()
{
	j=1;k=0;
	fprintf(stderr,"called once");
	if(this->getChildByTag(31))
	{
		this->removeChildByTag(31);
		fprintf(stderr,"\ncalled 1");
	}
	if(this->getChildByTag(32))
	{
		this->removeChildByTag(32);
		fprintf(stderr,"\ncalled 2");
	}
	if(this->getChildByTag(114))
	{
		this->removeChildByTag(114);
		fprintf(stderr,"\ncalled 3");
	}
	if(this->getChildByTag(101))
	{
		this->removeChildByTag(101);
		fprintf(stderr,"\ncalled 4");
	}
	b2FixtureDef ballShapeDef;
	b2CircleShape circle;

	CCSpriteBatchNode *spritesheet;
	if(strr2=="boy")
	{
		CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	    cache->addSpriteFramesWithFile((path1+"fly.plist").c_str());
	   spritesheet=CCSpriteBatchNode::create((path1+"fly.png").c_str());
	    spritesheet->setTag(32);
	    this->addChild(spritesheet);
	    sprite=CCSprite::createWithSpriteFrameName("boy.png");
	    sprite->setPosition(ccp(flyx,flyy));
		fprintf(stderr,"\nboy added");
		sprite->setTag(101);
	}
	if(strr2=="bboyf ")
	{
		CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile((path1+"fly.plist").c_str());
		spritesheet=CCSpriteBatchNode::create((path1+"fly.png").c_str());
		spritesheet->setTag(32);
		this->addChild(spritesheet);
	    sprite=CCSprite::createWithSpriteFrameName((strr2+ "(1).png").c_str());

	    sprite->setPosition(ccp(flyx,flyy));
	    CCArray *animFrames=CCArray::createWithCapacity(16);
	    char str[100]={0};
	    for(int k=9;k<=16;k++)
	    {
	    	sprintf(str,(strr2+"(%d).png").c_str(),k);
	    	CCSpriteFrame *frame=cache->spriteFrameByName(str);
	    	animFrames->addObject(frame);
	    }
	    CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,0.05f);
	    sprite->setTag(101);
	    sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	}
	if(strr2=="gboyf ")
	{
		CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
	    cache->addSpriteFramesWithFile((path1+"fly.plist").c_str());
	    spritesheet=CCSpriteBatchNode::create((path1+"fly.png").c_str());
	    spritesheet->setTag(32);
	    this->addChild(spritesheet);
	    sprite=CCSprite::createWithSpriteFrameName((strr2+ "(1).png").c_str());
	    sprite->setPosition(ccp(flyx,flyy));
	    CCArray *animFrames=CCArray::createWithCapacity(9);
	    char str[100]={0};
	    for(int k=1;k<=9;k++)
	    {
	    	sprintf(str,(strr2+"(%d).png").c_str(),k);
	    	CCSpriteFrame *frame=cache->spriteFrameByName(str);
	    	animFrames->addObject(frame);
	    }
	    CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,0.5f);
	    sprite->setTag(101);
	    sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	}
	if(strr2=="rboyf ")
	{
		CCSpriteFrameCache *cache=CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile((path1+"fly.plist").c_str());
	spritesheet=CCSpriteBatchNode::create((path1+"fly.png").c_str());
		spritesheet->setTag(32);
	    this->addChild(spritesheet);
	    sprite=CCSprite::createWithSpriteFrameName((strr2+ "(1).png").c_str());
	    sprite->setPosition(ccp(flyx,flyy));
		CCArray *animFrames=CCArray::createWithCapacity(9);
		char str[100]={0};
		for(int k=1;k<=9;k++)
		{
			sprintf(str,(strr2+"(%d).png").c_str(),k);
	    	CCSpriteFrame *frame=cache->spriteFrameByName(str);
			animFrames->addObject(frame);
		}
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,0.5f);
		sprite->setTag(101);
		sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	}
	spritesheet->addChild(sprite,1);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	// Create a world
	fprintf(stderr,"before run");
	b2Vec2 gravity = b2Vec2(0.0f, -40.0f);
	_world = new b2World(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,2);
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	//wall definitions
	if(path1=="z10/")
			{
		groundEdge.Set(b2Vec2(0,0), b2Vec2(size.width/PTM_RATIO, 0));
			groundBody->CreateFixture(&boxShapeDef);
			groundEdge.Set(b2Vec2(150/PTM_RATIO,0), b2Vec2(150/PTM_RATIO,size.height/PTM_RATIO));
			groundBody->CreateFixture(&boxShapeDef);
			groundEdge.Set(b2Vec2(0, 680/PTM_RATIO),
			b2Vec2(size.width/PTM_RATIO, 565/PTM_RATIO));
			groundBody->CreateFixture(&boxShapeDef);
			groundEdge.Set(b2Vec2(size.width/PTM_RATIO, size.height/PTM_RATIO),
			b2Vec2(size.width/PTM_RATIO, 0));
			groundBody->CreateFixture(&boxShapeDef);
			}
			else
			{
				groundEdge.Set(b2Vec2(0,0), b2Vec2(size.width/PTM_RATIO, 0));
					groundBody->CreateFixture(&boxShapeDef);
					groundEdge.Set(b2Vec2(80/PTM_RATIO,0), b2Vec2(80/PTM_RATIO,size.height/PTM_RATIO));
					groundBody->CreateFixture(&boxShapeDef);
					groundEdge.Set(b2Vec2(0, 650/PTM_RATIO),b2Vec2(size.width/PTM_RATIO, 565/PTM_RATIO));
					groundBody->CreateFixture(&boxShapeDef);
					groundEdge.Set(b2Vec2(size.width/PTM_RATIO, size.height/PTM_RATIO),
					b2Vec2(size.width/PTM_RATIO, 0));
					groundBody->CreateFixture(&boxShapeDef);
			}

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(flyx/PTM_RATIO, flyy/PTM_RATIO);
	ballBodyDef.userData = sprite;
	_body = _world->CreateBody(&ballBodyDef);
	circle.m_radius = 26.0/PTM_RATIO;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = playerMass;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.01f;
	_body->CreateFixture(&ballShapeDef);
	_projectiles->addObject(sprite);
	fprintf(stderr,"called nom");

}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *touches,cocos2d::CCEvent *event)
{
	if(m_touch)
			return;
		m_touch=true;
	fprintf(stderr,strr2.c_str());
	if(j==0)
	{
	HelloWorld::flysprite();
	}
	CCTouch *touch=(CCTouch *)(touches->anyObject());
	CCPoint location=touch->getLocationInView();
	_body->SetLinearVelocity(b2Vec2(0,18));
	if(this->getChildByTag(1296321))
	{
		//this->removeChildByTag(1296321);
	}
	else
	{
	//HelloWorld::partic();
	}
}
void HelloWorld::ccTouchesEnded(cocos2d::CCSet *touches,cocos2d::CCEvent *event)
{
	m_touch=false;
}
void HelloWorld::Bgspeed(CCPoint ss)
{
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	if(this->getChildByTag(665))
	{
		this->removeChildByTag(665);
	}
	if(this->getChildByTag(666))
	{
		this->removeChildByTag(666);
	}
	if(this->getChildByTag(667))
	{
		this->removeChildByTag(667);
	}
	this->addChild(_backgroundNode,0);
	_trees=CCSprite::create((path1+"backcopy.png").c_str());
	_trees->setTag(665);
	_city1=CCSprite::create((path1+"backcopy.png").c_str());
	_city1->setTag(666);
	_city2=CCSprite::create((path1+"backcopy.png").c_str());
	_city2->setTag(667);
	_backgroundNode->addChild(_trees,0,bgspeed,ccp(size.width/2,size.height/2));
	_backgroundNode->addChild(_city1,0,bgspeed,ccp(0,size.height/2));
	_backgroundNode->addChild(_city2,0,bgspeed,ccp(_city1->getContentSize().width,size.height/2));
}
void HelloWorld::partic()
{
	CCSize sizep=CCDirector::sharedDirector()->getWinSize();
	m_emitter = CCParticleGalaxy::create();
	m_emitter->retain();
	m_emitter->setTag(1296321);
	this->addChild(m_emitter, 50);
	m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage((path1+"images/fire.png").c_str()));
	m_emitter->setEmissionRate(50.0);
	m_emitter->setSpeed(50);
	m_emitter->setLifeVar(2);
	m_emitter->setLife(2);
	m_emitter->setPosition( ccp(bx, by) );
	this->schedule(schedule_selector(HelloWorld::particremoved),0.11);
}
void HelloWorld::particremoved(float dt)
{
	m_emitter->stopSystem();
	this->removeChildByTag(1296321);
	//m_emitter->cleanup();
}
void HelloWorld::partic1()
{
	CCSize sizep=CCDirector::sharedDirector()->getWinSize();
	m_emitter1 = new CCParticleSystemQuad();
	std::string filename = (path1+"Particles/ExplodingRing.plist").c_str();
	m_emitter1->initWithFile(filename.c_str());
	addChild(m_emitter1, 10);
	m_emitter1->setPosition( ccp(bx, by) );
	this->schedule(schedule_selector(HelloWorld::particremoved1),0.75);
}
void HelloWorld::particremoved1(float dt )
{
	m_emitter1->stopSystem();

}







