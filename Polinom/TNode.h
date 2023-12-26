#pragma once

template<class T>
class TNode
{
public:
	T value;
	TNode* pNext;
	TNode() {
		value = T();
		this->pNext = nullptr;
	}
	TNode(const T& val) {
		this->value = val;
		this->pNext = nullptr;
	}
	TNode(const TNode<T>& node) {
		this->value = node.value;
		this->pNext = node.pNext;
	}
};