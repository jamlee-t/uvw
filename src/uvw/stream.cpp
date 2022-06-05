#ifdef UVW_AS_LIB
#    include "stream.h"
#endif

#include "config.h"

namespace uvw {

UVW_INLINE DataEvent::DataEvent(std::unique_ptr<char[]> buf, std::size_t len) noexcept
    : data{std::move(buf)}, length{len} {}

// JAMLEE: 调用 uv_shutdown 关闭 1 个 stream
UVW_INLINE void details::ShutdownReq::shutdown(uv_stream_t *handle) {
    invoke(&uv_shutdown, get(), handle, &defaultCallback<ShutdownEvent>);
}

} // namespace uvw
