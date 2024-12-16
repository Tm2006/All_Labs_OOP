﻿#pragma once

// Реализация двунаправленного списка
template <typename T>
class List {
private:
	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
	};

	Node* _head;
	Node* _tail;
	size_t _size;

public:
	class Iterator {
	private:
		Node* _node;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		Iterator(Node* node) : _node(node) {}

		T& operator*() const {
			return _node->data;
		}

		T* operator->() const {
			return &_node->data;
		}

		Iterator& operator++() {
			_node = _node->next;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			_node = _node->next;
			return temp;
		}

		bool operator==(const Iterator& other) const {
			return _node == other._node;
		}

		bool operator!=(const Iterator& other) const {
			return _node != other._node;
		}
	};

	Iterator begin() const {
		return Iterator(_head);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	class ReverseIterator {
	private:
		Node* _node;

	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		ReverseIterator(Node* node) : _node(node) {}

		T& operator*() const {
			return _node->data;
		}

		T* operator->() const {
			return &_node->data;
		}

		ReverseIterator& operator++() {
			_node = _node->prev;
			return *this;
		}

		ReverseIterator operator++(int) {
			ReverseIterator temp = *this;
			_node = _node->prev;
			return temp;
		}

		bool operator==(const ReverseIterator& other) const {
			return _node == other._node;
		}

		bool operator!=(const ReverseIterator& other) const {
			return _node != other._node;
		}
	};

	ReverseIterator rbegin() const {
		return ReverseIterator(_tail);
	}

	ReverseIterator rend() const {
		return ReverseIterator(nullptr);
	}


public:
	List() : _head(nullptr), _tail(nullptr), _size(0) {}

	// Конструктор от initializer_list
	List(std::initializer_list<T> initList) : List()  {
		for (const auto& value : initList) {
			push_back(value);
		}
	}

	List(const List& other) : List() {
		for (auto i = other._head; i != nullptr; i = i->next) {
			push_back(i->data);
		}
	}

	List(List&& other) noexcept : List() {
		other.swap(*this);
	}

	List& operator=(const List& other) {
		List(other).swap(*this);
		return *this;
	}

	List& operator=(List&& other) noexcept {
		List(std::move(other)).swap(*this);
		return *this;
	}

	~List() {
		clear();
	}

	void push_back(const T& value) {
		Node* newNode = new Node(value);
		if (_tail) {
			_tail->next = newNode;
			newNode->prev = _tail;
			_tail = newNode;
		}
		else {
			_head = _tail = newNode;
		}
		++_size;
	}

	void pop_back() {
		if (!_tail) 
			return;
		
		Node* temp = _tail;
		
		_tail = _tail->prev;
		
		if (_tail) 
			_tail->next = nullptr;
		else 
			_head = nullptr;
		
		delete temp;
		
		--_size;
	}

	T& back() const {
		if (!_tail)
			throw std::out_of_range("List is empty");
		return _tail->data;
	}

	bool empty() const {
		return _size == 0;
	}

	size_t size() const {
		return _size;
	}

	void clear() {
		while (_head) {
			pop_back();
		}
	}

	void swap(List& other) {
		std::swap(_head, other._head);
		std::swap(_size, other._size);
		std::swap(_tail, other._tail);
	}
};