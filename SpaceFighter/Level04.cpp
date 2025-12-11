

#include "Level04.h"
#include "BossEnemyShip.h"
extern int LEVELCOUNT;

void Level04::LoadContent(ResourceManager& resourceManager)
{
	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyBoss.png");

	const int COUNT = 1;
	LEVELCOUNT = 1;

	double xPositions[COUNT] =
	{
		0.5
	};

	double delays[COUNT] =
	{
		0.0
	};

	float delay = 3.0; // start delay
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += delays[i];
		position.Set(xPositions[i] * Game::GetScreenWidth(), (pTexture->GetCenter().Y - 350));

		BossEnemyShip* pEnemy = new BossEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);
	}
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground03.png"));

	Level::LoadContent(resourceManager);
}

