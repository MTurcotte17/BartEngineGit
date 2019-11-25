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

	void AddOiseau(Ennemy* aOiseau) { m_OiseauList.push_back(aOiseau); }
	std::vector<Ennemy*> GetOiseau() { return m_OiseauList; }
	void RemoveOiseau() { m_OiseauList.pop_back();}
	

private:
	std::vector<Ennemy*> m_OiseauList;
};

#endif // !OISEAU_MANAGER_H
