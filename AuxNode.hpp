#ifndef SJTU_AUXNODE_HPP
#define SJTU_AUXNODE_HPP

#include "TNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class AuxNode : TNode<T, A, M>{
private:
	T tagTree;
	bool haveTagTree;
	AuxNode *child[2], *father;
	void makeDelta(const T &value);

public:
	void pushdown();
	void update();

};

#include "source/AuxNode.cpp"

}

#endif
