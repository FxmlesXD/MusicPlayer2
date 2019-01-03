#pragma once
class CVariant
{
public:
	CVariant(int value);
	CVariant(unsigned int value);
	CVariant(double value);
	CVariant(LPCTSTR value);
	CVariant(const CString& value);
	CVariant(const wstring& value);

	~CVariant();

	CString ToString() const;

private:
	enum class eType { INT, UINT, DOUBLE, STRING, WSTRING };

	int m_value_int;
	double m_value_double;
	CString m_value_string;
	std::wstring m_value_wstring;
	eType m_type;

};

