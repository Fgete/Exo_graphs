#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// ------------ CLASSES ------------
template<class T> class graph_node {
protected:
	int id;
public:
	T data;

	graph_node(const int id, const T data);
	~graph_node();

	void setId(const int id);
	int getId() const;

	void print();
};

template<class T> class graph {
private:
	int getIndexByNodeId(const int id) const;
protected:
	int count;
	vector<graph_node<T>*> nodeTab;
	vector<vector<int>> bows;
public:
	graph();
	graph(graph_node<T>* node);
	~graph();

	int getCount() const;
	int getBow(const int idFrom, const int idTo) const;

	void addNode(graph_node<T>* node);
	void addBow(const int idFrom, const int idTo);

	void printBows();
};

// ------------ FUNCTIONS ------------
template<class T>
inline graph_node<T>::graph_node(const int id, const T data)
{
	this->id = id;
	this->data = data;
}

template<class T>
inline graph_node<T>::~graph_node()
{
}

template<class T>
inline void graph_node<T>::setId(const int id)
{
	this->id = id;
}

template<class T>
inline int graph_node<T>::getId() const
{
	return this->id;
}

template<class T>
inline void graph_node<T>::print()
{
	cout << this->id << " : " << this->data << endl;
}

template<class T>
inline int graph<T>::getIndexByNodeId(const int id) const
{
	for (int i = 0; i < nodeTab.size(); i++)
		if (nodeTab[i]->getId() == id)
			return i;
	return -1;
}

template<class T>
inline graph<T>::graph()
{
	this->count = 0;
}

template<class T>
inline graph<T>::graph(graph_node<T>* node)
{
	this->count = 1;
	this->nodeTab.push_back(node);
	vector<int> v = NULL;
	v = (vector<int>)calloc(1, sizeof(vector<int>));
	this->bows.push_back(v);
	this->bows[0].push_back(0);
}

template<class T>
inline graph<T>::~graph()
{
	/*
	for (int i = 0; i < this->bows.size(); i++)
		free(&this->bows[i]);
	*/
}

template<class T>
inline int graph<T>::getCount() const
{
	return this->count;
}

template<class T>
inline int graph<T>::getBow(const int idFrom, const int idTo) const
{
	return this->bows[idFrom][idTo];
}

template<class T>
inline void graph<T>::addNode(graph_node<T>* node)
{
	this->count++;
	this->nodeTab.push_back(node);

	// vector<int>* v = nullptr;
	// v = (vector<int>*)calloc(1, sizeof(vector<int>));
	// this->bows.push_back(&v);

	// New column for the bows matrix
	vector<int> v;
	this->bows.push_back(v);

	// Grow bows matrix & fill it with default values (0)
	for (int i = 0; i < count; i++) {
		bows[count - 1].push_back(0);
		bows[i].push_back(0);
	}
}

template<class T>
inline void graph<T>::addBow(const int idFrom, const int idTo)
{
	// Return index of idFrom & idTo
	int i = getIndexByNodeId(idFrom);
	int j = getIndexByNodeId(idTo);

	// use indexes to fill bows
	if (i >= 0 && j >= 0)
		bows[i][j] = 1;
}

template<class T>
inline void graph<T>::printBows()
{
	if (bows.size() == 0) {
		cout << "empty matrix" << endl;
		return;
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++)
			cout << bows[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
