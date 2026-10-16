// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/msg/msg_center.h"


#ifndef CV_MSG__MSG__DETAIL__MSG_CENTER__FUNCTIONS_H_
#define CV_MSG__MSG__DETAIL__MSG_CENTER__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "cv_msg/msg/rosidl_generator_c__visibility_control.h"

#include "cv_msg/msg/detail/msg_center__struct.h"

/// Initialize msg/MsgCenter message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cv_msg__msg__MsgCenter
 * )) before or use
 * cv_msg__msg__MsgCenter__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__msg__MsgCenter__init(cv_msg__msg__MsgCenter * msg);

/// Finalize msg/MsgCenter message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__msg__MsgCenter__fini(cv_msg__msg__MsgCenter * msg);

/// Create msg/MsgCenter message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cv_msg__msg__MsgCenter__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__msg__MsgCenter *
cv_msg__msg__MsgCenter__create(void);

/// Destroy msg/MsgCenter message.
/**
 * It calls
 * cv_msg__msg__MsgCenter__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__msg__MsgCenter__destroy(cv_msg__msg__MsgCenter * msg);

/// Check for msg/MsgCenter message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__msg__MsgCenter__are_equal(const cv_msg__msg__MsgCenter * lhs, const cv_msg__msg__MsgCenter * rhs);

/// Copy a msg/MsgCenter message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__msg__MsgCenter__copy(
  const cv_msg__msg__MsgCenter * input,
  cv_msg__msg__MsgCenter * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_type_hash_t *
cv_msg__msg__MsgCenter__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeDescription *
cv_msg__msg__MsgCenter__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource *
cv_msg__msg__MsgCenter__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cv_msg__msg__MsgCenter__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/MsgCenter messages.
/**
 * It allocates the memory for the number of elements and calls
 * cv_msg__msg__MsgCenter__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__msg__MsgCenter__Sequence__init(cv_msg__msg__MsgCenter__Sequence * array, size_t size);

/// Finalize array of msg/MsgCenter messages.
/**
 * It calls
 * cv_msg__msg__MsgCenter__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__msg__MsgCenter__Sequence__fini(cv_msg__msg__MsgCenter__Sequence * array);

/// Create array of msg/MsgCenter messages.
/**
 * It allocates the memory for the array and calls
 * cv_msg__msg__MsgCenter__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__msg__MsgCenter__Sequence *
cv_msg__msg__MsgCenter__Sequence__create(size_t size);

/// Destroy array of msg/MsgCenter messages.
/**
 * It calls
 * cv_msg__msg__MsgCenter__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__msg__MsgCenter__Sequence__destroy(cv_msg__msg__MsgCenter__Sequence * array);

/// Check for msg/MsgCenter message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__msg__MsgCenter__Sequence__are_equal(const cv_msg__msg__MsgCenter__Sequence * lhs, const cv_msg__msg__MsgCenter__Sequence * rhs);

/// Copy an array of msg/MsgCenter messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__msg__MsgCenter__Sequence__copy(
  const cv_msg__msg__MsgCenter__Sequence * input,
  cv_msg__msg__MsgCenter__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CV_MSG__MSG__DETAIL__MSG_CENTER__FUNCTIONS_H_
