#ifndef OISEAU_MANAGER_H
#define OISEAU_MANAGER_H

#include <Ennemy.h>
#include <Entity.h>
#include <string>

class OiseauManager
{
public:
	static OiseauManager& Instance()
	{
		static OiseauManager instance;
		return instance;
	}

	void AddOiseau(Ennemy* aOiseau);
	std::vector<Ennemy*> GetOiseau() { return m_OiseauList; }
	void RemoveOiseau();
	void ChangeLevel();
	void SetCurrentLevel(int aLevel) { m_CurrentLevel = aLevel; }
	void ClearList();
	bool GetVictory();
	int GetLevel() { return m_CurrentLevel ; }
	

private:
	std::vector<Ennemy*> m_OiseauList;
	int m_CurrentLevel = 1;
	int m_OiseauCount = 0;
	bool m_isVictory = false;
};

#endif // !OISEAU_MANAGER_H
