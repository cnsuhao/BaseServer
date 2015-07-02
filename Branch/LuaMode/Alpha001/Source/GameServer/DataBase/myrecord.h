// myrecords.h 用于分解出myrecordset.h中的单个记录。
// 仙剑修，2002.9.12
//////////////////////////////////////////////////////////////////////

#ifndef	MYRECORD_H
#define	MYRECORD_H

class CCriticalSection;
class CMyDatabase;

class CMyRecord : public IRecord
{
public: // interface
	virtual IRecord*	CreateNewRecord(DB_KEY idNewKey = NEWKEY_NONE);
	virtual	void		Release() { delete this; }

	virtual DB_KEY		InsertRecord(INT nType = DBUPDATE_SYNC);
	virtual bool		UpdateRecord(INT nType = DBUPDATE_ASYNC);
	virtual bool		DeleteRecord(INT nType = DBUPDATE_SYNC);

	virtual bool		IsString	(int idx);
	virtual int			GetFieldCount(void){return m_uiFieldsCount;}
	virtual void		ClearUpdateFlags	()	{ ClsEditFlag(); }
	virtual DB_KEY		GetKey		();
	
public:
	virtual	I64			GetInt64	(int idx);
	virtual I64			GetInt64	(const char* szField);
	virtual void		SetInt64	(int idx, I64 i64Data);
	virtual void		SetInt64	(const char* szField,	I64 i64Data);
	virtual double		GetDouble	(int idx);
	virtual int			GetInt		(int idx);
	virtual int     	GetInt		(const char* szField);
	virtual	const char*	GetStr		(const char* szField);
	virtual const char*	GetStr		(int idx);
	virtual void		SetInt		(const char* szField, int nData);
	virtual void		SetInt		(int idx, int nData);
	virtual void		SetStr		(int idx, const char* szData, int nSize);
	virtual	void		SetStr		(const char* szField,const char* szData, int nSize);


public: // Constructor
	CMyRecord(CMyDatabase  * pMyDatabase);
	virtual ~CMyRecord();

public:
	static CMyRecord* CreateNew(CMyDatabase  *pMyDatabase);

public:
	MYHEAP_DECLARATION(s_heap)

public:
	enum { modeEdit, modeAddNew, modeDelete };

	virtual bool Open( CMyRecordset* pRes, DB_KEY idNewKey = 0);
	virtual bool Spawn(CMyRecord  *pMyRecord, DB_KEY idNewKey = 0);
	virtual void Close();

	int FieldsCount();

	void AddNew();
	void Edit();
	bool Update();
	void Delete();

	bool IsOpen();

	bool CanUpdate() const;     // Can Edit/AddNew/Delete be called?
	void ClsEditFlag();

	void SetDatabase(CMyDatabase* pDb) { m_pMyDatabase = pDb; }
	bool SetTableName(const char* szName, DB_KEY idNewKey = 0);

	CMyField		Fields(char * szField);
	CMyField 		Fields(UINT	uiIndex );

	CMyDatabase	*	m_pMyDatabase;

protected: // inside function
	int				UpdateFieldsCount();

	void			BuildUpdateSQL();
	void			BuildUpdateCondition();
	void			BuildUpdateOpration();

	CMyField *		GetFieldRef(UINT uiIndex);

	bool			Query(const char * szSQL, MYSQL_RES * * res);

	void			GetFieldValue(UINT uiIndex);
	bool			FormatField(char* szFormat, const CMyField& objField);

protected:
	MYSQL_FIELD*	m_Fields;				//? COPY的结构，table、def未复制，不可用

	unsigned int 	m_uiFieldsCount;

	char	  		m_szKey[16];
	unsigned int 	m_uiKeyIndex;
	char		 	m_szKeyData[96];		//paled add 可能有点大

	bool	*		m_pbDirty;

	bool 			m_bEdit;
	bool 			m_bIsOpen;

	int				m_nEditMode;

	CMyField	*	m_objFields;

	char 			m_szTableName[32];
	char			m_szUpdateCondition[128];

	std::string		m_strUpdateSQL;
	std::string		m_strUpdateOpration;

	bool			m_bCanUpdate;
};

#endif // MYRECORD_H