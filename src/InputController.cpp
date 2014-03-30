// InputController.cpp: implementation of the InputController class.
//
//////////////////////////////////////////////////////////////////////

#include "wxprec.h"
#include "InputController.h"
#include "InputControllerRelative.h"
#include "InputControllerAbsolute.h"

InputController* InputController::Create(const wxString& name)
{
	if (name.Cmp("InputControllerRelative") == 0)
		return new InputControllerRelative();
	if (name.Cmp("InputControllerAbsolute") == 0)
		return new InputControllerAbsolute();

	wxCHECK_MSG(0==1, NULL, "Wrong type!");
}