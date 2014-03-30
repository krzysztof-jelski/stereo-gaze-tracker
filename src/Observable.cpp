#include "wxprec.h"
#include "Observable.h"

Observable::Observable()
{
}
Observable::~Observable()
{
}

void Observable::AddObserver(Observer * observer)
{
	m_observers.Add(observer);
}

void Observable::RemoveObserver(Observer *observer)
{
	m_observers.Remove(observer);
}
void Observable::NotifyObservers()
{
	for (unsigned int i = 0; i < m_observers.Count(); i++)
		m_observers[i]->Update(this);
}
