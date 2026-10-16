// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cv_msg:srv/SrvAddint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cv_msg/srv/detail/srv_addint__rosidl_typesupport_introspection_c.h"
#include "cv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cv_msg/srv/detail/srv_addint__functions.h"
#include "cv_msg/srv/detail/srv_addint__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cv_msg__srv__SrvAddint_Request__init(message_memory);
}

void cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_fini_function(void * message_memory)
{
  cv_msg__srv__SrvAddint_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_member_array[2] = {
  {
    "a",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cv_msg__srv__SrvAddint_Request, a),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "b",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cv_msg__srv__SrvAddint_Request, b),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_members = {
  "cv_msg__srv",  // message namespace
  "SrvAddint_Request",  // message name
  2,  // number of fields
  sizeof(cv_msg__srv__SrvAddint_Request),
  false,  // has_any_key_member_
  cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_member_array,  // message members
  cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_type_support_handle = {
  0,
  &cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_members,
  get_message_typesupport_handle_function,
  &cv_msg__srv__SrvAddint_Request__get_type_hash,
  &cv_msg__srv__SrvAddint_Request__get_type_description,
  &cv_msg__srv__SrvAddint_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Request)() {
  if (!cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_type_support_handle.typesupport_identifier) {
    cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cv_msg/srv/detail/srv_addint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cv_msg/srv/detail/srv_addint__functions.h"
// already included above
// #include "cv_msg/srv/detail/srv_addint__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cv_msg__srv__SrvAddint_Response__init(message_memory);
}

void cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_fini_function(void * message_memory)
{
  cv_msg__srv__SrvAddint_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_member_array[1] = {
  {
    "sum",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cv_msg__srv__SrvAddint_Response, sum),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_members = {
  "cv_msg__srv",  // message namespace
  "SrvAddint_Response",  // message name
  1,  // number of fields
  sizeof(cv_msg__srv__SrvAddint_Response),
  false,  // has_any_key_member_
  cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_member_array,  // message members
  cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle = {
  0,
  &cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_members,
  get_message_typesupport_handle_function,
  &cv_msg__srv__SrvAddint_Response__get_type_hash,
  &cv_msg__srv__SrvAddint_Response__get_type_description,
  &cv_msg__srv__SrvAddint_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Response)() {
  if (!cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle.typesupport_identifier) {
    cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cv_msg/srv/detail/srv_addint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cv_msg/srv/detail/srv_addint__functions.h"
// already included above
// #include "cv_msg/srv/detail/srv_addint__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "cv_msg/srv/srv_addint.h"
// Member `request`
// Member `response`
// already included above
// #include "cv_msg/srv/detail/srv_addint__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cv_msg__srv__SrvAddint_Event__init(message_memory);
}

void cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_fini_function(void * message_memory)
{
  cv_msg__srv__SrvAddint_Event__fini(message_memory);
}

size_t cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__size_function__SrvAddint_Event__request(
  const void * untyped_member)
{
  const cv_msg__srv__SrvAddint_Request__Sequence * member =
    (const cv_msg__srv__SrvAddint_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_const_function__SrvAddint_Event__request(
  const void * untyped_member, size_t index)
{
  const cv_msg__srv__SrvAddint_Request__Sequence * member =
    (const cv_msg__srv__SrvAddint_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_function__SrvAddint_Event__request(
  void * untyped_member, size_t index)
{
  cv_msg__srv__SrvAddint_Request__Sequence * member =
    (cv_msg__srv__SrvAddint_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__fetch_function__SrvAddint_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cv_msg__srv__SrvAddint_Request * item =
    ((const cv_msg__srv__SrvAddint_Request *)
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_const_function__SrvAddint_Event__request(untyped_member, index));
  cv_msg__srv__SrvAddint_Request * value =
    (cv_msg__srv__SrvAddint_Request *)(untyped_value);
  *value = *item;
}

void cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__assign_function__SrvAddint_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cv_msg__srv__SrvAddint_Request * item =
    ((cv_msg__srv__SrvAddint_Request *)
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_function__SrvAddint_Event__request(untyped_member, index));
  const cv_msg__srv__SrvAddint_Request * value =
    (const cv_msg__srv__SrvAddint_Request *)(untyped_value);
  *item = *value;
}

bool cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__resize_function__SrvAddint_Event__request(
  void * untyped_member, size_t size)
{
  cv_msg__srv__SrvAddint_Request__Sequence * member =
    (cv_msg__srv__SrvAddint_Request__Sequence *)(untyped_member);
  cv_msg__srv__SrvAddint_Request__Sequence__fini(member);
  return cv_msg__srv__SrvAddint_Request__Sequence__init(member, size);
}

size_t cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__size_function__SrvAddint_Event__response(
  const void * untyped_member)
{
  const cv_msg__srv__SrvAddint_Response__Sequence * member =
    (const cv_msg__srv__SrvAddint_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_const_function__SrvAddint_Event__response(
  const void * untyped_member, size_t index)
{
  const cv_msg__srv__SrvAddint_Response__Sequence * member =
    (const cv_msg__srv__SrvAddint_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_function__SrvAddint_Event__response(
  void * untyped_member, size_t index)
{
  cv_msg__srv__SrvAddint_Response__Sequence * member =
    (cv_msg__srv__SrvAddint_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__fetch_function__SrvAddint_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cv_msg__srv__SrvAddint_Response * item =
    ((const cv_msg__srv__SrvAddint_Response *)
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_const_function__SrvAddint_Event__response(untyped_member, index));
  cv_msg__srv__SrvAddint_Response * value =
    (cv_msg__srv__SrvAddint_Response *)(untyped_value);
  *value = *item;
}

void cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__assign_function__SrvAddint_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cv_msg__srv__SrvAddint_Response * item =
    ((cv_msg__srv__SrvAddint_Response *)
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_function__SrvAddint_Event__response(untyped_member, index));
  const cv_msg__srv__SrvAddint_Response * value =
    (const cv_msg__srv__SrvAddint_Response *)(untyped_value);
  *item = *value;
}

bool cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__resize_function__SrvAddint_Event__response(
  void * untyped_member, size_t size)
{
  cv_msg__srv__SrvAddint_Response__Sequence * member =
    (cv_msg__srv__SrvAddint_Response__Sequence *)(untyped_member);
  cv_msg__srv__SrvAddint_Response__Sequence__fini(member);
  return cv_msg__srv__SrvAddint_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cv_msg__srv__SrvAddint_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(cv_msg__srv__SrvAddint_Event, request),  // bytes offset in struct
    NULL,  // default value
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__size_function__SrvAddint_Event__request,  // size() function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_const_function__SrvAddint_Event__request,  // get_const(index) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_function__SrvAddint_Event__request,  // get(index) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__fetch_function__SrvAddint_Event__request,  // fetch(index, &value) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__assign_function__SrvAddint_Event__request,  // assign(index, value) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__resize_function__SrvAddint_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(cv_msg__srv__SrvAddint_Event, response),  // bytes offset in struct
    NULL,  // default value
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__size_function__SrvAddint_Event__response,  // size() function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_const_function__SrvAddint_Event__response,  // get_const(index) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__get_function__SrvAddint_Event__response,  // get(index) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__fetch_function__SrvAddint_Event__response,  // fetch(index, &value) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__assign_function__SrvAddint_Event__response,  // assign(index, value) function pointer
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__resize_function__SrvAddint_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_members = {
  "cv_msg__srv",  // message namespace
  "SrvAddint_Event",  // message name
  3,  // number of fields
  sizeof(cv_msg__srv__SrvAddint_Event),
  false,  // has_any_key_member_
  cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_member_array,  // message members
  cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_type_support_handle = {
  0,
  &cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_members,
  get_message_typesupport_handle_function,
  &cv_msg__srv__SrvAddint_Event__get_type_hash,
  &cv_msg__srv__SrvAddint_Event__get_type_description,
  &cv_msg__srv__SrvAddint_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cv_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Event)() {
  cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Request)();
  cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Response)();
  if (!cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_type_support_handle.typesupport_identifier) {
    cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cv_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cv_msg/srv/detail/srv_addint__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_members = {
  "cv_msg__srv",  // service namespace
  "SrvAddint",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_Request_message_type_support_handle,
  NULL,  // response message
  // cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle
  NULL  // event_message
  // cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle
};


static rosidl_service_type_support_t cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_type_support_handle = {
  0,
  &cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_members,
  get_service_typesupport_handle_function,
  &cv_msg__srv__SrvAddint_Request__rosidl_typesupport_introspection_c__SrvAddint_Request_message_type_support_handle,
  &cv_msg__srv__SrvAddint_Response__rosidl_typesupport_introspection_c__SrvAddint_Response_message_type_support_handle,
  &cv_msg__srv__SrvAddint_Event__rosidl_typesupport_introspection_c__SrvAddint_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cv_msg,
    srv,
    SrvAddint
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cv_msg,
    srv,
    SrvAddint
  ),
  &cv_msg__srv__SrvAddint__get_type_hash,
  &cv_msg__srv__SrvAddint__get_type_description,
  &cv_msg__srv__SrvAddint__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cv_msg
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint)(void) {
  if (!cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_type_support_handle.typesupport_identifier) {
    cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvAddint_Event)()->data;
  }

  return &cv_msg__srv__detail__srv_addint__rosidl_typesupport_introspection_c__SrvAddint_service_type_support_handle;
}
