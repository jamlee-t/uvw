#ifdef UVW_AS_LIB
#    include "idle.h"
#endif

#include "config.h"

namespace uvw {

// JAMLEE: 调用回调
UVW_INLINE void IdleHandle::startCallback(uv_idle_t *handle) {
    IdleHandle &idle = *(static_cast<IdleHandle *>(handle->data));
    idle.publish(IdleEvent{});
}

// JAMLEE: 初始化 handle
UVW_INLINE bool IdleHandle::init() {
    return initialize(&uv_idle_init);
}

// JAMLEE: 启动 handle。调用回调函数 startCallback
UVW_INLINE void IdleHandle::start() {
    invoke(&uv_idle_start, get(), &startCallback);
}

// JAMLEE: 关闭 handle
UVW_INLINE void IdleHandle::stop() {
    invoke(&uv_idle_stop, get());
}

} // namespace uvw
