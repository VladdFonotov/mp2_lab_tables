#pragma once
#ifndef _arraytable_h
#define _arraytable_h

#include "Table.h"

#define TabMaxSize 25

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {

protected:
	TTabRecord *pRecs; // память для записей таблицы
	int TabSize; //макс. возм. кол-во записей
	int CurrPos; //номер текущей записи(нумерация от 0)

public:
	TArrayTable() {
		TabSize = -1;
		pRecs = NULL;
		CurrPos = -1;
	};
	TArrayTable(int Size = TabMaxSize) {
		pRecs = new TTabRecord[Size];
		TabSize = Size;
		DataCount = CurrPos = 0;
	}
	~TArrayTable() {
		delete[] pRecs;
	}

	//информационные методы
	virtual bool IsFull() const {
		return DataCount >= TabSize;
	}

	int GetTabSize() const {
		return TabSize;
	}

	//доступ
	virtual TKey GetKey(void) const {
		return GetKey(CURRENT_POS);
	}
	virtual TValue GetValue(void) const {
		return GetValue(CURRENT_POS);
	}

	virtual TKey GetKey(TDataPos mode) const;

	virtual TValue GetValue(TDataPos mode) const;


	//навигация
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);
	virtual int SetCurrentPos(int pos);
	int GetCurrentPos(void) const{
		return CurrPos;
	}
	
	friend class TSortTable;
};
#endif