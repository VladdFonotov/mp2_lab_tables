#include"ArrayHash.h"
#include"HashTable.h"
#include"Record.h"

TArrayHashTable::TArrayHashTable(int Size, int Step) : TabSize(Size), HashStep(Step) {
	pRecs = new TTabRecord[TabSize];
	Empty = TTabRecord(-1);
	Mark = TTabRecord(-2);
	for (int i = 0; i < TabSize; i++) {
		pRecs[i] = Empty;
	}
}

TArrayHashTable::~TArrayHashTable() {
	delete[] pRecs;
}

bool TArrayHashTable::FindRecord(TKey k) {
	bool result = false;
	Efficiency = 0;
	FreePos = -1;
	CurrPos = HashFunck(k) % TabSize;
	for (int i = 0; i < TabSize; i++) {
		Efficiency++;
		if (pRecs[CurrPos] == Empty) {
			break;
		}
		else if (pRecs[CurrPos] == Mark) {
			if (FreePos == -1) {
				FreePos = CurrPos;
			}
		}
		else if (pRecs[CurrPos].GetKey() == k) {
			result = true;
			break;
		}
		CurrPos = GetNextPos(CurrPos);
	}
	return result;
}

int TArrayHashTable::InsRecord(TKey k, TValue pVal) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		if (FindRecord(k)) {
			return TabRecDbl;
		}
		else {
			if (FreePos != -1) {
				CurrPos = FreePos;
			}
			pRecs[CurrPos] = TTabRecord(k);
			pRecs[CurrPos].SetValue(pVal);
			DataCount++;
			return TabOK;
		}
	}
}

int TArrayHashTable::DelRecord(TKey k) {
	bool temp = FindRecord(k);
	if (temp == false) {
		cerr << " TabNoRec " << endl;
		return TabNoRec;
	}
	else {
		pRecs[CurrPos] = Mark;
		DataCount--;
		return TabOK;
	}
}

int TArrayHashTable::Reset(void) {
	CurrPos = 0;
	while (CurrPos < TabSize) {
		if ((pRecs[CurrPos] != Empty) && (pRecs[CurrPos] != Mark))
			break;
		else
			CurrPos++;
	}
	return IsTabEnded();
}

int TArrayHashTable::IsTabEnded(void) const {
	return CurrPos >= TabSize;
}

int TArrayHashTable::GoNext(void) {
	if (!IsTabEnded())
	{
		while (++CurrPos < TabSize)
			if ((pRecs[CurrPos] != Empty) && (pRecs[CurrPos] != Mark))
				break;
	}
	return IsTabEnded();
}

TKey TArrayHashTable::GetKey(void) const {
	return pRecs[CurrPos].GetKey();
}

TValue TArrayHashTable::GetValue(void) const {
	return  pRecs[CurrPos].GetValue();
}