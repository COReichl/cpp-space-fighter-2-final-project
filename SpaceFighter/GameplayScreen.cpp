
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"
#include "Level02.h"
#include "Level03.h"
#include "Level04.h"

int m_levelIndex = 0;
int levelIndex = 0;
extern int howmany;
extern int LEVELCOUNT;

GameplayScreen::GameplayScreen(int levelIndex)
{
	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetOnRemove([this](){ AddScreen(new MainMenuScreen()); });

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);
}

void GameplayScreen::LoadLevel(int levelIndex)
{
	if (m_pLevel) delete m_pLevel;

	switch (levelIndex)
	{
	case 0: std::cout << "Starting Level 1 \n"; m_pLevel = new Level01(); break;
	case 1: std::cout << "Starting Level 2 \n"; m_pLevel = new Level02(); break;
	case 2: std::cout << "Starting Level 3 \n"; m_pLevel = new Level03(); break;
	case 3: std::cout << "Starting Level 4 \n"; m_pLevel = new Level04(); break;
	}
	m_pLevel->SetGameplayScreen(this);
	m_pLevel->LoadContent(*m_pResourceManager);
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime)
{
	m_pLevel->Update(gameTime);
	//checks how many of the enemies have been killed or despawned
	if (howmany == LEVELCOUNT) {
		//if the number of enemies in the level have despawned then it moves onto the next level
		m_levelIndex++;
		if (m_levelIndex == 4) {
		//if it would be moving onto level 4 it switches back to the main menu instead
		SetOnRemove([this]() { AddScreen(new MainMenuScreen()); });
		Exit();
		m_levelIndex = 0;
		howmany = 0;
		LEVELCOUNT = 21;
		}
		else {
			SetOnRemove([this]() { AddScreen(new GameplayScreen()); });
			Exit();
			howmany = 0;
		}
	}
}

void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}
