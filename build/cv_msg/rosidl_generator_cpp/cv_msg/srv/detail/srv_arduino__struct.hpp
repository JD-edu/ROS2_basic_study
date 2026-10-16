// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cv_msg:srv/SrvArduino.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/srv/srv_arduino.hpp"


#ifndef CV_MSG__SRV__DETAIL__SRV_ARDUINO__STRUCT_HPP_
#define CV_MSG__SRV__DETAIL__SRV_ARDUINO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__cv_msg__srv__SrvArduino_Request __attribute__((deprecated))
#else
# define DEPRECATED__cv_msg__srv__SrvArduino_Request __declspec(deprecated)
#endif

namespace cv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SrvArduino_Request_
{
  using Type = SrvArduino_Request_<ContainerAllocator>;

  explicit SrvArduino_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dir = 0ll;
      this->speed = 0ll;
    }
  }

  explicit SrvArduino_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->dir = 0ll;
      this->speed = 0ll;
    }
  }

  // field types and members
  using _dir_type =
    int64_t;
  _dir_type dir;
  using _speed_type =
    int64_t;
  _speed_type speed;

  // setters for named parameter idiom
  Type & set__dir(
    const int64_t & _arg)
  {
    this->dir = _arg;
    return *this;
  }
  Type & set__speed(
    const int64_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cv_msg::srv::SrvArduino_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const cv_msg::srv::SrvArduino_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cv_msg__srv__SrvArduino_Request
    std::shared_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cv_msg__srv__SrvArduino_Request
    std::shared_ptr<cv_msg::srv::SrvArduino_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SrvArduino_Request_ & other) const
  {
    if (this->dir != other.dir) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const SrvArduino_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SrvArduino_Request_

// alias to use template instance with default allocator
using SrvArduino_Request =
  cv_msg::srv::SrvArduino_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cv_msg


#ifndef _WIN32
# define DEPRECATED__cv_msg__srv__SrvArduino_Response __attribute__((deprecated))
#else
# define DEPRECATED__cv_msg__srv__SrvArduino_Response __declspec(deprecated)
#endif

namespace cv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SrvArduino_Response_
{
  using Type = SrvArduino_Response_<ContainerAllocator>;

  explicit SrvArduino_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->answer = 0ll;
    }
  }

  explicit SrvArduino_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->answer = 0ll;
    }
  }

  // field types and members
  using _answer_type =
    int64_t;
  _answer_type answer;

  // setters for named parameter idiom
  Type & set__answer(
    const int64_t & _arg)
  {
    this->answer = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cv_msg::srv::SrvArduino_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const cv_msg::srv::SrvArduino_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cv_msg__srv__SrvArduino_Response
    std::shared_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cv_msg__srv__SrvArduino_Response
    std::shared_ptr<cv_msg::srv::SrvArduino_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SrvArduino_Response_ & other) const
  {
    if (this->answer != other.answer) {
      return false;
    }
    return true;
  }
  bool operator!=(const SrvArduino_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SrvArduino_Response_

// alias to use template instance with default allocator
using SrvArduino_Response =
  cv_msg::srv::SrvArduino_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cv_msg


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cv_msg__srv__SrvArduino_Event __attribute__((deprecated))
#else
# define DEPRECATED__cv_msg__srv__SrvArduino_Event __declspec(deprecated)
#endif

namespace cv_msg
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SrvArduino_Event_
{
  using Type = SrvArduino_Event_<ContainerAllocator>;

  explicit SrvArduino_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit SrvArduino_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cv_msg::srv::SrvArduino_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cv_msg::srv::SrvArduino_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cv_msg::srv::SrvArduino_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const cv_msg::srv::SrvArduino_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cv_msg::srv::SrvArduino_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cv_msg::srv::SrvArduino_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cv_msg__srv__SrvArduino_Event
    std::shared_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cv_msg__srv__SrvArduino_Event
    std::shared_ptr<cv_msg::srv::SrvArduino_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SrvArduino_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SrvArduino_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SrvArduino_Event_

// alias to use template instance with default allocator
using SrvArduino_Event =
  cv_msg::srv::SrvArduino_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace cv_msg

namespace cv_msg
{

namespace srv
{

struct SrvArduino
{
  using Request = cv_msg::srv::SrvArduino_Request;
  using Response = cv_msg::srv::SrvArduino_Response;
  using Event = cv_msg::srv::SrvArduino_Event;
};

}  // namespace srv

}  // namespace cv_msg

#endif  // CV_MSG__SRV__DETAIL__SRV_ARDUINO__STRUCT_HPP_
