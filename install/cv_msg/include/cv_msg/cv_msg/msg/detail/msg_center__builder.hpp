// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/msg/msg_center.hpp"


#ifndef CV_MSG__MSG__DETAIL__MSG_CENTER__BUILDER_HPP_
#define CV_MSG__MSG__DETAIL__MSG_CENTER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cv_msg/msg/detail/msg_center__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cv_msg
{

namespace msg
{

namespace builder
{

class Init_MsgCenter_y
{
public:
  explicit Init_MsgCenter_y(::cv_msg::msg::MsgCenter & msg)
  : msg_(msg)
  {}
  ::cv_msg::msg::MsgCenter y(::cv_msg::msg::MsgCenter::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cv_msg::msg::MsgCenter msg_;
};

class Init_MsgCenter_x
{
public:
  Init_MsgCenter_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MsgCenter_y x(::cv_msg::msg::MsgCenter::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_MsgCenter_y(msg_);
  }

private:
  ::cv_msg::msg::MsgCenter msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cv_msg::msg::MsgCenter>()
{
  return cv_msg::msg::builder::Init_MsgCenter_x();
}

}  // namespace cv_msg

#endif  // CV_MSG__MSG__DETAIL__MSG_CENTER__BUILDER_HPP_
