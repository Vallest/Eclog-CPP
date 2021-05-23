// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_RENDERERHANDLE_H_
#define ECLOG_CPP_RENDERERHANDLE_H_

namespace eclog {

	class Renderer;
	class ObjectRenderer;
	class ArrayRenderer;

	struct RendererHandle {
	private:
		friend class Renderer;
		friend class ObjectRenderer;
		friend class ArrayRenderer;

	private:
		explicit RendererHandle(void* p1, void* p2)
		{
			this->p1 = p1;
			this->p2 = p2;
		}

	private:
		void* p1;
		void* p2;
	};

} // eclog

#endif // ECLOG_CPP_RENDERERHANDLE_H_

