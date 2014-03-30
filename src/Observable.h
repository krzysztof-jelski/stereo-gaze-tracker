/** @file Observable.h
 *  Interface for the Observable class.
 */


#ifndef Observable_H
#define Observable_H

#include "wxprec.h"
#include "Observer.h"

WX_DEFINE_ARRAY(Observer *, ArrayOfObservers);


class Observable 
{
public:
	Observable();
	virtual ~Observable();
	void NotifyObservers();
	void AddObserver(Observer * observer);
	void RemoveObserver(Observer *observer);

protected:
	ArrayOfObservers m_observers;
};

#endif // ifndef Observable_H
