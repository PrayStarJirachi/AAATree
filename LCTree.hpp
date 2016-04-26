#ifndef SJTU_LCTREE_HPP
#define SJTU_LCTREE_HPP

#include "LCTNode.hpp"
#include "TBase.hpp"

namespace sjtu{

template<class T, class A, class M>
class LCTree : public TBase<T, A, M>{
private:

protected:
	LCTNode<T, A, M>* access(LCTNode<T, A, M> *u);
	void setRoot(LCTNode<T, A, M> *u);

};

#include "source/LCTree.cpp"

/*

add(u, v) {
	add v into aaaTree of u;
}

del(u, v) {
	delete v in aaaTree of u;
}

*/

template<class T, class A, class M>
void LCTree<T, A, M>::rotate(LCTNode<T, A, M> *u, int c) {
	LCTNode<T, A, M> *v = u->father;
	v->child[c ^ 1] = u->child[c];
	if (u->child[c] != nullptr) {
		u->child[c]->father = v;
	}
	u->father = v->father;
	if (v->father->child[0] == v) {
		u->father->child[0] = u;
	} else if (v->father->child[1] == v) {
		u->father->child[1] = u;
	}
	v->father = u;
	u->child[c] = v;
}


template<class T, class A, class M>
void LCTree<T, A, M>::zig(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::rotate(u, 0);
}

template<class T, class A, class M>
void LCTree<T, A, M>::zag(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::rotate(u, 1);
}

template<class T, class A, class M>
LCTNode<T, A, M>* LCTree<T, A, M>::getSplayRoot(LCTNode<T, A, M> *u) {
	while (!LCTree<T, A, M>::isSplayRoot(u)) {
		u = u->father;
	}
	return u;
}

template<class T, class A, class M>
void LCTree<T, A, M>::splay(LCTNode<T, A, M> *u) {
	LCTNode<T, A, M> uRoot = LCTree<T, A, M>::getSplayRoot(u);
	del(uRoot->father, uRoot);
	
	u->clearTag();
	while (!isSplayRoot(u)) {
		LCTNode<T, A, M> *v = u->father;
		if (isSplayRoot(v)) {
			v->clearTag();
			u->clearTag();
			if (v->child[0] == u) {
				LCTree<T, A, M>::zig(u);
			} else {
				LCTree<T, A, M>::zag(u);
			}
		} else {
			LCTNode<T, A, M> *w = v->father;
			w->clearTag();
			v->clearTag();
			u->clearTag();
			if (w->child[0] == v) {
				if (v->child[0] == u) {
					LCTree<T, A, M>::zig(v);
					LCTree<T, A, M>::zig(u);
				} else {
					LCTree<T, A, M>::zag(u);
					LCTree<T, A, M>::zig(u);
				}
			} else {
				if (v->child[1] == u) {
					LCTree<T, A, M>::zag(v);
					LCTree<T, A, M>::zag(u);
				} else {
					LCTree<T, A, M>::zig(u);
					LCTree<T, A, M>::zag(u);
				}
			}
		}
	}
	LCTree<T, A, M>::update(u);
	add(u->father, u);
}

template<class T, class A, class M>
LCTNode<T, A, M>* LCTree<T, A, M>::access(LCTNode<T, A, M> *u) {
	LCTNode<T, A, M>* v = nullptr;
	for ( ; u != nullptr; u = u->father) {
		LCTree<T, A, M>::splay(u);
		LCTree<T, A, M>::del(u, v);
		LCTree<T, A, M>::add(u, u->child[1]);
		
		u->child[1] = v;
		
		v = u;
		v->update();
	}
	return v;
}

template<class T, class A, class M>
void LCTree<T, A, M>::setRoot(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::access(u)->reverse ^= true;
	LCTree<T, A, M>::splay(u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::link(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	for (LCTNode<T, A, M> *vv = v; vv != nullptr; vv = vv->father) {
		vv->sum += u->sum;
	}
	u->father = v;
	LCTree<T, A, M>::access(u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::cut(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	v->child[0]->father = nullptr;
	v->child[0] = nullptr;
	v->update();
}

template<class T, class A, class B>
void LCTree<T, A, M>::modifyChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v, T value) {
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	v->makeTagChain(value);
	v->clearTag();
}

template<class T, class A, class B>
T LCTree<T, A, M>::queryChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	return v->sumChain;
}

template<class T, class A, class B>
void LCTree<T, A, M>::modifySubtree(LCTNode<T, A, M> *u, T value) {
	LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	u->makeTagSubtree(value);
	u->clearTag();
	u->update();
	LCTree<T, A, M>::splay(u);
}

template<class T, class A, class B>
void LCTree<T, A, M>::querySubtree(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	return u->sumSubtree;
}

}

#endif
