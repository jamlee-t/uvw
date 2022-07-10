#ifndef UVW_UNDERLYING_TYPE_INCLUDE_H
#define UVW_UNDERLYING_TYPE_INCLUDE_H

#include <memory>
#include <type_traits>
#include <utility>
#include "loop.h"

namespace uvw {

// JAMLEE:
// T: 代表 UnderlyingType 的子类
// U: 代表 resource 类型，也就是 resource 字段的类型
/**
 * @brief Wrapper class for underlying types.
 *
 * It acts mainly as a wrapper around data structures of the underlying library.
 */
template<typename T, typename U>
class UnderlyingType {
    // JAMLEE: 本身模板类友元类
    template<typename, typename>
    friend class UnderlyingType;

protected:
    // JAMLEE: 这个保护型的结构体，也就是说只有子类能够初始化父类了
    struct ConstructorAccess {
        explicit ConstructorAccess(int) {}
    };

    // JAMLEE: resource 指针，转换为 R 类型的指针 
    template<typename R = U>
    auto get() noexcept {
        return reinterpret_cast<R *>(&resource);
    }

    // JAMLEE: resource 指针，转换为 R 类型的常量指针 resource
    template<typename R = U>
    auto get() const noexcept {
        return reinterpret_cast<const R *>(&resource);
    }

    // JAMLEE: 获取其他底层资源的指针
    template<typename R, typename... P>
    auto get(UnderlyingType<P...> &other) noexcept {
        return reinterpret_cast<R *>(&other.resource);
    }

public:
    // JAMLEE: 构造函数
    explicit UnderlyingType(ConstructorAccess, std::shared_ptr<Loop> ref) noexcept
        : pLoop{std::move(ref)}, resource{} {}

    UnderlyingType(const UnderlyingType &) = delete;
    UnderlyingType(UnderlyingType &&) = delete;

    virtual ~UnderlyingType() {
        static_assert(std::is_base_of_v<UnderlyingType<T, U>, T>);
    }

    // JAMLEE: 删除默认的赋值符
    UnderlyingType &operator=(const UnderlyingType &) = delete;
    UnderlyingType &operator=(UnderlyingType &&) = delete;

    // JAMLEE: 创建 resource。
    /**
     * @brief Creates a new resource of the given type.
     * @param args Arguments to be forwarded to the actual constructor (if any).
     * @return A pointer to the newly created resource.
     */
    template<typename... Args>
    static std::shared_ptr<T> create(Args &&...args) {
        return std::make_shared<T>(ConstructorAccess{0}, std::forward<Args>(args)...);
    }

    // JAMLEE: 获取 resource 被发起的 loop。返回值为引用，避免调用拷贝构造函数
    /**
     * @brief Gets the loop from which the resource was originated.
     * @return A reference to a loop instance.
     */
    Loop &loop() const noexcept {
        return *pLoop;
    }

    /**
     * @brief Gets the underlying raw data structure.
     *
     * This function should not be used, unless you know exactly what you are
     * doing and what are the risks.<br/>
     * Going raw is dangerous, mainly because the lifetime management of a loop,
     * a handle or a request is in charge to the library itself and users should
     * not work around it.
     *
     * @warning
     * Use this function at your own risk, but do not expect any support in case
     * of bugs.
     *
     * @return The underlying raw data structure.
     */
    const U *raw() const noexcept {
        return &resource;
    }

    /**
     * @brief Gets the underlying raw data structure.
     *
     * This function should not be used, unless you know exactly what you are
     * doing and what are the risks.<br/>
     * Going raw is dangerous, mainly because the lifetime management of a loop,
     * a handle or a request is in charge to the library itself and users should
     * not work around it.
     *
     * @warning
     * Use this function at your own risk, but do not expect any support in case
     * of bugs.
     *
     * @return The underlying raw data structure.
     */
    U *raw() noexcept {
        return const_cast<U *>(const_cast<const UnderlyingType *>(this)->raw());
    }

private:
    std::shared_ptr<Loop> pLoop;
    U resource; // T 代表 UnderlyingType, U 代表类似 uv_idle_type 类型
};

} // namespace uvw

#endif // UVW_UNDERLYING_TYPE_INCLUDE_H
