// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice
#ifndef CV_MSG__MSG__DETAIL__MSG_CENTER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define CV_MSG__MSG__DETAIL__MSG_CENTER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "cv_msg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cv_msg/msg/detail/msg_center__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
bool cdr_serialize_cv_msg__msg__MsgCenter(
  const cv_msg__msg__MsgCenter * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
bool cdr_deserialize_cv_msg__msg__MsgCenter(
  eprosima::fastcdr::Cdr &,
  cv_msg__msg__MsgCenter * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
size_t get_serialized_size_cv_msg__msg__MsgCenter(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
size_t max_serialized_size_cv_msg__msg__MsgCenter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
bool cdr_serialize_key_cv_msg__msg__MsgCenter(
  const cv_msg__msg__MsgCenter * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
size_t get_serialized_size_key_cv_msg__msg__MsgCenter(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
size_t max_serialized_size_key_cv_msg__msg__MsgCenter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cv_msg, msg, MsgCenter)();

#ifdef __cplusplus
}
#endif

#endif  // CV_MSG__MSG__DETAIL__MSG_CENTER__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
