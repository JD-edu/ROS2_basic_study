// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cv_msg/msg/detail/msg_center__rosidl_typesupport_introspection_c.h"
#include "cv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cv_msg/msg/detail/msg_center__functions.h"
#include "cv_msg/msg/detail/msg_center__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cv_msg__msg__MsgCenter__init(message_memory);
}

void cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_fini_function(void * message_memory)
{
  cv_msg__msg__MsgCenter__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_member_array[2] = {
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cv_msg__msg__MsgCenter, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cv_msg__msg__MsgCenter, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_members = {
  "cv_msg__msg",  // message namespace
  "MsgCenter",  // message name
  2,  // number of fields
  sizeof(cv_msg__msg__MsgCenter),
  false,  // has_any_key_member_
  cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_member_array,  // message members
  cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_init_function,  // function to initialize message memory (memory has to be allocated)
  cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_type_support_handle = {
  0,
  &cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_members,
  get_message_typesupport_handle_function,
  &cv_msg__msg__MsgCenter__get_type_hash,
  &cv_msg__msg__MsgCenter__get_type_description,
  &cv_msg__msg__MsgCenter__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, msg, MsgCenter)() {
  if (!cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_type_support_handle.typesupport_identifier) {
    cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cv_msg__msg__MsgCenter__rosidl_typesupport_introspection_c__MsgCenter_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
