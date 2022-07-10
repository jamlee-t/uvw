#ifndef UVW_RESOURCE_INCLUDE_H
#define UVW_RESOURCE_INCLUDE_H

#include <memory>
#include <utility>
#include "emitter.h"
#include "underlying_type.hpp"

namespace uvw {

// JAMLEE: Handle 的基类。
// T: T 代表 UnderlyingType 及其子类
// U: 代表 resource 类型，也就是 resource 字段的类型
// std::enable_shared_from_this 防止析构函数调用 2 次。


/**
 * @brief Common class for almost all the resources available in `uvw`.
 *
 * This is the base class for handles and requests.
 */
template<typename T, typename U>
class Resource: public UnderlyingType<T, U>, public Emitter<T>, public std::enable_shared_from_this<T> {
protected:
    // JAMLEE: 类型别名
    using ConstructorAccess = typename UnderlyingType<T, U>::ConstructorAccess;

    // JAMLEE: 资源的父级，全是 loop
    auto parent() const noexcept {
        return this->loop().loop.get();
    }

    // JAMLEE: 当前对象赋值给 sPtr。
    void leak() noexcept {
        sPtr = this->shared_from_this();
    }

    void reset() noexcept {
        sPtr.reset();
    }

    // JAMLEE: 将 sPtr 转换为 bool 值。空指针为 false 有内容指针为 true
    bool self() const noexcept {
        return static_cast<bool>(sPtr);
    }

public:
    // JAMLEE: 构造函数。初始时 Data 关联到自身。
    explicit Resource(ConstructorAccess ca, std::shared_ptr<Loop> ref)
        : UnderlyingType<T, U>{ca, std::move(ref)} {
        this->get()->data = this;
    }

    // JAMLEE: 获取 Resource 类定义的 data
    /**
     * @brief Gets user-defined data. `uvw` won't use this field in any case.
     * @return User-defined data if any, an invalid pointer otherwise.
     */
    template<typename R = void>
    std::shared_ptr<R> data() const {
        return std::static_pointer_cast<R>(userData);
    }

    // JAMLEE: 设置 uData
    /**
     * @brief Sets arbitrary data. `uvw` won't use this field in any case.
     * @param uData User-defined arbitrary data.
     */
    void data(std::shared_ptr<void> uData) {
        userData = std::move(uData);
    }

private:
    std::shared_ptr<void> userData{nullptr};
    // JAMLEE: 指向本身的指针
    std::shared_ptr<void> sPtr{nullptr};
};

} // namespace uvw

#endif // UVW_RESOURCE_INCLUDE_H
