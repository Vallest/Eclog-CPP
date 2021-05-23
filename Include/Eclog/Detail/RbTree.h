// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_RBTREE_H_
#define ECLOG_CPP_DETAIL_RBTREE_H_

#include <Eclog/Utility.h>
#include <Eclog/Detail/Utility.h>
#include <Eclog/Detail/NonCopyable.h>

// RbTree (based on the red-black tree implementation of STLport)
//
// Copyright (c) 1994
// Hewlett-Packard Company
// 
// Copyright (c) 1996,1997
// Silicon Graphics Computer Systems, Inc.
// 
// Copyright (c) 1997
// Moscow Center for SPARC Technology
// 
// Copyright (c) 1999
// Boris Fomitchev
// 
// This material is provided "as is", with absolutely no warranty
// expressed or implied. Any use is at your own risk.
// 
// Permission to use or copy this software for any purpose is hereby
// granted without fee, provided the above notices are retained on
// all copies. Permission to modify the code and to distribute
// modified code is granted, provided the above notices are retained,
// and a notice that the code was modified is included with the above
// copyright notice.

namespace eclog {

	namespace detail {

		template<typename Node, typename Traits, typename Compare>
		class RbTree : private NonCopyable {
		private:
			typedef typename Traits::ColorType ColorType;

		public:
			RbTree() : size_(0)
			{
				setColor(&head_, red());
				setParent(&head_, 0);
				setLeft(&head_, &head_);
				setRight(&head_, &head_);
			}

			void clear()
			{
				if (size_ != 0)
				{
					setParent(&head_, 0);
					setLeft(&head_, &head_);
					setRight(&head_, &head_);

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
				return getLeft(&head_);
			}

			const Node* begin() const
			{
				return getLeft(&head_);
			}

			Node* end()
			{
				return &head_;
			}

			const Node* end() const
			{
				return &head_;
			}

			template<typename Key>
			Node* find(const Key& key)
			{
				return find<Key, Node*>(key, getParent(&head_), &head_);
			}

			template<typename Key>
			const Node* find(const Key& key) const
			{
				return find<Key, const Node*>(key, getParent(&head_), &head_);
			}

			Pair<Node*, bool> insertUnique(Node* node)
			{
				setLeft(node, 0);
				setRight(node, 0);

				Node* p = &head_;
				Node* p2 = getParent(&head_);

				bool comp = true;

				while (p2 != 0)
				{
					p = p2;
					comp = compare(*node, *p2);
					p2 = comp ? getLeft(p2) : getRight(p2);
				}

				Node* p3 = p;

				if (comp)
				{
					if (p3 == getLeft(&head_))
					{
						insert(p, node, p);

						return Pair<Node*, bool>(node, true);
					}
					else
					{
						p3 = decrement(p3);
					}
				}

				if (compare(*p3, *node))
				{
					insert(p, node, p2);

					return Pair<Node*, bool>(node, true);
				}

				return Pair<Node*, bool>(p3, false);
			}

			void erase(Node* node)
			{
				Node* root = getParent(&head_);
				Node* leftmost = getLeft(&head_);
				Node* rightmost = getRight(&head_);

				rebalanceForErase(node, root, leftmost, rightmost);

				setParent(&head_, root);
				setLeft(&head_, leftmost);
				setRight(&head_, rightmost);

				--size_;
			}

			void swap(RbTree& other)
			{
				if (other.empty())
				{
					if (!empty())
					{
						Node* root = getParent(&head_);
						Node* leftmost = getLeft(&head_);
						Node* rightmost = getRight(&head_);

						setParent(&head_, 0);
						setLeft(&head_, &head_);
						setRight(&head_, &head_);

						setParent(&other.head_, root);
						setLeft(&other.head_, leftmost);
						setRight(&other.head_, rightmost);

						setParent(root, &other.head_);

						detail::swap(size_, other.size_);
					}
				}
				else if (empty())
				{
					other.swap(*this);
				}
				else
				{
					Node* root = getParent(&head_);
					Node* leftmost = getLeft(&head_);
					Node* rightmost = getRight(&head_);

					setParent(&head_, getParent(&other.head_));
					setLeft(&head_, getLeft(&other.head_));
					setRight(&head_, getRight(&other.head_));
					setParent(getParent(&head_), &head_);

					setParent(&other.head_, root);
					setLeft(&other.head_, leftmost);
					setRight(&other.head_, rightmost);
					setParent(getParent(&other.head_), &other.head_);

					detail::swap(size_, other.size_);
				}
			}

			bool verify() const
			{
				Node* root = getParent(&head_);
				Node* leftmost = getLeft(&head_);
				Node* rightmost = getRight(&head_);

				if (size() == 0 || begin() == end())
				{
					return ((size() == 0) && (begin() == end()) && (leftmost == &head_) && (rightmost == &head_));
				}

				int len = blackCount(leftmost, root);

				for (const Node* p = begin(); p != end(); p = increment(p))
				{
					const Node* left = getLeft(p);
					const Node* right = getRight(p);

					if (getColor(p) == red())
					{
						if ((left && getColor(left) == red()) || (right && getColor(right) == red())) {
							return false;
						}
					}

					if (left && compare(*p, *left)) {
						return false;
					}

					if (right && compare(*right, *p)) {
						return false;
					}

					if (!left && !right && blackCount(p, root) != len) {
						return false;
					}
				}

				if (leftmost != minimum(root)) {
					return false;
				}

				if (rightmost != maximum(root)) {
					return false;
				}

				return true;
			}

		public:
			template<typename NodePtr>
			static NodePtr increment(NodePtr node)
			{
				if (getRight(node) != 0)
				{
					node = minimum(getRight(node));
				}
				else
				{
					Node* p = getParent(node);

					while (node == getRight(p))
					{
						node = p;
						p = getParent(p);
					}

					if (getRight(node) != p) {
						node = p;
					}
				}

				return node;
			}

			template<typename NodePtr>
			static NodePtr decrement(NodePtr node)
			{
				if (getColor(node) == red() && getParent(getParent(node)) == node)
				{
					node = getRight(node);
				}
				else if (getLeft(node) != 0)
				{
					node = maximum(getLeft(node));
				}
				else
				{
					NodePtr p = getParent(node);

					while (node == getLeft(p))
					{
						node = p;
						p = getParent(p);
					}

					node = p;
				}

				return node;
			}

		private:
			static Node* getParent(const Node* node)
			{
				return Traits::getParent(node);
			}

			static void setParent(Node* node, Node* parent)
			{
				Traits::setParent(node, parent);
			}

			static Node* getLeft(const Node* node)
			{
				return Traits::getLeft(node);
			}

			static void setLeft(Node* node, Node* left)
			{
				Traits::setLeft(node, left);
			}

			static Node* getRight(const Node* node)
			{
				return Traits::getRight(node);
			}

			static void setRight(Node* node, Node* right)
			{
				Traits::setRight(node, right);
			}

			static ColorType getColor(const Node* node)
			{
				return Traits::getColor(node);
			}

			static void setColor(Node* node, ColorType color)
			{
				Traits::setColor(node, color);
			}

			static ColorType red()
			{
				return Traits::red();
			}

			static ColorType black()
			{
				return Traits::black();
			}

			template<typename T1, typename T2>
			static bool compare(const T1& a, const T2& b)
			{
				return Compare()(a, b);
			}

			static Node* minimum(Node* node)
			{
				while (getLeft(node) != 0) {
					node = getLeft(node);
				}

				return node;
			}

			static Node* maximum(Node* node)
			{
				while (getRight(node) != 0) {
					node = getRight(node);
				}

				return node;
			}

			static void rotateLeft(Node* node, Node*& root)
			{
				Node* p = getRight(node);

				setRight(node, getLeft(p));

				if (getLeft(p) != 0) {
					setParent(getLeft(p), node);
				}

				setParent(p, getParent(node));

				if (node == root) {
					root = p;
				}
				else if (node == getLeft(getParent(node))) {
					setLeft(getParent(node), p);
				}
				else {
					setRight(getParent(node), p);
				}

				setLeft(p, node);
				setParent(node, p);
			}

			static void rotateRight(Node* node, Node*& root)
			{
				Node* p = getLeft(node);

				setLeft(node, getRight(p));

				if (getRight(p) != 0) {
					setParent(getRight(p), node);
				}

				setParent(p, getParent(node));

				if (node == root) {
					root = p;
				}
				else if (node == getRight(getParent(node))) {
					setRight(getParent(node), p);
				}
				else {
					setLeft(getParent(node), p);
				}

				setRight(p, node);
				setParent(node, p);
			}

			static void rebalance(Node* node, Node*& root)
			{
				setColor(node, red());

				while (node != root && getColor(getParent(node)) == red())
				{
					if (getParent(node) == getLeft(getParent(getParent(node))))
					{
						Node* p = getRight(getParent(getParent(node)));

						if (p && getColor(p) == red())
						{
							setColor(getParent(node), black());
							setColor(p, black());
							setColor(getParent(getParent(node)), red());
							node = getParent(getParent(node));
						}
						else
						{
							if (node == getRight(getParent(node)))
							{
								node = getParent(node);
								rotateLeft(node, root);
							}

							setColor(getParent(node), black());
							setColor(getParent(getParent(node)), red());
							rotateRight(getParent(getParent(node)), root);
						}
					}
					else
					{
						Node* p = getLeft(getParent(getParent(node)));

						if (p && getColor(p) == red())
						{
							setColor(getParent(node), black());
							setColor(p, black());
							setColor(getParent(getParent(node)), red());
							node = getParent(getParent(node));
						}
						else
						{
							if (node == getLeft(getParent(node)))
							{
								node = getParent(node);
								rotateRight(node, root);
							}

							setColor(getParent(node), black());
							setColor(getParent(getParent(node)), red());
							rotateLeft(getParent(getParent(node)), root);
						}
					}
				}

				setColor(root, black());
			}

			static Node* rebalanceForErase(Node* node, Node*& root, Node*& leftmost, Node*& rightmost)
			{
				Node* p = node;
				Node* p2;
				Node* p3;

				if (getLeft(p) == 0)
				{
					p2 = getRight(p);
				}
				else if (getRight(p) == 0)
				{
					p2 = getLeft(p);
				}
				else
				{
					p = minimum(getRight(p));
					p2 = getRight(p);
				}

				if (p != node)
				{
					setParent(getLeft(node), p);
					setLeft(p, getLeft(node));

					if (p != getRight(node))
					{
						p3 = getParent(p);

						if (p2) {
							setParent(p2, getParent(p));
						}

						setLeft(getParent(p), p2);
						setRight(p, getRight(node));
						setParent(getRight(node), p);
					}
					else
					{
						p3 = p;
					}

					if (root == node) {
						root = p;
					}
					else if (getLeft(getParent(node)) == node) {
						setLeft(getParent(node), p);
					}
					else {
						setRight(getParent(node), p);
					}

					setParent(p, getParent(node));

					ColorType t = getColor(p);
					setColor(p, getColor(node));
					setColor(node, t);

					p = node;
				}
				else
				{
					p3 = getParent(p);

					if (p2) {
						setParent(p2, getParent(p));
					}

					if (root == node) {
						root = p2;
					}
					else if (getLeft(getParent(node)) == node) {
						setLeft(getParent(node), p2);
					}
					else {
						setRight(getParent(node), p2);
					}

					if (leftmost == node)
					{
						if (getRight(node) == 0) {
							leftmost = getParent(node);
						}
						else {
							leftmost = minimum(p2);
						}
					}

					if (rightmost == node)
					{
						if (getLeft(node) == 0) {
							rightmost = getParent(node);
						}
						else {
							rightmost = maximum(p2);
						}
					}
				}

				if (getColor(p) != red())
				{
					while (p2 != root && (p2 == 0 || getColor(p2) == black()))
					{
						if (p2 == getLeft(p3))
						{
							Node* p4 = getRight(p3);

							if (getColor(p4) == red())
							{
								setColor(p4, black());
								setColor(p3, red());
								rotateLeft(p3, root);
								p4 = getRight(p3);
							}

							if ((getLeft(p4) == 0 || getColor(getLeft(p4)) == black()) && (getRight(p4) == 0 || getColor(getRight(p4)) == black()))
							{
								setColor(p4, red());
								p2 = p3;
								p3 = getParent(p3);
							}
							else
							{
								if (getRight(p4) == 0 || getColor(getRight(p4)) == black())
								{
									if (getLeft(p4)) {
										setColor(getLeft(p4), black());
									}

									setColor(p4, red());
									rotateRight(p4, root);
									p4 = getRight(p3);
								}

								setColor(p4, getColor(p3));
								setColor(p3, black());

								if (getRight(p4)) {
									setColor(getRight(p4), black());
								}

								rotateLeft(p3, root);
								break;
							}
						}
						else
						{
							Node* p4 = getLeft(p3);

							if (getColor(p4) == red())
							{
								setColor(p4, black());
								setColor(p3, red());
								rotateRight(p3, root);
								p4 = getLeft(p3);
							}

							if ((getRight(p4) == 0 || getColor(getRight(p4)) == black()) && (getLeft(p4) == 0 || getColor(getLeft(p4)) == black()))
							{
								setColor(p4, red());
								p2 = p3;
								p3 = getParent(p3);
							}
							else
							{
								if (getLeft(p4) == 0 || getColor(getLeft(p4)) == black())
								{
									if (getRight(p4)) {
										setColor(getRight(p4), black());
									}

									setColor(p4, red());
									rotateLeft(p4, root);
									p4 = getLeft(p3);
								}

								setColor(p4, getColor(p3));
								setColor(p3, black());

								if (getLeft(p4)) {
									setColor(getLeft(p4), black());
								}

								rotateRight(p3, root);
								break;
							}
						}
					}

					if (p2) {
						setColor(p2, black());
					}
				}

				return p;
			}

			template<typename Key, typename NodePtr>
			static NodePtr find(const Key& key, NodePtr root, NodePtr end)
			{
				NodePtr p = end;
				NodePtr p2 = root;

				while (p2 != 0)
				{
					if (!compare(*p2, key))
					{
						p = p2;
						p2 = getLeft(p2);
					}
					else
					{
						p2 = getRight(p2);
					}
				}

				if (p != end)
				{
					if (compare(key, *p)) {
						p = end;
					}
				}

				return p;
			}

			Node* insert(Node* parent, Node* node, Node* onLeft = 0, Node* onRight = 0)
			{
				if (parent == &head_)
				{
					setLeft(parent, node);
					setParent(&head_, node);
					setRight(&head_, node);
				}
				else if (onRight == 0 && (onLeft != 0 || compare(*node, *parent)))
				{
					setLeft(parent, node);

					if (parent == getLeft(&head_)) {
						setLeft(&head_, node);
					}
				}
				else
				{
					setRight(parent, node);

					if (parent == getRight(&head_)) {
						setRight(&head_, node);
					}
				}

				setParent(node, parent);

				Node* root = getParent(&head_);

				rebalance(node, root);

				setParent(&head_, root);

				++size_;

				return node;
			}

			int blackCount(const Node* node, const Node* root) const
			{
				if (node == 0) {
					return 0;
				}

				int count = getColor(node) == black() ? 1 : 0;

				if (node == root) {
					return count;
				}
				else {
					return count + blackCount(getParent(node), root);
				}
			}

		private:
			Node head_;
			size_t size_;
		};

		template<typename Node, typename Traits, typename Compare>
		inline void swap(RbTree<Node, Traits, Compare>& a, RbTree<Node, Traits, Compare>& b)
		{
			a.swap(b);
		}

	} // detail

} // eclog

#endif // ECLOG_CPP_DETAIL_RBTREE_H_

