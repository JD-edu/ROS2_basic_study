// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/msg/msg_center.hpp"


#ifndef CV_MSG__MSG__DETAIL__MSG_CENTER__STRUCT_HPP_
#define CV_MSG__MSG__DETAIL__MSG_CENTER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cv_msg__msg__MsgCenter __attribute__((deprecated))
#else
# define DEPRECATED__cv_msg__msg__MsgCenter __declspec(deprecated)
#endif

namespace cv_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MsgCenter_
{
  using Type = MsgCenter_<ContainerAllocator>;

  explicit MsgCenter_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0ll;
      this->y = 0ll;
    }
  }

  explicit MsgCenter_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0ll;
      this->y = 0ll;
    }
  }

  // field types and members
  using _x_type =
    int64_t;
  _x_type x;
  using _y_type =
    int64_t;
  _y_type y;

  // setters for named parameter idiom
  Type & set__x(
    const int64_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const int64_t & _arg)
  {
    this->y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cv_msg::msg::MsgCenter_<ContainerAllocator> *;
  using ConstRawPtr =
    const cv_msg::msg::MsgCenter_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cv_msg::msg::MsgCenter_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cv_msg::msg::MsgCenter_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cv_msg__msg__MsgCenter
    std::shared_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cv_msg__msg__MsgCenter
    std::shared_ptr<cv_msg::msg::MsgCenter_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MsgCenter_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    return true;
  }
  bool operator!=(const MsgCenter_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MsgCenter_

// alias to use template instance with default allocator
using MsgCenter =
  cv_msg::msg::MsgCenter_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cv_msg

#endif  // CV_MSG__MSG__DETAIL__MSG_CENTER__STRUCT_HPP_
