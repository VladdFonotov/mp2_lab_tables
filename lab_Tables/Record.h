#pragma once

#ifndef _record_h
#define _record_h

#include <iostream>
#include <string>

using namespace std;

typedef int TKey;
typedef string TValue;

class TTabRecord {

protected:
	TKey Key;
	TValue pValue;
public:
	
	TTabRecord(TKey k = 0, TValue pVal = "0") { Key = k; pValue = pVal; }
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void SetValue(TValue p) { pValue = p; }
	TValue GetValue(void) { return pValue; }
	TTabRecord& operator=(TTabRecord& tr) {
		Key = tr.Key;
		pValue = tr.pValue;
		return *this;
	}
	virtual void Print(ostream& os) { os << Key << " " << pValue; }

	virtual int operator==(const TTabRecord& tr) { return Key == tr.Key; }
	virtual int operator!=(const TTabRecord& tr) { return Key != tr.Key; }
	virtual int operator< (const TTabRecord& tr) { return Key > tr.Key; }
	virtual int operator=(const TTabRecord& tr) { return Key = tr.Key; }
	virtual int operator> (const TTabRecord& tr) { return Key < tr.Key; }

	friend class TArrayTable;
	friend class TScanTable;
	friend class TSortTable;
	friend class TTreeNode;
	friend class TTreeTable;
	friend class TArrayHashTable;
	friend class HashTable;
};

#endif