/** @file StepDiff1st.cpp
 *  Implementation of the StepDiff1st class.
 */

#include "StepDiff1st.h"

IplImage* StepDiff1st::DoDiff(IplImage* src)
{
	if (m_sizeData.SizeChanged(src))
		m_Diff.ReInit();
	return m_Diff.GetDiff(src);
}

