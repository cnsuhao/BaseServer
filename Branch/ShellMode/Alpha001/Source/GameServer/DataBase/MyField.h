#ifndef _MYFIELD_H
#define _MYFIELD_H
/////////////////////////////////////////////////////////////////////////////
class CCriticalSection;
class CMyRecordset;

class CMyField
{
// Constructor
public:
	CMyField();
	virtual ~CMyField();

public:
	MYHEAP_DECLARATION(s_heap)

protected:
	unsigned long			m_ulType;
	union
	{
		unsigned char		m_ucVal;	//TINY			//�� ����Ҫ����ֱ��ʹ��LONG
		char				m_cVal;		//TINY			//�� ����Ҫ����ֱ��ʹ��LONG
		short int			m_nVal;		//SHORT			//�� ����Ҫ����ֱ��ʹ��LONG
		int					m_iVal;		//INT			//�� ����Ҫ����ֱ��ʹ��LONG
		long				m_lVal;		//LONG
		unsigned long		m_ulVal;	//UNSIGNED LONG

		float				m_fVal;		//FLOAT
		double				m_dVal;		//DOUBLE
		I64					m_i64Val;	//int64
	
	};
	char*				m_szVal;	//CSTRING
	int					m_nIndex;
	MYSQL_FIELD			m_Field;
	CMyField *			m_pMyField;		//paled ָ����������ڸ��¡�

	friend class	CMyRecordset;
	friend class	CMyRecord;

// Operations
private:
	void Clear();

// Attributes
public:
	void					FieldName(char * szFileName);		
	unsigned int			FieldAttr() const;
	unsigned int			FieldType() const;
	unsigned int			FieldLen()	const;

	void					CopyTo(char * szField, int nLen);
	void					CopyFrom(const char * szField, int nLen);

// Operator
public:
	operator int	()
	{	if ( m_ulType == FIELD_TYPE_SHORT
				|| m_ulType == FIELD_TYPE_TINY
				|| m_ulType == FIELD_TYPE_LONG )
			return m_iVal;
		else return -1;
	};

	operator long()
	{
		if (m_ulType==FIELD_TYPE_SHORT 
				|| m_ulType == FIELD_TYPE_TINY
				|| m_ulType==FIELD_TYPE_LONG)
			return m_lVal;
		else return -1;
	};

	operator unsigned char ()
	{	if (m_ulType==FIELD_TYPE_TINY )
			return m_ucVal;
		else return 0;
	};

	operator char ()
	{	if (m_ulType==FIELD_TYPE_TINY )
			return m_cVal;
		else return 0;
	};

	operator float()
	{	
		if (m_ulType==FIELD_TYPE_DOUBLE ||
			m_ulType==FIELD_TYPE_FLOAT)
			return m_fVal;
		else return 0;
	};

	operator double()
	{
		if (m_ulType==FIELD_TYPE_DOUBLE ||
			m_ulType==FIELD_TYPE_FLOAT)
			return m_dVal;
		else return 0; 

	};

	
	operator unsigned int()
	{
		if (m_ulType == FIELD_TYPE_SHORT 
				|| m_ulType == FIELD_TYPE_TINY
				|| m_ulType == FIELD_TYPE_LONG)
			return m_iVal;
		else return 0; 

	};

	operator unsigned long()
	{
		if (m_ulType == FIELD_TYPE_SHORT 
				|| m_ulType == FIELD_TYPE_TINY
				|| m_ulType == FIELD_TYPE_LONG)
			return m_lVal;
		else return 0; 
	};

	operator unsigned short()
	{
		if (m_ulType == FIELD_TYPE_SHORT 
				|| m_ulType == FIELD_TYPE_TINY
				|| m_ulType == FIELD_TYPE_LONG)
			return m_nVal;
		else return 0; 
	};

	operator __int64()
	{
		if (m_ulType == FIELD_TYPE_SHORT 
			|| m_ulType == FIELD_TYPE_TINY
			|| m_ulType == FIELD_TYPE_LONG
			|| m_ulType == FIELD_TYPE_LONGLONG)
			return m_i64Val;
		else return 0; 
	};



	operator const char* ()			//���� BUG: ����ָ�룬�ⲿ�ɷǷ�д���ڲ������ܻ���ִ��ռ������BUG, ��δ���
	{
		if (m_ulType==FIELD_TYPE_STRING ||
			m_ulType==FIELD_TYPE_VAR_STRING)
			return (m_szVal);
		else return "";				//paled return NULL
	}
	CMyField& operator = (const char* szVal);
	
	CMyField& operator = (int nOp);

	CMyField& operator = (long lOp);
	CMyField& operator = (unsigned long lOp );

	CMyField& operator = (float fltOp);
	CMyField& operator = (double dblOp);
	CMyField& operator = (_int64 i64Op);

	CMyField& operator = (unsigned char chOp);
	CMyField& operator = (char chOp);
};
	
/////////////////////////////////////////////////////////////////////////////
#endif
