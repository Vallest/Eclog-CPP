// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_RENDERER_H_
#define ECLOG_CPP_RENDERER_H_

#include <Eclog/OutputStream.h>
#include <Eclog/RendererConfig.h>
#include <Eclog/ObjectDesc.h>
#include <Eclog/RendererHandle.h>
#include <Eclog/cstring.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/Renderer.h>
#include <Eclog/Detail/RendererState.h>
#include <Eclog/Detail/NonCopyable.h>

namespace eclog {

	class Renderer : private detail::NonCopyable {
	public:
		explicit Renderer(OutputStream& stream, const RendererConfig& rendererConfig = RendererConfig()) :
			renderer_(stream, rendererConfig), state_(detail::renderer_state_init)
		{
			initialize();
		}

		void beginRootObject()
		{
			changeStateBeginRootObject();

			renderer_.beginObject(0);
		}

		void endRootObject()
		{
			changeStateEndRootObject();

			renderer_.endObject(0);
		}

		void beginRootObject(ErrorCode& ec)
		{
			changeStateBeginRootObject();

			renderer_.beginObject(&ec);
		}

		void endRootObject(ErrorCode& ec)
		{
			changeStateEndRootObject();

			renderer_.endObject(&ec);
		}

		void renderRootObject(const ObjectDesc& root)
		{
			changeStateRoot();

			renderer_.renderMember(root, 0);
		}

		void renderRootObject(const ObjectDesc& root, ErrorCode& ec)
		{
			changeStateRoot();

			renderer_.renderMember(root, &ec);
		}

		void renderEmptyLines(int count)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, 0);
		}

		void renderEmptyLines(int count, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderEmptyLines(count, &ec);
		}

		void renderComment(cstring comment)
		{
			checkStateElement();

			renderer_.renderComment(comment, 0);
		}

		void renderComment(cstring comment, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderComment(comment, &ec);
		}

		int beginInline()
		{
			checkStateElement();

			return renderer_.beginInline();
		}

		int endInline()
		{
			checkStateElement();

			return renderer_.endInline();
		}

		void close()
		{
			close(0);
		}

		void close(ErrorCode& ec)
		{
			close(&ec);
		}

		operator RendererHandle()
		{
			return RendererHandle(&renderer_, &state_);
		}

	private:
		void initialize()
		{
			checkState(state_, detail::renderer_state_init);
			changeState(state_, detail::renderer_state_element);
		}

		void checkStateElement()
		{
			checkState(state_, detail::renderer_state_element, detail::renderer_state_element | detail::renderer_state_root);
		}

		void changeStateBeginRootObject()
		{
			checkState(state_, detail::renderer_state_element);
			changeState(state_, detail::renderer_state_object);
		}

		void changeStateEndRootObject()
		{
			checkState(state_, detail::renderer_state_object, detail::renderer_state_object | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_element | detail::renderer_state_root);
		}

		void changeStateRoot()
		{
			checkState(state_, detail::renderer_state_element);
			changeState(state_, detail::renderer_state_element | detail::renderer_state_root);
		}

		void close(ErrorCode* ec)
		{
			checkState(state_, detail::renderer_state_element, detail::renderer_state_element | detail::renderer_state_root);

			bool hasRootObject = (state_ & detail::renderer_state_root) != 0;

			changeState(state_, detail::renderer_state_closed);

			if (!hasRootObject)
			{
				renderer_.renderMember(empty_object, ec);
				ECLOG_ON_ERROR(return);
			}

			renderer_.close(ec);
			ECLOG_ON_ERROR(return);
		}

	private:
		static void checkState(int& state, int expected)
		{
			if (state != expected) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void checkState(int& state, int expected, int expected2)
		{
			if (state != expected && state != expected2) {
				ECLOG_FAULT(InvalidOperation);
			}
		}

		static void changeState(int& state, int to)
		{
			state = to;
		}

	private:
		detail::Renderer renderer_;

		int state_;
	};

} // eclog

#endif // ECLOG_CPP_RENDERER_H_

