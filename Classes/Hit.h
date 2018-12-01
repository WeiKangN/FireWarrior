#ifndef _HIT_H
#define _HIT_H

#include"cocos2d.h"
#include"GameObject.h"

class Hit;
typedef std::function<void(Hit* Slash)> OnHitDestroyCallback;
class Hit : public GameObject

{
public:
	Hit();
	~Hit();
	virtual bool init();
	CREATE_FUNC(Hit);
	virtual void onContactBeganWith(GameObject* obj) override;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	void setOnDestroyCallback(OnHitDestroyCallback callback);
	void reset();
	void attackAt(cocos2d::Vec2 pos);
	void scheduleAutoDestroy();
private :
	void update(float delta);

private:
	cocos2d::Sprite*	_sprFrame;
	bool _willBeDestroy;
	OnHitDestroyCallback _onHitDestroyCallback;


};




#endif // !_HIT_H

