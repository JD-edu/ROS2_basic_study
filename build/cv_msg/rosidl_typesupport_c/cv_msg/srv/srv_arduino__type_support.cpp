// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from cv_msg:srv/SrvArduino.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "cv_msg/srv/detail/srv_arduino__struct.h"
#include "cv_msg/srv/detail/srv_arduino__type_support.h"
#include "cv_msg/srv/detail/srv_arduino__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _SrvArduino_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_Request_type_support_ids_t;

static const _SrvArduino_Request_type_support_ids_t _SrvArduino_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SrvArduino_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SrvArduino_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SrvArduino_Request_type_support_symbol_names_t _SrvArduino_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cv_msg, srv, SrvArduino_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvArduino_Request)),
  }
};

typedef struct _SrvArduino_Request_type_support_data_t
{
  void * data[2];
} _SrvArduino_Request_type_support_data_t;

static _SrvArduino_Request_type_support_data_t _SrvArduino_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SrvArduino_Request_message_typesupport_map = {
  2,
  "cv_msg",
  &_SrvArduino_Request_message_typesupport_ids.typesupport_identifier[0],
  &_SrvArduino_Request_message_typesupport_symbol_names.symbol_name[0],
  &_SrvArduino_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SrvArduino_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &cv_msg__srv__SrvArduino_Request__get_type_hash,
  &cv_msg__srv__SrvArduino_Request__get_type_description,
  &cv_msg__srv__SrvArduino_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cv_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, cv_msg, srv, SrvArduino_Request)() {
  return &::cv_msg::srv::rosidl_typesupport_c::SrvArduino_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__type_support.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _SrvArduino_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_Response_type_support_ids_t;

static const _SrvArduino_Response_type_support_ids_t _SrvArduino_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SrvArduino_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SrvArduino_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SrvArduino_Response_type_support_symbol_names_t _SrvArduino_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cv_msg, srv, SrvArduino_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvArduino_Response)),
  }
};

typedef struct _SrvArduino_Response_type_support_data_t
{
  void * data[2];
} _SrvArduino_Response_type_support_data_t;

static _SrvArduino_Response_type_support_data_t _SrvArduino_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SrvArduino_Response_message_typesupport_map = {
  2,
  "cv_msg",
  &_SrvArduino_Response_message_typesupport_ids.typesupport_identifier[0],
  &_SrvArduino_Response_message_typesupport_symbol_names.symbol_name[0],
  &_SrvArduino_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SrvArduino_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &cv_msg__srv__SrvArduino_Response__get_type_hash,
  &cv_msg__srv__SrvArduino_Response__get_type_description,
  &cv_msg__srv__SrvArduino_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cv_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, cv_msg, srv, SrvArduino_Response)() {
  return &::cv_msg::srv::rosidl_typesupport_c::SrvArduino_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__type_support.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _SrvArduino_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_Event_type_support_ids_t;

static const _SrvArduino_Event_type_support_ids_t _SrvArduino_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SrvArduino_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SrvArduino_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SrvArduino_Event_type_support_symbol_names_t _SrvArduino_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cv_msg, srv, SrvArduino_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvArduino_Event)),
  }
};

typedef struct _SrvArduino_Event_type_support_data_t
{
  void * data[2];
} _SrvArduino_Event_type_support_data_t;

static _SrvArduino_Event_type_support_data_t _SrvArduino_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SrvArduino_Event_message_typesupport_map = {
  2,
  "cv_msg",
  &_SrvArduino_Event_message_typesupport_ids.typesupport_identifier[0],
  &_SrvArduino_Event_message_typesupport_symbol_names.symbol_name[0],
  &_SrvArduino_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SrvArduino_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &cv_msg__srv__SrvArduino_Event__get_type_hash,
  &cv_msg__srv__SrvArduino_Event__get_type_description,
  &cv_msg__srv__SrvArduino_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cv_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, cv_msg, srv, SrvArduino_Event)() {
  return &::cv_msg::srv::rosidl_typesupport_c::SrvArduino_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _SrvArduino_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_type_support_ids_t;

static const _SrvArduino_type_support_ids_t _SrvArduino_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _SrvArduino_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SrvArduino_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SrvArduino_type_support_symbol_names_t _SrvArduino_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cv_msg, srv, SrvArduino)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cv_msg, srv, SrvArduino)),
  }
};

typedef struct _SrvArduino_type_support_data_t
{
  void * data[2];
} _SrvArduino_type_support_data_t;

static _SrvArduino_type_support_data_t _SrvArduino_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SrvArduino_service_typesupport_map = {
  2,
  "cv_msg",
  &_SrvArduino_service_typesupport_ids.typesupport_identifier[0],
  &_SrvArduino_service_typesupport_symbol_names.symbol_name[0],
  &_SrvArduino_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t SrvArduino_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &SrvArduino_Request_message_type_support_handle,
  &SrvArduino_Response_message_type_support_handle,
  &SrvArduino_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cv_msg,
    srv,
    SrvArduino
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cv_msg,
    srv,
    SrvArduino
  ),
  &cv_msg__srv__SrvArduino__get_type_hash,
  &cv_msg__srv__SrvArduino__get_type_description,
  &cv_msg__srv__SrvArduino__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cv_msg

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, cv_msg, srv, SrvArduino)() {
  return &::cv_msg::srv::rosidl_typesupport_c::SrvArduino_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
