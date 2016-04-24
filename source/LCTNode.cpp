#ifdef SJTU_LCTNODE_HPP

#ifndef SJTU_LCTNODE_CPP
#define SJTU_LCTNODE_CPP

template<class T, class A, class M>
void LCTNode<T, A, M>::makeTagChain(const T &value) {
	if (!haveTagChain) {
		tagChain = value;
		haveTagChain = true;
	} else {
		tagChain = add(tagChain, value);
	}
	data = add(data, value);
	sum = add(sum, mult(size, value));
}

template<class T, class A, class M>
void LCTNode<T, A, M>::makeTagTree(const T &value) {
	if (!haveTagTree) {
		tagTree = value;
		haveTagTree = true;
	} else {
		tagTree = add(tagTree, value);
	}
	data = add(data, value);
	sum = add(sum, mult(subtree.getSize() + 1, value));
	subtree.root.makeTagTree(value);
}

template<class T, class A, class M>
void LCTNode<T, A, M>::pushTagChain() {
	if (reverse) {
		std::swap(child[0], child[1]);
		if (child[0] != nullptr) {
			child[0] -> reverse ^= 1;
		}
		if (child[1] != nullptr) {
			child[1] -> reverse ^= 1;
		}
		reverse = false;
	}
	if (haveTagChain) {
		if (child[0] != nullptr) {
			child[0] -> makeTagChain(tagChain);
		}
		if (child[1] != nullptr) {
			child[1] -> makeTagChain(tagChain);
		}
		haveTagChain = false;
	}
}

template<class T, class A, class M>
void LCTNode<T, A, M>::pushTagTree() {
	if (haveTagTree) {
		subtree.root -> makeTagChain(tagTree);
		if (child[1] != nullptr) {
			child[1] -> makeTagTree(tagTree);
		}
		haveTagTree = false;
	}
}

template<class T, class A, class M>
void LCTNode<T, A, M>::update() {
	size = 1;
	sum = data;
	if (child[0] != nullptr) {
		size += child[0] -> size;
		sum = add(sum, data);
	}
	if (child[1] != nullptr) {
		size += child[1] -> size;
		sum = add(sum, data);
	}
}

#endif

#endif
