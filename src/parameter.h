#pragma once
#include "wxprec.h"
#include "SizeData.h"
#include "Observer.h"

class Parameter : public Observer, public Observable
{
public:
	enum PercType
	{
		WIDTH = 0,
		HEIGHT,
		AREA,
		COLOUR_RANGE,
		NONE
	};

	enum ParamType
	{
		LONG = 0,
		DOUBLE
	};

public:
	Parameter(void);
	virtual ~Parameter(void);
public:
	// Get parameter's name
	wxString GetName(void) const;
	// Get parameter's description
	wxString GetInfo(void) const;
	// Set parameter's name
	void SetName(const wxString& name);
	// Set parameter's description
	void SetInfo(const wxString& info);
	// Set type of percent reference
	void SetPercType(const PercType type);
	void SetPercType(const int type);
	void SetPercType(const wxString& type);
	// Set size data
	void SetSizeData(SizeData *pSizeData);
	bool IsActive();
	void SetActive(bool active);

	// Get parameter's value
	virtual const void * GetValue(void) = 0;
	virtual void SetValue(const void *value) = 0;
	virtual void SetValue(const wxString& value) = 0;

	// Get percentage value
	virtual double GetPercValue() const;
	virtual void SetPercValue(const double percValue) = 0;
	virtual double GetPercMin() const;
	virtual double GetPercMax() const;
	bool IsPercentAvail() const;
	bool IsPercentModification() const;
	
	virtual void * GetMin() = 0;
	virtual void SetMin(const void *min) = 0;
	virtual void SetMin(const wxString& min) = 0;
	virtual void * GetMax() = 0;
	virtual void SetMax(const void *max) = 0;
	virtual void SetMax(const wxString& max) = 0;
	
	virtual void * GetStep()=0;
	virtual void SetStep(const void *step) = 0;
	virtual void SetStep(const wxString& step) = 0;
	virtual ParamType GetType() = 0;

	// Observer members
	virtual void Update(Observable *observable);
	// Observerable states
	bool IsDestroyed();
protected:
	virtual void UpdatePercRef() = 0;
	virtual void UpdatePercentValue() = 0;
	
protected:
	// Parameters short name, used to refer to param from other classes
	wxString m_Name;
	// Parameters description
	wxString m_Description;
	// Percentage value
	double m_Percent;
	// Percentage reference type
	PercType m_PercType;
	// Is current value modified by percentage
	bool m_isPercentModification;
	// Current size data
	SizeData* m_pSizeData;
	// Active state
	bool m_Active;
	// Inside destructor
	bool m_Destroyed;
};

class LongParameter : public Parameter
{
public:
	LongParameter();
public:
	virtual const void * GetValue(void);
//	virtual const long& GetLongValue(void);
//	virtual const double& GetDoubleValue(void);
	
	virtual void SetValue(const void *value);
	virtual void SetValue(const wxString& value);

	virtual void SetPercValue(const double percValue);
	virtual double GetPercMin() const;
	virtual double GetPercMax() const;

	virtual void * GetMin();
	virtual void SetMin(const void *min);
	virtual void SetMin(const wxString& min);
	virtual void * GetMax();
	virtual void SetMax(const void *max);
	virtual void SetMax(const wxString& max);

	virtual ParamType GetType();
	virtual void * GetStep();
	virtual void SetStep(const void *);
	virtual void SetStep(const wxString& step);

protected:
	void SetValue(const long value);
	long GetStepLong();
	void SetStep(long step);
	virtual void UpdatePercRef();
	virtual void UpdatePercentValue();
	void UpdateValueFromPercent();
protected:
	long m_Value;
	long m_PercRef;
	long m_Step;
	long m_Min;
	long m_Max;

};

class DoubleParameter : public Parameter
{
public:
	DoubleParameter();
public:
	virtual const void * GetValue(void);
//	virtual const long& GetLongValue(void);
//	virtual const double& GetDoubleValue(void);
	
	virtual void SetValue(const void *value);
	virtual void SetValue(const wxString& value);

	virtual void SetPercValue(const double percValue);
	virtual double GetPercMin() const;
	virtual double GetPercMax() const;
	virtual ParamType GetType();

	virtual void * GetMin();
	virtual void SetMin(const void *min);
	virtual void SetMin(const wxString& min);

	virtual void * GetMax();
	virtual void SetMax(const void *max);
	virtual void SetMax(const wxString& max);
	virtual void SetStep(const wxString& step);
	virtual void SetStep(const void *);
	virtual void * GetStep();

protected:
	void SetValue(const double value);
	double GetStepDouble();
	void SetStep(double step);
	
	virtual void UpdatePercRef();
	virtual void UpdatePercentValue();
	void UpdateValueFromPercent();
protected:
	double m_Value;
	double m_PercRef;
	double m_Step;
	double m_Min;
	double m_Max;

};