#ifndef SJTU_TNODE_HPP
#define SJTU_TNODE_HPP

#include "TBase.hpp"

namespace sjtu{

template<class T, class A, class M>
class TNode{
protected:
	T data, sum;
	size_t size;

	static A add;
	static M mult;

public:
	TNode();
	virtual ~TNode();

};

template<class T, class A, class M>
A TNode<T, A, M>::add;

template<class T, class A, class M>
M TNode<T, A, M>::mult;

#include "source/TNode.cpp"

}

#endif
