// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/msg/msg_center.h"


#ifndef CV_MSG__MSG__DETAIL__MSG_CENTER__STRUCT_H_
#define CV_MSG__MSG__DETAIL__MSG_CENTER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/MsgCenter in the package cv_msg.
typedef struct cv_msg__msg__MsgCenter
{
  int64_t x;
  int64_t y;
} cv_msg__msg__MsgCenter;

// Struct for a sequence of cv_msg__msg__MsgCenter.
typedef struct cv_msg__msg__MsgCenter__Sequence
{
  cv_msg__msg__MsgCenter * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cv_msg__msg__MsgCenter__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CV_MSG__MSG__DETAIL__MSG_CENTER__STRUCT_H_
