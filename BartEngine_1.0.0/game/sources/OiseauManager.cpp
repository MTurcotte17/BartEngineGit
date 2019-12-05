#include <OiseauManager.h>
#include <iostream>

void OiseauManager::AddOiseau(Ennemy * aOiseau)
{
	m_OiseauList.push_back(aOiseau);
	m_OiseauCount++;
}

void OiseauManager::RemoveOiseau()
{
	m_OiseauCount--;
	if (m_OiseauCount == 0)
	{
		m_isVictory = true;
	}
	std::cout << m_OiseauCount << std::endl;
}

bool OiseauManager::GetVictory()
{
	return m_isVictory;
}

void OiseauManager::ChangeLevel()
{
	m_CurrentLevel++;
	m_isVictory = false;
	if (m_CurrentLevel == 2)
	{
		Engine::Instance().GetScene().Load("LevelTwo");
	}
	else
	{
		m_CurrentLevel = 1;
		Engine::Instance().GetScene().Load("MainMenu");
	}
}

void OiseauManager::ClearList()
{
	if (m_OiseauList.size() != 0)
	{
		m_OiseauList.clear();
	}
	m_OiseauCount = m_OiseauList.size();
}
