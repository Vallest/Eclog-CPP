// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DOCUMENT_H_
#define ECLOG_CPP_DOCUMENT_H_

#include <Eclog/Detail/ObjectNodeImpl.h>
#include <Eclog/Detail/NodeFactory.h>

namespace eclog {

	template<typename Alloc>
	class BasicDocument : public ObjectNode {
	public:
		BasicDocument()
		{
		}

		BasicDocument(const ObjectDesc& desc) : impl_(desc)
		{
		}

		BasicDocument(const ObjectNode& other) : impl_(other)
		{
		}

		BasicDocument(const BasicDocument& other) : impl_(other)
		{
		}

		BasicDocument& operator=(const ObjectDesc& desc)
		{
			assign(desc);
			return *this;
		}

		BasicDocument& operator=(const ObjectNode& other)
		{
			assign(other);
			return *this;
		}

		BasicDocument& operator=(const BasicDocument& other)
		{
			assign(other);
			return *this;
		}

		void swap(BasicDocument& other)
		{
			impl_.swap(other.impl_);
		}

	public:
		virtual NodeType nodeType() const ECLOG_OVERRIDE
		{
			return impl_.nodeType();
		}

		virtual void clear() ECLOG_OVERRIDE
		{
			impl_.clear();
		}

		virtual bool empty() const ECLOG_OVERRIDE
		{
			return impl_.empty();
		}

		virtual size_t size() const ECLOG_OVERRIDE
		{
			return impl_.size();
		}

		virtual Iterator begin() ECLOG_OVERRIDE
		{
			return impl_.begin();
		}

		virtual Iterator end() ECLOG_OVERRIDE
		{
			return impl_.end();
		}

		virtual ConstIterator begin() const ECLOG_OVERRIDE
		{
			return impl_.begin();
		}

		virtual ConstIterator end() const ECLOG_OVERRIDE
		{
			return impl_.end();
		}

		virtual bool contains(cstring key) const ECLOG_OVERRIDE
		{
			return impl_.contains(key);
		}

		virtual Iterator find(cstring key) ECLOG_OVERRIDE
		{
			return impl_.find(key);
		}

		virtual ConstIterator find(cstring key) const ECLOG_OVERRIDE
		{
			return impl_.find(key);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const Element& element) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, element);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const eclog::KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Pair<Iterator, bool> insert(Iterator pos, const KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insert(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const Element& element) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, element);
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const eclog::KeyDesc& key, const ValueNode& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const KeyNode& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual Iterator insertForce(Iterator pos, const eclog::KeyDesc& key, const ValueDesc& value) ECLOG_OVERRIDE
		{
			return impl_.insertForce(pos, key, value);
		}

		virtual void merge(const ObjectDesc& patch) ECLOG_OVERRIDE
		{
			impl_.merge(patch);
		}

		virtual void merge(const ObjectNode& patch) ECLOG_OVERRIDE
		{
			impl_.merge(patch);
		}

		virtual void remove(Iterator pos) ECLOG_OVERRIDE
		{
			impl_.remove(pos);
		}

		virtual size_t remove(Iterator first, Iterator last) ECLOG_OVERRIDE
		{
			return impl_.remove(first, last);
		}

		virtual bool remove(cstring key) ECLOG_OVERRIDE
		{
			return impl_.remove(key);
		}

		virtual void parse(eclog::Context& ctx) ECLOG_OVERRIDE
		{
			impl_.parse(ctx);
		}

		virtual void parse(eclog::Context& ctx, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(ctx, ec);
		}

		virtual void parse(InputStream& stream) ECLOG_OVERRIDE
		{
			impl_.parse(stream);
		}

		virtual void parse(InputStream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(stream, ec);
		}

		virtual void parse(cstring str) ECLOG_OVERRIDE
		{
			impl_.parse(str);
		}

		virtual void parse(cstring str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(str, ec);
		}

		virtual void parse(std::istream& stream) ECLOG_OVERRIDE
		{
			impl_.parse(stream);
		}

		virtual void parse(std::istream& stream, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(stream, ec);
		}

		virtual void parse(const std::string& str) ECLOG_OVERRIDE
		{
			impl_.parse(str);
		}

		virtual void parse(const std::string& str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(str, ec);
		}

		virtual void parse(const char* str) ECLOG_OVERRIDE
		{
			impl_.parse(str);
		}

		virtual void parse(const char* str, ErrorCode& ec) ECLOG_OVERRIDE
		{
			impl_.parse(str, ec);
		}

		virtual void render(OutputStream& stream) const ECLOG_OVERRIDE
		{
			impl_.render(stream);
		}

		virtual void render(OutputStream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, ec);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc);
		}

		virtual void render(OutputStream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc, ec);
		}

		virtual void render(std::ostream& stream) const ECLOG_OVERRIDE
		{
			impl_.render(stream);
		}

		virtual void render(std::ostream& stream, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, ec);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc);
		}

		virtual void render(std::ostream& stream, const RendererConfig& rc, ErrorCode& ec) const ECLOG_OVERRIDE
		{
			impl_.render(stream, rc, ec);
		}

		virtual void assign(const ObjectDesc& desc) ECLOG_OVERRIDE
		{
			impl_.assign(desc);
		}

		virtual void assign(const ObjectNode& other) ECLOG_OVERRIDE
		{
			if (&other == this) {
				return;
			}

			impl_.assign(other);
		}

	private:
		detail::ObjectNodeImpl<detail::NodeFactory<Alloc> > impl_;
	};

	template<typename Alloc>
	inline void swap(BasicDocument<Alloc>& a, BasicDocument<Alloc>& b)
	{
		a.swap(b);
	}

	typedef BasicDocument<ECLOG_DEFAULT_ALLOCATOR> Document;

} // eclog

#endif // ECLOG_CPP_DOCUMENT_H_

