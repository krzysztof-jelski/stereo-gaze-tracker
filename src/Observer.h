/** @file Observer.h
 *  Interface for the Observer class.
 */


#ifndef Observer_H
#define Observer_H

class Observable;

class Observer 
{
public:
	Observer(){};
	virtual ~Observer(){};
	virtual void Update(Observable* observable)=0;
protected:

};

#endif // ifndef Observer_H
