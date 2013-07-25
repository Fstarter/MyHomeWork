#include <iostream>
using namespace std;


class Iterator;
class Reiterator;
class List;

class Element
{
private:
	Element* next;
	int value;
public:
	friend class Iterator;
    friend class Reiterator;
	friend List;

	Element()
	{
		this->next = NULL;
		this->value = 0;
	}
	void SetNext(Element* n)
	{
		this->next = n;
	}
	Element* GetNext()
	{
		return this->next;
	}
	void SetValue(int val)
	{
		this->value = val;
	}
	int GetValue()
	{
		return this->value;
	}
	~Element(void){}
};

class Iterator
{
private:
	Element* elem;
public:
	Iterator(void):elem(NULL){}
	Iterator(Element* el): elem(el){}
	~Iterator(void){}
	Iterator operator ++(int)
	{
		this->elem = this->elem->GetNext();
		return *this;
	}

	int operator*()
	{
		return this->elem->GetValue();
	}
	bool operator != (Iterator& it)
	{
		return this->elem != it.elem;
	}
};

class Reiterator
{
	private:
	Element* elem;
public:
	Reiterator(void):elem(NULL){}
	Reiterator(Element* el): elem(el){}
	~Reiterator(void){}

	Reiterator operator ++(int)
	{
		this->elem = this->elem->GetNext();
		return *this;
	}

	int operator*()
	{
		return this->elem->GetValue();
	}
	bool operator != (Reiterator& it)
	{
		return this->elem != it.elem;
	}
};

class List
{
private:
	
public:

	friend class Reiterator;

Element* head;
	int amount;
	List(void)
	{
		SetAmount(0);
	}
	void SetHead(Element* el)
	{
		this->head = el;
	}
	Element* GetHead()
	{
		return this->head;
	}
	void SetAmount(unsigned int count)
	{
		this->amount = count;
	}
	unsigned int GetAmount()
	{
		return this->amount;
	}

	void Push(Element* el)
	{
		if(GetAmount() == 0)
		{
			SetHead(el);
		}
		else
		{
	        Element* tmp = this->head;
			for(int i = 0; i < GetAmount() - 1; i++)
			{
				tmp = tmp->GetNext();
			}
			tmp->SetNext(el);
		}
		int s = GetAmount();
		SetAmount(++s);
	}

	void Print()
	{
		if(GetAmount() > 0)
		{
			Element* tmp = this->head;
			for(int i = 0; i < GetAmount(); i++)
			{
				cout << "[" << i << "] - " << tmp->GetValue() << endl;
				tmp = tmp->GetNext();
			}
		}
	}

	void ReversePrint(Element* el)
	{
		if(el == NULL)
		{
			return;
		}
		ReversePrint(el->GetNext());
		cout << el->GetValue() << " ";
	}

	void Reverse(Element* el)
	{
		if(el->GetNext() == NULL)
		{
			this->head = el;
			return;
		}
		Reverse(el->GetNext());
		Element*q = el->GetNext();
		q->SetNext(el);
		el->SetNext(NULL);
	}
	
	int operator[](unsigned int idx)
	{
		if(idx > GetAmount())
		{
			cout << "Error.\n";
		}
		else
		{
			Element* tmp = this->head;
			for(int i = 0; i < idx; i++)
			{
				tmp = tmp->GetNext();
			}
			return tmp->GetValue();
		}
	}

	Iterator begin()
	{
		return Iterator(GetHead());
	}
	Iterator end()
	{
		return Iterator(0);
	}

	Reiterator rbegin()
	{
		Reverse(GetHead());
		return Reiterator(GetHead());
	}
	Reiterator rend()
	{
		return Reiterator(0);
	}

};




int main()
{
	List list;
	Element one;
	Element* el;
	int value = 0, count = 0;
	cout << "Enter value of head: ";
	cin >> value;
	list.SetHead(&one);
	one.SetValue(value);
	list.Push(&one);
	cout << "Enter amount of elements: ";
	cin >> count;
	el = new Element[count];
	for(int i = 0; i < count; i++)
	{
		cout << "Enter value: ";
		cin >> value;
		el[i].SetValue(value);
		list.Push(&el[i]);
	}
	list.Print();

	for(Iterator i = list.begin(); i != list.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	for(Reiterator i = list.rbegin(); i != list.rend(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
	
	
	return 0;
}