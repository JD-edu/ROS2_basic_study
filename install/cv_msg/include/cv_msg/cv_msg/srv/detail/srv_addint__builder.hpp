// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cv_msg:srv/SrvAddint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/srv/srv_addint.hpp"


#ifndef CV_MSG__SRV__DETAIL__SRV_ADDINT__BUILDER_HPP_
#define CV_MSG__SRV__DETAIL__SRV_ADDINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cv_msg/srv/detail/srv_addint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cv_msg
{

namespace srv
{

namespace builder
{

class Init_SrvAddint_Request_b
{
public:
  explicit Init_SrvAddint_Request_b(::cv_msg::srv::SrvAddint_Request & msg)
  : msg_(msg)
  {}
  ::cv_msg::srv::SrvAddint_Request b(::cv_msg::srv::SrvAddint_Request::_b_type arg)
  {
    msg_.b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cv_msg::srv::SrvAddint_Request msg_;
};

class Init_SrvAddint_Request_a
{
public:
  Init_SrvAddint_Request_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SrvAddint_Request_b a(::cv_msg::srv::SrvAddint_Request::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_SrvAddint_Request_b(msg_);
  }

private:
  ::cv_msg::srv::SrvAddint_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cv_msg::srv::SrvAddint_Request>()
{
  return cv_msg::srv::builder::Init_SrvAddint_Request_a();
}

}  // namespace cv_msg


namespace cv_msg
{

namespace srv
{

namespace builder
{

class Init_SrvAddint_Response_sum
{
public:
  Init_SrvAddint_Response_sum()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cv_msg::srv::SrvAddint_Response sum(::cv_msg::srv::SrvAddint_Response::_sum_type arg)
  {
    msg_.sum = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cv_msg::srv::SrvAddint_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cv_msg::srv::SrvAddint_Response>()
{
  return cv_msg::srv::builder::Init_SrvAddint_Response_sum();
}

}  // namespace cv_msg


namespace cv_msg
{

namespace srv
{

namespace builder
{

class Init_SrvAddint_Event_response
{
public:
  explicit Init_SrvAddint_Event_response(::cv_msg::srv::SrvAddint_Event & msg)
  : msg_(msg)
  {}
  ::cv_msg::srv::SrvAddint_Event response(::cv_msg::srv::SrvAddint_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cv_msg::srv::SrvAddint_Event msg_;
};

class Init_SrvAddint_Event_request
{
public:
  explicit Init_SrvAddint_Event_request(::cv_msg::srv::SrvAddint_Event & msg)
  : msg_(msg)
  {}
  Init_SrvAddint_Event_response request(::cv_msg::srv::SrvAddint_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SrvAddint_Event_response(msg_);
  }

private:
  ::cv_msg::srv::SrvAddint_Event msg_;
};

class Init_SrvAddint_Event_info
{
public:
  Init_SrvAddint_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SrvAddint_Event_request info(::cv_msg::srv::SrvAddint_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SrvAddint_Event_request(msg_);
  }

private:
  ::cv_msg::srv::SrvAddint_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cv_msg::srv::SrvAddint_Event>()
{
  return cv_msg::srv::builder::Init_SrvAddint_Event_info();
}

}  // namespace cv_msg

#endif  // CV_MSG__SRV__DETAIL__SRV_ADDINT__BUILDER_HPP_
