#ifndef SJTU_LCTREE_HPP
#define SJTU_LCTREE_HPP

#include "TBase.hpp"
#include "LCTNode.hpp"

namespace sjtu{

template<class T, class A, class M>
class LCTree : public TBase<T, A, M>{
private:
	LCTNode<T, A, M>* access(LCTNode<T, A, M> *u);
	void add(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void del(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void isSplayRoot(LCTNode<T, A, M> *u);

protected:
	static void rotate(LCTNode<T, A, M> *u, int c);
	static void zig(LCTNode<T, A, M> *u);
	static void zag(LCTNode<T, A, M> *u);
	static LCTNode<T, A, M>* getSplayRoot(LCTNode<T, A, M> *u);
	static void splay(LCTNode<T, A, M> *u);
	void link(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void cut(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void modifyChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v, const T &value);
	T queryChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v);
	void modifySubtree(LCTNode<T, A, M> *u, const T &value);
	void querySubtree(LCTNode<T, A, M> *u);
	LCTNode<T, A, M> * setRoot(LCTNode<T, A, M> *u);

};

#include "source/LCTree.cpp"

template<class T, class A, class M>
void LCTree<T, A, M>::add(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	if (u == nullptr || v == nullptr) return;
	(u -> subtree).insert(AuxNode<T, A, M>(v, rand()));
}

template<class T, class A, class M>
void LCTree<T, A, M>::del(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	if (u == nullptr || v == nullptr) return;
	(u -> subtree).erase(AuxNode<T, A, M>(v, rand()));
}

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
void LCTree<T, A, M>::isSplayRoot(LCTNode<T, A, M> *u) {
	return u->father == nullptr || (u->father->child[0] != u && u->father->child[1] != u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::splay(LCTNode<T, A, M> *u) {
	LCTNode<T, A, M> * uRoot = LCTree<T, A, M>::getSplayRoot(u);
	del(uRoot->father, uRoot);
	
	while (!isSplayRoot(u)) {
		LCTNode<T, A, M> *v = u->father;
		if (isSplayRoot(v)) {
			v->update();
			u->update();
			if (v->child[0] == u) {
				LCTree<T, A, M>::zig(u);
			} else {
				LCTree<T, A, M>::zag(u);
			}
		} else {
			LCTNode<T, A, M> *w = v->father;
			w->update();
			v->update();
			u->update();
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
		if (u->child[1] != nullptr) {
			u->sum -= u->child[1]->sum;
		}
		u->child[1] = v;
		u->sum += v->sum;
		v = u;
		v->update();
	}
	return v;
}

template<class T, class A, class M>
LCTNode<T, A, M> * LCTree<T, A, M>::setRoot(LCTNode<T, A, M> *u) {
	LCTNode<T, A, M> * tmp = LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	LCTNode<T, A, M> *p = u;
	while (p -> child[0] != nullptr) {
		p = p -> child[0];
	}
	tmp->reverse ^= true;
	LCTree<T, A, M>::splay(u);
	return p;
}

template<class T, class A, class M>
void LCTree<T, A, M>::link(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	u->father = v;
	add(v, u);
	LCTree<T, A, M>::access(u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::cut(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	v->child[0]->father = nullptr;
	v->child[0] = nullptr;
	update(v);
}

template<class T, class A, class M>
void LCTree<T, A, M>::modifyChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v, const T &value) { 
	LCTNode<T, A, M> tmp = LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	v->makeTagChain(value);
	LCTree<T, A, M>::setRoot(tmp);
}

template<class T, class A, class M>
T LCTree<T, A, M>::queryChain(LCTNode<T, A, M> *u, LCTNode<T, A, M> *v) {
	LCTNode<T, A, M> tmp = LCTree<T, A, M>::setRoot(u);
	LCTree<T, A, M>::access(v);
	LCTree<T, A, M>::splay(v);
	T ret = v->sumChain;
	LCTree<T, A, M>::setRoot(tmp);
	return ret;
}

template<class T, class A, class M>
void LCTree<T, A, M>::modifySubtree(LCTNode<T, A, M> *u, const T &value) {
	LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	u->makeTagTree(value);
	u->update();
	LCTree<T, A, M>::splay(u);
}

template<class T, class A, class M>
void LCTree<T, A, M>::querySubtree(LCTNode<T, A, M> *u) {
	LCTree<T, A, M>::access(u);
	LCTree<T, A, M>::splay(u);
	return add(u->sumSubtree, u->data);
}

}

#endif
