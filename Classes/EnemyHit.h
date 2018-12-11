#ifndef _ENEMY_HIT_
#define _ENEMY_HIT_

#include"cocos2d.h"
#include"GameObject.h"

class EnemyHit;
typedef std::function<void(EnemyHit* Slash)> OnHitDestroyCallback;
class EnemyHit:public GameObject
{
public:
	EnemyHit();
	~EnemyHit();
	virtual bool init();
	CREATE_FUNC(EnemyHit);
	virtual void onContactBeganWith(GameObject* obj) override;
	virtual void onContactPostSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve) override;
	virtual void onContactSeparateWith(GameObject* obj, cocos2d::PhysicsContact& contact) override;
	virtual void onContactPreSolveWith(GameObject* obj, cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve) override;
	void setOnDestroyCallback(OnHitDestroyCallback callback);
	void reset();
	void attackAt(cocos2d::Vec2 pos);
	void scheduleAutoDestroy();

	float getDmg();
private:
	void update(float delta);

private:
	cocos2d::Sprite*	_sprFrame;
	bool _willBeDestroy;
	OnHitDestroyCallback _onHitDestroyCallback;

};
#endif // !1



