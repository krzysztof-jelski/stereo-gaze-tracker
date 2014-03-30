#include "wxprec.h"
#include "Parameter.h"


///////////////////////////////////////////////////////////////////////////////
//									Parameter				                 //
///////////////////////////////////////////////////////////////////////////////
Parameter::Parameter(void) :
	m_pSizeData(NULL),
	m_isPercentModification(false),
	m_Destroyed(false)
{
}

Parameter::~Parameter(void)
{
	m_Destroyed = true;
	NotifyObservers();
	if (m_pSizeData != NULL)
		m_pSizeData->RemoveObserver(this);
}

bool Parameter::IsDestroyed()
{
	return m_Destroyed;
}
// Get parameter's name
wxString Parameter::GetName(void) const
{
	return m_Name;
}

void Parameter::SetName(const wxString &name)
{
	m_Name = name;
}

// Get parameter's description
wxString Parameter::GetInfo(void) const
{
	return m_Description;
}

void Parameter::SetInfo(const wxString &info)
{
	m_Description = info;
}

void Parameter::SetPercType(const PercType type)
{
	m_PercType = type;
	UpdatePercRef();
}

void Parameter::SetPercType(const int type)
{
	SetPercType( (PercType) type );
}

void Parameter::SetPercType(const wxString& type)
{
	if (type.IsSameAs("none"))
		SetPercType(Parameter::NONE);
	else if (type.IsSameAs("area"))
		SetPercType(Parameter::AREA);
	else if (type.IsSameAs("width"))
		SetPercType(Parameter::WIDTH);
	else if (type.IsSameAs("height"))
		SetPercType(Parameter::HEIGHT);
	else if (type.IsSameAs("colour_range"))
		SetPercType(Parameter::COLOUR_RANGE);
	else
		wxFAIL_MSG("Unkown percent type");
}
double Parameter::GetPercValue() const
{
	return m_Percent;
}

double Parameter::GetPercMin() const
{
	return 0;
}

double Parameter::GetPercMax() const
{
	return 100;
}

bool Parameter::IsPercentAvail() const
{
	return (m_PercType != Parameter::NONE);
}

bool Parameter::IsPercentModification() const
{
	return m_isPercentModification;
}
void Parameter::SetSizeData(SizeData *pSizeData)
{
	m_pSizeData = pSizeData;
	m_pSizeData->AddObserver(this);
	Update(pSizeData);
}

bool Parameter::IsActive()
{
	return m_Active;
}

void Parameter::SetActive(bool active)
{
	m_Active = active;
}

void Parameter::Update(Observable *observable)
{
	UpdatePercRef();
}
///////////////////////////////////////////////////////////////////////////////
//								Long Parameter				                 //
///////////////////////////////////////////////////////////////////////////////

LongParameter::LongParameter() : Parameter(),
	m_PercRef(-1)
{

}


const void * LongParameter::GetValue()
{
	SetActive(true);
	return &m_Value;
}


void LongParameter::SetValue(const long value)
{
	m_Value = value;
	UpdatePercentValue();
	m_isPercentModification = false;
}

void LongParameter::SetValue(const void *value)
{
	SetValue( *((long *)value));
}

void LongParameter::SetValue(const wxString& value)
{
	long temp;
	if (value.ToLong(&temp))
		SetValue(temp);
}
void LongParameter::SetPercValue(const double percValue)
{
	if ((percValue < 0.0) || (percValue > 100.0))
		return;
	if (m_PercType == NONE)
		return;
	if (m_PercRef == -1)
		return;
	m_Percent = percValue;
	UpdateValueFromPercent();
	m_isPercentModification = true;
}

void LongParameter::UpdateValueFromPercent()
{
	m_Value = m_PercRef * (m_Percent / 100.0);
}

double LongParameter::GetPercMin() const
{
	if ((m_PercRef == -1) || (m_PercType == NONE))
		return Parameter::GetPercMin();
	return ((double)m_Min / (double)m_PercRef) * 100.0;
}

double LongParameter::GetPercMax() const
{
	if ((m_PercRef == -1) || (m_PercType == NONE))
		return Parameter::GetPercMax();
	return ((double)m_Max / (double)m_PercRef) * 100.0;
}

void LongParameter::UpdatePercRef()
{
	if (m_pSizeData == NULL)
		return;
	switch (m_PercType)
	{
	case AREA:
		m_PercRef = m_pSizeData->GetArea();
		break;
	case HEIGHT:
		m_PercRef = m_pSizeData->GetHeight();
		break;
	case WIDTH:
		m_PercRef = m_pSizeData->GetWidth();
		break;
	case COLOUR_RANGE:
		m_PercRef = 255;
		break;
	default:
		m_PercRef = -1;
	}
	if (IsPercentModification())
		UpdateValueFromPercent();
	else
		UpdatePercentValue();
	NotifyObservers();
}

Parameter::ParamType LongParameter::GetType()
{
	return LONG;
}

long LongParameter::GetStepLong()
{
	return m_Step;
}

void LongParameter::SetStep(long step)
{
	m_Step = step;
}

void * LongParameter::GetStep()
{
	return &m_Step;
}

void LongParameter::SetStep(const void * step)
{
	m_Step = * (long *)step;
}

void LongParameter::SetStep(const wxString& step)
{
	step.ToLong(&m_Step);
}

void * LongParameter::GetMin()
{
	return &m_Min;
}

void LongParameter::SetMin(const void *min)
{
	m_Min = *(long *)min;
}

void LongParameter::SetMin(const wxString &min)
{
	min.ToLong(&m_Min);
}
void * LongParameter::GetMax()
{
	return &m_Max;
}
void LongParameter::SetMax(const void *max)
{
	m_Max = * (long *)max;
}
void LongParameter::SetMax(const wxString &max)
{
	max.ToLong(&m_Max);
}

void LongParameter::UpdatePercentValue()
{
	if ((m_PercType != NONE) && (m_PercRef != -1))
		m_Percent = 100.0 * (double)m_Value / (double)m_PercRef;
}
///////////////////////////////////////////////////////////////////////////////
//								Double Parameter				             //
///////////////////////////////////////////////////////////////////////////////

DoubleParameter::DoubleParameter() : Parameter(),
	m_PercRef(-1)
{

}


const void * DoubleParameter::GetValue()
{
	SetActive(true);
	return &m_Value;
}


void DoubleParameter::SetValue(const double value)
{
	m_Value = value;
	UpdatePercentValue();
	m_isPercentModification = false;
}


void DoubleParameter::SetValue(const void *value)
{
	SetValue( *((double *)value));
}

void DoubleParameter::SetValue(const wxString& value)
{
	double temp;
	if (value.ToDouble(&temp))
		SetValue(temp);
}

void DoubleParameter::SetPercValue(const double percValue)
{
	if ((percValue < 0.0) || (percValue > 100.0))
		return;
	if (m_PercType == NONE)
		return;
	if (m_PercRef == -1)
		return;
	m_Percent = percValue;
	UpdateValueFromPercent();
	m_isPercentModification = true;
}

void DoubleParameter::UpdateValueFromPercent()
{
	m_Value = m_PercRef * (m_Percent / 100.0);
}

double DoubleParameter::GetPercMin() const
{
	if ((m_PercRef == -1) || (m_PercType == NONE))
		return Parameter::GetPercMin();
	return (m_Min / m_PercRef) * 100.0;
}

double DoubleParameter::GetPercMax() const
{
	if ((m_PercRef == -1) || (m_PercType == NONE))
		return Parameter::GetPercMin();
	return (m_Max / m_PercRef) * 100.0;
}

void DoubleParameter::UpdatePercRef()
{
	if (m_pSizeData == NULL)
		return;
	switch (m_PercType)
	{
	case AREA:
		m_PercRef = m_pSizeData->GetArea();
		break;
	case HEIGHT:
		m_PercRef = m_pSizeData->GetHeight();
		break;
	case WIDTH:
		m_PercRef = m_pSizeData->GetWidth();
		break;
	case COLOUR_RANGE:
		m_PercRef = 255;
		break;
	default:
		m_PercRef = -1;
	}
	UpdatePercentValue();
	NotifyObservers();
}

Parameter::ParamType DoubleParameter::GetType()
{
	return DOUBLE;
}


double DoubleParameter::GetStepDouble()
{
	return m_Step;
}

void DoubleParameter::SetStep(double step)
{
	m_Step = step;
}

void * DoubleParameter::GetStep()
{
	return &m_Step;
}

void DoubleParameter::SetStep(const void * step)
{
	m_Step = * (double *)step;
}

void DoubleParameter::SetStep(const wxString &step)
{
	step.ToDouble(&m_Step);
}
void * DoubleParameter::GetMin()
{
	return &m_Min;
}
void DoubleParameter::SetMin(const void *min)
{
	m_Min = *(double *)min;
}

void DoubleParameter::SetMin(const wxString &min)
{
	min.ToDouble(&m_Min);
}
void * DoubleParameter::GetMax()
{
	return &m_Max;
}
void DoubleParameter::SetMax(const void *max)
{
	m_Max = * (double *)max;
}

void DoubleParameter::SetMax(const wxString &max)
{
	max.ToDouble(&m_Max);
}

void DoubleParameter::UpdatePercentValue()
{
	if ((m_PercType != NONE) && (m_PercRef != -1))
		m_Percent = 100.0 * m_Value / m_PercRef;
}