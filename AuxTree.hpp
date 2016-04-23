#ifndef SJTU_AUXTREE_HPP
#define SJTU_AUXTREE_HPP

#include "AuxNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxTree{
private:
	
	AuxNode<T, A, M> *root;
	int size;
	void LL(AuxNode<T, A, M>* &t);
	void RR(AuxNode<T, A, M>* &t);
	AuxNode* Treap_find(const int &key, AuxNode<T, A, M>* t);
	void Treap_Insert(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t);
	void Treap_Delete(const AuxNode<T, A, M> &rhs, AuxNode<T, A, M>* &t);
	
public:
	
	AuxTree() : root(NULL), size(0) {}
	AuxNode* find(const AuxNode<T, A, M> &rhs);
	void insert(const AuxNode<T, A, M> &rhs);
	void erase(const AuxNode<T, A, M> &rhs);
	
};

#include "source/AuxTree.cpp"

}

#endif
