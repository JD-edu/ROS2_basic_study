// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from cv_msg:srv/SrvArduino.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "cv_msg/srv/detail/srv_arduino__functions.h"
#include "cv_msg/srv/detail/srv_arduino__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SrvArduino_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_Request_type_support_ids_t;

static const _SrvArduino_Request_type_support_ids_t _SrvArduino_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cv_msg, srv, SrvArduino_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cv_msg, srv, SrvArduino_Request)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &cv_msg__srv__SrvArduino_Request__get_type_hash,
  &cv_msg__srv__SrvArduino_Request__get_type_description,
  &cv_msg__srv__SrvArduino_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cv_msg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cv_msg::srv::SrvArduino_Request>()
{
  return &::cv_msg::srv::rosidl_typesupport_cpp::SrvArduino_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cv_msg, srv, SrvArduino_Request)() {
  return get_message_type_support_handle<cv_msg::srv::SrvArduino_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__functions.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SrvArduino_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_Response_type_support_ids_t;

static const _SrvArduino_Response_type_support_ids_t _SrvArduino_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cv_msg, srv, SrvArduino_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cv_msg, srv, SrvArduino_Response)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &cv_msg__srv__SrvArduino_Response__get_type_hash,
  &cv_msg__srv__SrvArduino_Response__get_type_description,
  &cv_msg__srv__SrvArduino_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cv_msg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cv_msg::srv::SrvArduino_Response>()
{
  return &::cv_msg::srv::rosidl_typesupport_cpp::SrvArduino_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cv_msg, srv, SrvArduino_Response)() {
  return get_message_type_support_handle<cv_msg::srv::SrvArduino_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__functions.h"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SrvArduino_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_Event_type_support_ids_t;

static const _SrvArduino_Event_type_support_ids_t _SrvArduino_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cv_msg, srv, SrvArduino_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cv_msg, srv, SrvArduino_Event)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &cv_msg__srv__SrvArduino_Event__get_type_hash,
  &cv_msg__srv__SrvArduino_Event__get_type_description,
  &cv_msg__srv__SrvArduino_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cv_msg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cv_msg::srv::SrvArduino_Event>()
{
  return &::cv_msg::srv::rosidl_typesupport_cpp::SrvArduino_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, cv_msg, srv, SrvArduino_Event)() {
  return get_message_type_support_handle<cv_msg::srv::SrvArduino_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "cv_msg/srv/detail/srv_arduino__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cv_msg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SrvArduino_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SrvArduino_type_support_ids_t;

static const _SrvArduino_type_support_ids_t _SrvArduino_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, cv_msg, srv, SrvArduino)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cv_msg, srv, SrvArduino)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SrvArduino_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<cv_msg::srv::SrvArduino_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<cv_msg::srv::SrvArduino_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<cv_msg::srv::SrvArduino_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<cv_msg::srv::SrvArduino>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<cv_msg::srv::SrvArduino>,
  &cv_msg__srv__SrvArduino__get_type_hash,
  &cv_msg__srv__SrvArduino__get_type_description,
  &cv_msg__srv__SrvArduino__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace cv_msg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<cv_msg::srv::SrvArduino>()
{
  return &::cv_msg::srv::rosidl_typesupport_cpp::SrvArduino_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, cv_msg, srv, SrvArduino)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<cv_msg::srv::SrvArduino>();
}

#ifdef __cplusplus
}
#endif
