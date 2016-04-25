#ifdef SJTU_AUXNODE_HPP

#ifndef SJTU_AUXNODE_CPP
#define SJTU_AUXNODE_CPP

template<class T, class A, class M>
void AuxNode<T, A, M>::makeTagTree(const T &value) {
	if (!haveTagTree) {
		tagTree = value;
		haveTagTree = true;
	} else {
		tagTree = add(tagTree, value);
	}
	data -> makeTagTree(value);
	sum = add(sum, mult(size, value));
}

template<class T, class A, class M>
void AuxNode<T, A, M>::pushTagTree() {
	if (haveTagTree) {
		haveTagTree = false;
		if (child[0] != nullptr) {
			child[0] -> makeDelta(tagTree);
		}
		if (child[1] != nullptr) {
			child[1] -> makeDelta(tagTree);
		}
	}
}

template<class T, class A, class M>
void AuxNode<T, A, M>::update() {
	size = 1;
	sum = data -> sumTree;
	if (child[0] != nullptr) {
		size += child[0] -> size;
		sum = add(sum, child[0] -> sum);
	}
	if (child[1] != nullptr) {
		size += child[1] -> size;
		sum = add(sum, child[1] -> sum);
	}
}

#endif

#endif
