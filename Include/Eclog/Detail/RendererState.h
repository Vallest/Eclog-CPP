// Eclog-CPP
// Copyright (c) Vallest Systems LLC. All Rights Reserved.
// Released under the MIT license.

#ifndef ECLOG_CPP_DETAIL_RENDERERSTATE_H_
#define ECLOG_CPP_DETAIL_RENDERERSTATE_H_

namespace vallest {
namespace eclog {
namespace detail {

	enum RendererState {
		renderer_state_init = 0,
		renderer_state_element = 1,
		renderer_state_object = 2,
		renderer_state_array = 3,
		renderer_state_closed = 4,

		renderer_state_ref_1 = 1 << 4,
		renderer_state_ref_2 = 2 << 4,
		renderer_state_root = 3 << 4,
	};

} // detail
} // eclog
} // vallest

#endif // ECLOG_CPP_DETAIL_RENDERERSTATE_H_

