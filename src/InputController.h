// InputController.h: interface for the InputController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined _InputController_H_
#define _InputController_H_

#include "wxprec.h"

class InputController
{
public:
	InputController(){};
	virtual ~InputController(){};
	static InputController * Create(const wxString &name);
	virtual void Toggle() = 0;
	virtual void On() = 0;
	virtual void Off() = 0;
	virtual void Process(float x, float y, float z) = 0;
	virtual void Init(float x, float y, float z) = 0;
	virtual bool IsMouseDown() = 0;

};

#endif // !defined _InputController_H_
