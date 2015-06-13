// myrecordset.h

#ifndef	MYRECORDSET_H
#define	MYRECORDSET_H

class CCriticalSection;
class CMyDatabase;
class IRecordset;
class IRecord;
class CMyRecordset : public IRecordset
{
	friend class CMyRecord;
	friend class CMyField;
// Constructor
public:
	CMyRecordset(CMyDatabase  * pMyDatabase);
	virtual ~CMyRecordset();

public: // recordset
	virtual UINT		RecordCount();								// return -1: error
	virtual void		MoveFirst();
	virtual bool		MoveNext();

public: // record
	virtual IRecord*	CreateNewRecord(DB_KEY idNewKey = NEWKEY_NONE);
	virtual	void		Release() { delete this; }

	virtual DB_KEY		InsertRecord(INT nType = DBUPDATE_SYNC);
	virtual bool		UpdateRecord(INT nType = DBUPDATE_ASYNC);
	virtual bool		DeleteRecord(INT nType = DBUPDATE_SYNC);

	virtual bool		IsString	(int idx);
	virtual int			GetFieldCount(void){return m_uiFieldsCount;}
	virtual void		ClearUpdateFlags	()		{ ClsEditFlag(); }
	virtual DB_KEY		GetKey();
	

public:
	virtual	I64			GetInt64	(int idx);
	virtual I64			GetInt64	(const char* szField);
	virtual void		SetInt64	(int idx, I64 i64Data);
	virtual void		SetInt64	(const char* szField,	I64 i64Data);
	virtual	double  	GetDouble	(int idx);
	virtual int			GetInt		(int idx);
	virtual int     	GetInt		(const char* szField);
	virtual	const char*	GetStr		(const char* szField);
	virtual const char*	GetStr		(int idx);
	virtual void		SetInt		(int idx, int nData);
	virtual void		SetInt		(const char* szField, int nData);
	virtual void		SetStr		(int idx, const char* szData, int nSize);
	virtual	void		SetStr		(const char* szField,const char* szData, int nSize);
	

public:
	static CMyRecordset* CreateNew(CMyDatabase  *pMyDatabase);

public:
	MYHEAP_DECLARATION(s_heap)
	
public:
	enum { modeEdit, modeAddNew, modeDelete };


	virtual bool Open( const char * lpszSQL);
	virtual void Close();

public: // no used
	int FieldsCount();

	void AddNew();
	void Edit();
	bool Update();
	void Delete();

	void MoveLast();
	void MovePrev();
	void Move(ULONG ulIndex);

	bool IsBOF();
	bool IsEOF();
	bool IsOpen();

	bool CanUpdate() const;     // Can Edit/AddNew/Delete be called?
	void ClsEditFlag();
	
	CMyField		Fields(char * szField);
	CMyField 		Fields(UINT	uiIndex );
	
protected:
	int UpdateFieldsCount();

	void			BuildUpdateSQL();
	void			BuildUpdateCondition();
	void			BuildUpdateOpration();

	CMyField *		GetFieldRef(UINT uiIndex);

	bool			Query(const char * szSQL, MYSQL_RES * * res);

	void			GetAllField();
public:
	bool			GetDefauldField(const char* pszTableName);

protected:
	CMyDatabase	*	m_pMyDatabase;

	MYSQL_RES	*	m_Recordset;
	MYSQL_FIELD *	m_Fields;
	MYSQL_ROW		m_Row;

	_int64			m_ulRowsCount;
	_int64			m_ulCursor;			//★ 当INSERT和DELETE后, 要及时更新
	unsigned int 	m_uiFieldsCount;

	char	  		m_szKey[16];
	unsigned int 	m_uiKeyIndex;

	bool	*		m_pbDirty;
	
	bool 			m_bIsOpen;
	bool 			m_bBOF;			//★ 当INSERT和DELETE后, 要及时更新
	bool 			m_bEOF;			//★ 当INSERT和DELETE后, 要及时更新
	bool 			m_bEdit;

	int				m_nEditMode;

	CMyField	*	m_objFields;

	char 			m_szTableName[32];
	char			m_szUpdateCondition[128];

	std::string		m_strUpdateSQL;
	std::string		m_strUpdateOpration;

	bool			m_bCanUpdate;

	bool			m_bDefaultValue;				// paled add, have a default field value.
};

#endif // MYRECORDSET_H