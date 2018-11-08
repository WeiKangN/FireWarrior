#ifndef _EVIL_DOG_
#define _EVIL_DOG_

#include"cocos2d.h"
#include"GamePlayLayer.h"
class EvilDog : public cocos2d::Node

{
public:
	EvilDog();
	~EvilDog();
	CREATE_FUNC(EvilDog);
	virtual bool init();
	void DogIdle();
	void Run();

private:
	cocos2d::Sprite*_sprDoggie;
};



#endif // !_EVIL_DOG_

