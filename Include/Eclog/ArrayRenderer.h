// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_ARRAYRENDERER_H_
#define ECLOG_CPP_ARRAYRENDERER_H_

#include <Eclog/RendererHandle.h>
#include <Eclog/cstring.h>
#include <Eclog/Error.h>
#include <Eclog/Detail/Renderer.h>
#include <Eclog/Detail/RendererState.h>
#include <Eclog/Detail/NonAssignable.h>

namespace vallest {
namespace eclog {

	class ArrayRenderer : private detail::NonAssignable {
	public:
		explicit ArrayRenderer(RendererHandle parent) :
			renderer_(*(detail::Renderer*)parent.p1), parentState_(*(int*)parent.p2),
			state_(detail::renderer_state_init)
		{
			initialize();
		}

		explicit ArrayRenderer(ArrayRenderer& parent) :
			renderer_(parent.renderer_), parentState_(parent.state_),
			state_(detail::renderer_state_init)
		{
			initialize();
		}

		void beginObject()
		{
			changeStateBeginObject();

			renderer_.beginObject(0);
		}

		void endObject()
		{
			changeStateEndObject();

			renderer_.endObject(0);
		}

		void beginObject(ErrorCode& ec)
		{
			changeStateBeginObject();

			renderer_.beginObject(&ec);
		}

		void endObject(ErrorCode& ec)
		{
			changeStateEndObject();

			renderer_.endObject(&ec);
		}

		void beginArray()
		{
			changeStateBeginArray();

			renderer_.beginArray(0);
		}

		void endArray()
		{
			changeStateEndArray();

			renderer_.endArray(0);
		}

		void beginArray(ErrorCode& ec)
		{
			changeStateBeginArray();

			renderer_.beginArray(&ec);
		}

		void endArray(ErrorCode& ec)
		{
			changeStateEndArray();

			renderer_.endArray(&ec);
		}

		void renderMember(const ValueDesc& value)
		{
			checkStateElement();

			renderer_.renderMember(value, 0);
		}

		void renderMember(const ValueDesc& value, ErrorCode& ec)
		{
			checkStateElement();

			renderer_.renderMember(value, &ec);
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

		operator RendererHandle()
		{
			return RendererHandle(&renderer_, &state_);
		}

	private:
		void initialize()
		{
			checkState(state_, detail::renderer_state_init);
			checkState(parentState_, detail::renderer_state_array);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

		void checkStateElement()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

		void changeStateBeginObject()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_object);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
		}

		void changeStateEndObject()
		{
			checkState(state_, detail::renderer_state_object, detail::renderer_state_object | detail::renderer_state_ref_1);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
		}

		void changeStateBeginArray()
		{
			checkState(state_, detail::renderer_state_element);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
			changeState(state_, detail::renderer_state_array);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
		}

		void changeStateEndArray()
		{
			checkState(state_, detail::renderer_state_array, detail::renderer_state_array | detail::renderer_state_ref_1);
			checkState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_2);
			changeState(state_, detail::renderer_state_element);
			changeState(parentState_, detail::renderer_state_array | detail::renderer_state_ref_1);
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
		detail::Renderer& renderer_;

		int& parentState_;

		int state_;
	};

} // eclog
} // vallest

#endif // ECLOG_CPP_ARRAYRENDERER_H_

