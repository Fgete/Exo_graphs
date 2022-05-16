#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;


// ------------ CLASSES ------------
template<class T> class lifo_element {
protected:
	T value;

public:
	lifo_element* p_next;

	lifo_element(const T& value);
	~lifo_element();

	void setValue(const T& value);
	T getValue() const;
	void print() const;
};

template<class T> class fifo_element {
protected:
	T value;

public:
	fifo_element* p_prev;

	fifo_element(const T& value);
	~fifo_element();

	void setValue(const T& value);
	T getValue() const;
	void print() const;
};

template<class T> class list_element {
protected:
	T value;

public:
	list_element* p_next;
	list_element* p_prev;

	list_element(const T& value);
	~list_element();

	void setValue(const T& value);
	T getValue() const;
	void print() const;
};

template<class T> class lifo {
protected:
	int length;

public:
	lifo_element<T>* head;

	lifo();
	lifo(lifo_element<T>* value);
	~lifo();

	void addValue(lifo_element<T>* value);
	T shiftValue();
	int getLength() const;
	void print() const;
};

template<class T> class fifo {
protected:
	int length;

public:
	fifo_element<T>* tail;

	fifo();
	fifo(fifo_element<T>* value);
	~fifo();

	void addValue(fifo_element<T>* value);
	T popValue();
	int getLength() const;
	void print() const;
};

template<class T> class list {
protected:
	int length;

public:
	list_element<T>* tail;
	list_element<T>* head;

	list();
	list(list_element<T>* value);
	~list();

	void addHeadValue(list_element<T>* value);
	void addTailValue(list_element<T>* value);
	T shiftValue();
	T popValue();
	int getLength() const;
	void print() const;
};


// ------------ FUNCTIONS ------------
template<class T>
inline lifo_element<T>::lifo_element(const T& value)
{
	this->value = value;
	this->p_next = nullptr;
}

template<class T>
inline lifo_element<T>::~lifo_element()
{
}

template<class T>
inline void lifo_element<T>::setValue(const T& value)
{
	this->value = value;
}

template<class T>
inline T lifo_element<T>::getValue() const
{
	return this->value;
}

template<class T>
inline void lifo_element<T>::print() const
{
	cout << "value : " << this->value << endl;
}

template<class T>
inline lifo<T>::lifo()
{
	this->head = nullptr;
	this->length = 0;
}

template<class T>
inline lifo<T>::lifo(lifo_element<T>* value)
{
	this->head = value;
	this->length = 1;
}

template<class T>
inline lifo<T>::~lifo()
{
}

template<class T>
inline void lifo<T>::addValue(lifo_element<T>* value)
{
	value->p_next = this->head;
	this->head = value;
	this->length++;
}

template<class T>
inline T lifo<T>::shiftValue()
{
	if (this->length == 0) return NULL;
	lifo_element* shift_elem = this->head;
	this->head = shift_elem->p_next;
	this->length--;
	return shift_elem;
}

template<class T>
inline int lifo<T>::getLength() const
{
	return this->length;
}

template<class T>
inline void lifo<T>::print() const
{
	if (this->length > 0) {
		lifo_element<T>* current = this->head;

		while (current->p_next != nullptr) {
			cout << current->getValue() << endl;
			current = current->p_next;
		}
		cout << current->getValue() << endl << endl;

	} else {
		cout << "empty list" << endl << endl;
	}
}

template<class T>
inline fifo_element<T>::fifo_element(const T& value)
{
	this->value = value;
	this->p_prev = nullptr;
}

template<class T>
inline fifo_element<T>::~fifo_element()
{
}

template<class T>
inline void fifo_element<T>::setValue(const T& value)
{
	this->value = value;
}

template<class T>
inline T fifo_element<T>::getValue() const
{
	return this->value;
}

template<class T>
inline void fifo_element<T>::print() const
{
	cout << "value : " << this->value << endl;
}

template<class T>
inline fifo<T>::fifo()
{
	this->tail = nullptr;
	this->length = 0;
}

template<class T>
inline fifo<T>::fifo(fifo_element<T>* value)
{
	this->tail = value;
	this->length = 1;
}

template<class T>
inline fifo<T>::~fifo()
{
}

template<class T>
inline void fifo<T>::addValue(fifo_element<T>* value)
{
	if (this->length > 0) {
		fifo_element<T>* current = this->tail;
		while (current->p_prev != nullptr)
			current = current->p_prev;
		current->p_prev = value;
	}
	else 
		this->tail = value;
	
	this->length++;
}

template<class T>
inline T fifo<T>::popValue()
{
	if (this->length == 0) return NULL;
	fifo_element<T>* pop_elem = this->tail;
	this->tail = pop_elem->p_prev;
	this->tail = nullptr;
	return pop_elem->value;
}

template<class T>
inline int fifo<T>::getLength() const
{
	return this->length;
}

template<class T>
inline void fifo<T>::print() const
{
	if (this->length > 0) {
		fifo_element<T>* current = this->tail;

		while (current->p_prev != nullptr) {
			cout << current->getValue() << endl;
			current = current->p_prev;
		}
		cout << current->getValue() << endl << endl;

	}
	else {
		cout << "empty list" << endl << endl;
	}
}

template<class T>
inline list_element<T>::list_element(const T& value)
{
	this->value = value;
	this->p_next = nullptr;
	this->p_prev = nullptr;
}

template<class T>
inline list_element<T>::~list_element()
{
}

template<class T>
inline void list_element<T>::setValue(const T& value)
{
	this->value = value;
}

template<class T>
inline T list_element<T>::getValue() const
{
	return this->value;
}

template<class T>
inline void list_element<T>::print() const
{
	cout << "value : " << this->value << endl;
}

template<class T>
inline list<T>::list()
{
	this->length = 0;
	this->head = nullptr;
	this->tail= nullptr;
}

template<class T>
inline list<T>::list(list_element<T>* value)
{
	this->length = 1;
	this->head = value;
	this->tail = value;
}

template<class T>
inline list<T>::~list()
{
}

template<class T>
inline void list<T>::addHeadValue(list_element<T>* value)
{
	if (this->length > 0) {
		this->head->p_prev = value;
		value->p_next = this->head;
		this->head = value;
	}
	else {
		this->head = value;
		this->tail = value;
	}
	this->length++;
}

template<class T>
inline void list<T>::addTailValue(list_element<T>* value)
{
	if (this->length > 0) {
		this->tail->p_next = value;
		value->p_prev = this->tail;
		this->tail = value;
	}
	else {
		this->head = value;
		this->tail = value;
	}
	this->length++;
}

template<class T>
inline T list<T>::shiftValue()
{
	if (this->length == 0) return NULL;
	list_element<T>* shift_elem = this->head;
	this->head = shift_elem->p_next;
	if (this->head != nullptr)
		this->head->p_prev = nullptr;
	this->length--;
	return shift_elem->getValue();
}

template<class T>
inline T list<T>::popValue()
{
	if (this->length == 0) return NULL;
	list_element<T>* pop_elem = this->tail;
	this->tail = pop_elem->p_prev;
	if (this->tail != nullptr)
		this->tail->p_next = nullptr;
	this->length--;
	return pop_elem->getValue();
}

template<class T>
inline int list<T>::getLength() const
{
	return this->length;
}

template<class T>
inline void list<T>::print() const
{
	if (this->length > 0) {
		list_element<T>* current = this->head;

		while (current->p_next != nullptr) {
			cout << current->getValue() << endl;
			current = current->p_next;
		}
		cout << current->getValue() << endl << endl;
	}
	else
		cout << "empty list" << endl << endl;
}
