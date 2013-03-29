#include <iostream.h>
#include <string.h>

typedef unsigned short USHORT;
typedef unsigned long ULONG;

// ********* Part ***********
//Abstract base class of parts
class Part
{
public:
	virtual Part * clone() const = 0; //must be overridden
	Part():itsPartNumber(1){}
	Part(ULONG partNumber):itsPartNumber(partNumber){}
	virtual ~Part() {}
	ULONG getPartNumber() const { return itsPartNumber; }
	virtual void display() const = 0; //must be overridden
	virtual int getType() const = 0; //must be overridden
	void setPartNumber(ULONG partNum){itsPartNumber = partNum; }
private:
	ULONG itsPartNumber;
};

//implementation of pure virtual function so that derived 
//classes can chain up
void Part::display() const
{
	cout << "In Part::display()\n";
	cout << "\nPart Number: " << itsPartNumber << endl;
}

// ********* Car Part **********
class CarPart : public Part
{
public:
	Part * clone() const;
	CarPart():itsModelYear(02){}
	CarPart(USHORT year, ULONG partNumber);
	
	~CarPart(){}

	virtual void display() const
	{
		cout << "In CarPart::display()\n";
		Part::display();
		cout << "Model year: " << itsModelYear << endl;
		cout << "Exiting CarPart::display()\n";
	}
	void setYear(USHORT year){itsModelYear = year;}	
	int getType() const { return 1; }
private: 
	USHORT itsModelYear;
};

CarPart::CarPart(USHORT year, ULONG partNumber):
	Part(partNumber),
	itsModelYear(year)
	{}

Part * CarPart::clone() const
{
	Part * newPart = new CarPart(itsModelYear, getPartNumber());
	return newPart;
}

// ********* Air Plane Part ***********
class AirPlanePart : public Part
{
public:
	AirPlanePart():itsEngineNumber(1){}
	AirPlanePart(USHORT engineNumber, ULONG partNumber);
	~AirPlanePart(){}

	Part * clone() const;
	virtual void display() const { Part::display();
	cout << "Engine Number: " << itsEngineNumber << endl;	}
	int getType() const { return 2; }
private:
	USHORT itsEngineNumber;
};

AirPlanePart::AirPlanePart(USHORT engineNumber, ULONG partNumber):
	Part(partNumber),	
	itsEngineNumber(engineNumber)
	{}

Part * AirPlanePart::clone() const
{
	Part * newPart = new AirPlanePart(itsEngineNumber,getPartNumber());
	return newPart;
}

// ********* Part Node *********
class PartNode
{
public:
	friend class PartList;
	PartNode(Part*);
	~PartNode();
	
	void setNext(PartNode * aNode) { itsNext = aNode; }
	PartNode * getNext() const;
	Part * getPart() const;
	
	PartNode(const PartNode & rhs);
	PartNode & operator=(const PartNode & rhs);
private:
	Part * itsPart;
	PartNode * itsNext;
};

PartNode::PartNode(Part * pPart):
	itsPart(pPart),
	itsNext(0)
	{}

PartNode::~PartNode()
{
	delete itsPart;
	itsPart = 0;
	delete itsNext;
	itsNext = 0;
}

// Returns null if no next PartNode
PartNode * PartNode::getNext() const
{
	return itsNext;
}

Part * PartNode::getPart() const
{
	if(itsPart)
		return itsPart;
	else
		return NULL;
}


PartNode & PartNode::operator=(const PartNode & rhs)
{
	cout << "this: partNumber= " << getPart()->getPartNumber() << endl;
	if(rhs.getNext())
	{
		cout << "rhs.getNext() != 0" << endl;
		*itsNext = *(rhs.getNext());
	}
	cout << "itsPart: " << itsPart << endl;
	itsPart = rhs.getPart()->clone();
	return *this;
}


PartNode::PartNode(const PartNode & rhs)
{
	if(rhs.getNext())
		*itsNext = *(rhs.getNext());
	*itsPart = *(rhs.getPart()->clone());
}


// *********** Part List *************
class PartList
{
public:
	PartList();
	~PartList();

	PartList(const PartList & rhs);
	PartList & operator=(const PartList & rhs);

	void iterate(void (Part::*pFunc)() const) const;
	Part * find(ULONG & position, ULONG partNumber) const;
	Part * getFirst() const;
	void insert(Part *);
	Part * operator[](ULONG) const;
	ULONG getCount() const { return itsCount; }
	PartNode * getHead() const{ return pHead; }
	static PartList & getGlobalPartList() { return globalPartList; }
private:
	PartNode * pHead;
	ULONG itsCount;
	static PartList globalPartList;
};

PartList PartList::globalPartList;

PartList::PartList():
	pHead(0),
	itsCount(0)
	{}

PartList::~PartList()
{
	delete pHead;
	pHead = 0;
}

PartList::PartList(const PartList & rhs)
{
	itsCount = rhs.getCount();
	*pHead = *(rhs.getHead());
}

PartList & PartList::operator=(const PartList & rhs)
{
	if(this == &rhs)
		return *this;
	itsCount = rhs.getCount();
	*pHead = *rhs.getHead();
	return *this;
}

Part * PartList::getFirst() const 
{
	if(pHead)
		return pHead->itsPart;
	else return NULL;
}

Part * PartList::operator [] (ULONG offset) const
{
	PartNode * pNode = pHead;

	if(!pHead)
		return NULL;

	if(offset > itsCount)
		return NULL;

	for(ULONG i = 0; i < offset; i++)
		pNode = pNode->itsNext;

	return pNode->itsPart;
}

Part * PartList::find(ULONG & position, ULONG partNumber) const
{
	PartNode * pNode = 0;
	for(pNode = pHead, position = 0;
		pNode != NULL;
		pNode = pNode->itsNext, position++)
	{
		if(pNode->itsPart->getPartNumber() == partNumber)
			break;
	}

	if(pNode == NULL)
	{
		return NULL;
	}
	else
		return pNode->itsPart;
}

void PartList::iterate(void (Part::*pFunc)() const) const
{
	if(!pHead)
		return;
	PartNode * pNode = pHead;
	do
	(pNode->itsPart->*pFunc)();
	while(pNode = pNode->itsNext);
}

void PartList::insert(Part * pPart)
{
	PartNode * pNode = new PartNode(pPart);
	PartNode * pCurrent = pHead;
	PartNode * pNext = 0;

	ULONG newNum = pPart->getPartNumber();
	ULONG nextNum = 0;
	itsCount++;

	if(!pHead)
	{
		pHead = pNode;
		return;
	}

	//if new node is smaller than the head
	//it is to be the head
	if(pHead->itsPart->getPartNumber() > newNum)
	{
		pNode->itsNext = pHead;
		pHead = pNode;
	}

	while(1)
	{
		//if there is no next, append the new one
		if (!pCurrent->itsNext)
		{
			pCurrent->itsNext = pNode;
			return;
		}

		//if the new one goes after the current node
		//and before the next node, insert it after the current
		//if not, go to the next node
		pNext = pCurrent->itsNext;
		nextNum = pNext->itsPart->getPartNumber();
		if(newNum < nextNum)
		{
			pCurrent->itsNext = pNode;
			pNode->itsNext = pNext;
			return;
		}
		pCurrent = pNext;
	}
}

// ********** Part Catalog *************
class PartCatalog : private PartList
{
public:
	void insert(Part *);
	ULONG exists(ULONG partNumber);
	Part * get(int partNumber);
	void showAll() { iterate(Part::display); }
};

void PartCatalog::insert(Part * newPart)
{
	ULONG partNumber = newPart->getPartNumber();
	ULONG offset;

	if(!find(offset, partNumber))
		PartList::insert(newPart);
	else
	{
		cout << partNumber << " was the ";
		switch(offset)
		{
			case 0: cout << "first "; break;
			case 1: cout << "second "; break;
			case 2: cout << "third "; break;
			default: cout << offset+1 << "th ";
		}
		cout << "entry. Rejected!\n";
	}
}

ULONG PartCatalog::exists(ULONG partNumber)
{
	ULONG offset;
	find(offset, partNumber);
	return offset;
}

Part * PartCatalog::get(int partNumber)
{
	ULONG offset;
	Part * thePart = find(offset, partNumber);
	return thePart;
}

void main()
{
	PartCatalog pc;
	Part * pPart = 0;
	ULONG partNumber;
	USHORT value;
	ULONG choice;

	while(1)
	{
		cout << "(0)Quit (1)Car (2)Plane: ";
		cin >> choice;
		if(!choice)
			break;

		cout << "New part number: " ;
		cin >> partNumber;
		if(choice == 1)
		{
			cout << "Model year: ";
			cin >> value;
			pPart = new CarPart(value, partNumber);
		}
		else
		{
			cout << "Engine number: ";
			cin >> value;
			pPart = new AirPlanePart(value, partNumber);
		}
		pc.insert(pPart);
	}
	pc.showAll();
}






