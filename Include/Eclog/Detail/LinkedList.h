// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_LINKEDLIST_H_
#define ECLOG_CPP_DETAIL_LINKEDLIST_H_

#include <Eclog/Detail/Utility.h>
#include <Eclog/Detail/NonCopyable.h>

#include <stddef.h> // size_t

namespace vallest {
namespace eclog {
namespace detail {

	template<typename Node, typename Traits>
	class LinkedList : private NonCopyable {
	public:
		LinkedList() : size_(0)
		{
			setPrev(&head_, &head_);
			setNext(&head_, &head_);
		}

		void clear()
		{
			if (size_ != 0)
			{
				setPrev(&head_, &head_);
				setNext(&head_, &head_);

				size_ = 0;
			}
		}

		bool empty() const
		{
			return (size_ == 0);
		}

		size_t size() const
		{
			return size_;
		}

		Node* begin()
		{
			return getNext(&head_);
		}

		const Node* begin() const
		{
			return getNext(&head_);
		}

		Node* end()
		{
			return &head_;
		}

		const Node* end() const
		{
			return &head_;
		}

		Node* front()
		{
			return getNext(&head_);
		}

		const Node* front() const
		{
			return getNext(&head_);
		}

		Node* back()
		{
			return getPrev(&head_);
		}

		const Node* back() const
		{
			return getPrev(&head_);
		}

		void pushBack(Node* node)
		{
			insertBefore(node, end());
		}

		void popBack()
		{
			erase(back());
		}

		void pushFront(Node* node)
		{
			insertBefore(node, begin());
		}

		void popFront()
		{
			erase(front());
		}

		void insertBefore(Node* node, Node* refNode)
		{
			setPrev(node, getPrev(refNode));
			setNext(node, refNode);
			setNext(getPrev(refNode), node);
			setPrev(refNode, node);

			++size_;
		}

		void insertAfter(Node* node, Node* refNode)
		{
			insertBefore(node, getNext(refNode));
		}

		void replace(Node* node, Node* oldNode)
		{
			setNext(node, getNext(oldNode));
			setPrev(node, getPrev(oldNode));
			setNext(getPrev(node), node);
			setPrev(getNext(node), node);
		}

		void erase(Node* node)
		{
			setNext(getPrev(node), getNext(node));
			setPrev(getNext(node), getPrev(node));

			--size_;
		}

		void swap(LinkedList& other)
		{
			if (other.empty())
			{
				if (!empty())
				{
					Node* next = getNext(&head_);
					Node* prev = getPrev(&head_);

					setPrev(&head_, &head_);
					setNext(&head_, &head_);

					setNext(&other.head_, next);
					setPrev(&other.head_, prev);
					setPrev(getNext(&other.head_), &other.head_);
					setNext(getPrev(&other.head_), &other.head_);

					detail::swap(size_, other.size_);
				}
			}
			else if (empty())
			{
				other.swap(*this);
			}
			else
			{
				Node* next = getNext(&head_);
				Node* prev = getPrev(&head_);

				setNext(&head_, getNext(&other.head_));
				setPrev(&head_, getPrev(&other.head_));
				setPrev(getNext(&head_), &head_);
				setNext(getPrev(&head_), &head_);

				setNext(&other.head_, next);
				setPrev(&other.head_, prev);
				setPrev(getNext(&other.head_), &other.head_);
				setNext(getPrev(&other.head_), &other.head_);

				detail::swap(size_, other.size_);
			}
		}

	public:
		template<typename NodePtr>
		static NodePtr increment(NodePtr node)
		{
			return getNext(node);
		}

		template<typename NodePtr>
		static NodePtr decrement(NodePtr node)
		{
			return getPrev(node);
		}

	private:
		static Node* getPrev(const Node* node)
		{
			return Traits::getPrev(node);
		}

		static void setPrev(Node* node, Node* prev)
		{
			Traits::setPrev(node, prev);
		}

		static Node* getNext(const Node* node)
		{
			return Traits::getNext(node);
		}

		static void setNext(Node* node, Node* next)
		{
			Traits::setNext(node, next);
		}

	private:
		Node head_;
		size_t size_;
	};

	template<typename Node, typename Traits>
	inline void swap(LinkedList<Node, Traits>& a, LinkedList<Node, Traits>& b)
	{
		a.swap(b);
	}

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_LINKEDLIST_H_

