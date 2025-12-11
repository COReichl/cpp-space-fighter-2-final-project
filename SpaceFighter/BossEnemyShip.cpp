
#include "BossEnemyShip.h"
#include "Level.h"

extern int howmany;

BossEnemyShip::BossEnemyShip()
{
	SetSpeed(10);
	SetMaxHitPoints(20);
	SetCollisionRadius(250);
}


void BossEnemyShip::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		float x = sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
		x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f;
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());

		if (!IsOnScreen()) {
			Deactivate();
			howmany++;
		}
	}

	EnemyShip::Update(gameTime);
}


void BossEnemyShip::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
