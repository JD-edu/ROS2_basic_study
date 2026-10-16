// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice

#include "cv_msg/msg/detail/msg_center__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_type_hash_t *
cv_msg__msg__MsgCenter__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x85, 0x34, 0x0b, 0x96, 0x84, 0x4f, 0xd3, 0x76,
      0x14, 0x57, 0xa5, 0x5f, 0x5b, 0x8c, 0xe0, 0x0c,
      0xd1, 0x24, 0xdd, 0xfc, 0x81, 0x2d, 0x8f, 0xcd,
      0x44, 0xff, 0xf6, 0xeb, 0xdb, 0x37, 0xdb, 0x79,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char cv_msg__msg__MsgCenter__TYPE_NAME[] = "cv_msg/msg/MsgCenter";

// Define type names, field names, and default values
static char cv_msg__msg__MsgCenter__FIELD_NAME__x[] = "x";
static char cv_msg__msg__MsgCenter__FIELD_NAME__y[] = "y";

static rosidl_runtime_c__type_description__Field cv_msg__msg__MsgCenter__FIELDS[] = {
  {
    {cv_msg__msg__MsgCenter__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cv_msg__msg__MsgCenter__FIELD_NAME__y, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT64,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cv_msg__msg__MsgCenter__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cv_msg__msg__MsgCenter__TYPE_NAME, 20, 20},
      {cv_msg__msg__MsgCenter__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int64 x\n"
  "int64 y";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
cv_msg__msg__MsgCenter__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cv_msg__msg__MsgCenter__TYPE_NAME, 20, 20},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 16, 16},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cv_msg__msg__MsgCenter__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cv_msg__msg__MsgCenter__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
