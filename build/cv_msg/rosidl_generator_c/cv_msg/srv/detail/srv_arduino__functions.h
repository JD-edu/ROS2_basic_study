// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from cv_msg:srv/SrvArduino.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cv_msg/srv/srv_arduino.h"


#ifndef CV_MSG__SRV__DETAIL__SRV_ARDUINO__FUNCTIONS_H_
#define CV_MSG__SRV__DETAIL__SRV_ARDUINO__FUNCTIONS_H_

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

#include "cv_msg/srv/detail/srv_arduino__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_type_hash_t *
cv_msg__srv__SrvArduino__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeDescription *
cv_msg__srv__SrvArduino__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource *
cv_msg__srv__SrvArduino__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cv_msg__srv__SrvArduino__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/SrvArduino message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cv_msg__srv__SrvArduino_Request
 * )) before or use
 * cv_msg__srv__SrvArduino_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Request__init(cv_msg__srv__SrvArduino_Request * msg);

/// Finalize srv/SrvArduino message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Request__fini(cv_msg__srv__SrvArduino_Request * msg);

/// Create srv/SrvArduino message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cv_msg__srv__SrvArduino_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__srv__SrvArduino_Request *
cv_msg__srv__SrvArduino_Request__create(void);

/// Destroy srv/SrvArduino message.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Request__destroy(cv_msg__srv__SrvArduino_Request * msg);

/// Check for srv/SrvArduino message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Request__are_equal(const cv_msg__srv__SrvArduino_Request * lhs, const cv_msg__srv__SrvArduino_Request * rhs);

/// Copy a srv/SrvArduino message.
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
cv_msg__srv__SrvArduino_Request__copy(
  const cv_msg__srv__SrvArduino_Request * input,
  cv_msg__srv__SrvArduino_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_type_hash_t *
cv_msg__srv__SrvArduino_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeDescription *
cv_msg__srv__SrvArduino_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource *
cv_msg__srv__SrvArduino_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cv_msg__srv__SrvArduino_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/SrvArduino messages.
/**
 * It allocates the memory for the number of elements and calls
 * cv_msg__srv__SrvArduino_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Request__Sequence__init(cv_msg__srv__SrvArduino_Request__Sequence * array, size_t size);

/// Finalize array of srv/SrvArduino messages.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Request__Sequence__fini(cv_msg__srv__SrvArduino_Request__Sequence * array);

/// Create array of srv/SrvArduino messages.
/**
 * It allocates the memory for the array and calls
 * cv_msg__srv__SrvArduino_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__srv__SrvArduino_Request__Sequence *
cv_msg__srv__SrvArduino_Request__Sequence__create(size_t size);

/// Destroy array of srv/SrvArduino messages.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Request__Sequence__destroy(cv_msg__srv__SrvArduino_Request__Sequence * array);

/// Check for srv/SrvArduino message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Request__Sequence__are_equal(const cv_msg__srv__SrvArduino_Request__Sequence * lhs, const cv_msg__srv__SrvArduino_Request__Sequence * rhs);

/// Copy an array of srv/SrvArduino messages.
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
cv_msg__srv__SrvArduino_Request__Sequence__copy(
  const cv_msg__srv__SrvArduino_Request__Sequence * input,
  cv_msg__srv__SrvArduino_Request__Sequence * output);

/// Initialize srv/SrvArduino message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cv_msg__srv__SrvArduino_Response
 * )) before or use
 * cv_msg__srv__SrvArduino_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Response__init(cv_msg__srv__SrvArduino_Response * msg);

/// Finalize srv/SrvArduino message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Response__fini(cv_msg__srv__SrvArduino_Response * msg);

/// Create srv/SrvArduino message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cv_msg__srv__SrvArduino_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__srv__SrvArduino_Response *
cv_msg__srv__SrvArduino_Response__create(void);

/// Destroy srv/SrvArduino message.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Response__destroy(cv_msg__srv__SrvArduino_Response * msg);

/// Check for srv/SrvArduino message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Response__are_equal(const cv_msg__srv__SrvArduino_Response * lhs, const cv_msg__srv__SrvArduino_Response * rhs);

/// Copy a srv/SrvArduino message.
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
cv_msg__srv__SrvArduino_Response__copy(
  const cv_msg__srv__SrvArduino_Response * input,
  cv_msg__srv__SrvArduino_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_type_hash_t *
cv_msg__srv__SrvArduino_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeDescription *
cv_msg__srv__SrvArduino_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource *
cv_msg__srv__SrvArduino_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cv_msg__srv__SrvArduino_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/SrvArduino messages.
/**
 * It allocates the memory for the number of elements and calls
 * cv_msg__srv__SrvArduino_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Response__Sequence__init(cv_msg__srv__SrvArduino_Response__Sequence * array, size_t size);

/// Finalize array of srv/SrvArduino messages.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Response__Sequence__fini(cv_msg__srv__SrvArduino_Response__Sequence * array);

/// Create array of srv/SrvArduino messages.
/**
 * It allocates the memory for the array and calls
 * cv_msg__srv__SrvArduino_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__srv__SrvArduino_Response__Sequence *
cv_msg__srv__SrvArduino_Response__Sequence__create(size_t size);

/// Destroy array of srv/SrvArduino messages.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Response__Sequence__destroy(cv_msg__srv__SrvArduino_Response__Sequence * array);

/// Check for srv/SrvArduino message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Response__Sequence__are_equal(const cv_msg__srv__SrvArduino_Response__Sequence * lhs, const cv_msg__srv__SrvArduino_Response__Sequence * rhs);

/// Copy an array of srv/SrvArduino messages.
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
cv_msg__srv__SrvArduino_Response__Sequence__copy(
  const cv_msg__srv__SrvArduino_Response__Sequence * input,
  cv_msg__srv__SrvArduino_Response__Sequence * output);

/// Initialize srv/SrvArduino message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * cv_msg__srv__SrvArduino_Event
 * )) before or use
 * cv_msg__srv__SrvArduino_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Event__init(cv_msg__srv__SrvArduino_Event * msg);

/// Finalize srv/SrvArduino message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Event__fini(cv_msg__srv__SrvArduino_Event * msg);

/// Create srv/SrvArduino message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * cv_msg__srv__SrvArduino_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__srv__SrvArduino_Event *
cv_msg__srv__SrvArduino_Event__create(void);

/// Destroy srv/SrvArduino message.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Event__destroy(cv_msg__srv__SrvArduino_Event * msg);

/// Check for srv/SrvArduino message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Event__are_equal(const cv_msg__srv__SrvArduino_Event * lhs, const cv_msg__srv__SrvArduino_Event * rhs);

/// Copy a srv/SrvArduino message.
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
cv_msg__srv__SrvArduino_Event__copy(
  const cv_msg__srv__SrvArduino_Event * input,
  cv_msg__srv__SrvArduino_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_type_hash_t *
cv_msg__srv__SrvArduino_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeDescription *
cv_msg__srv__SrvArduino_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource *
cv_msg__srv__SrvArduino_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
const rosidl_runtime_c__type_description__TypeSource__Sequence *
cv_msg__srv__SrvArduino_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/SrvArduino messages.
/**
 * It allocates the memory for the number of elements and calls
 * cv_msg__srv__SrvArduino_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Event__Sequence__init(cv_msg__srv__SrvArduino_Event__Sequence * array, size_t size);

/// Finalize array of srv/SrvArduino messages.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Event__Sequence__fini(cv_msg__srv__SrvArduino_Event__Sequence * array);

/// Create array of srv/SrvArduino messages.
/**
 * It allocates the memory for the array and calls
 * cv_msg__srv__SrvArduino_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
cv_msg__srv__SrvArduino_Event__Sequence *
cv_msg__srv__SrvArduino_Event__Sequence__create(size_t size);

/// Destroy array of srv/SrvArduino messages.
/**
 * It calls
 * cv_msg__srv__SrvArduino_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
void
cv_msg__srv__SrvArduino_Event__Sequence__destroy(cv_msg__srv__SrvArduino_Event__Sequence * array);

/// Check for srv/SrvArduino message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_cv_msg
bool
cv_msg__srv__SrvArduino_Event__Sequence__are_equal(const cv_msg__srv__SrvArduino_Event__Sequence * lhs, const cv_msg__srv__SrvArduino_Event__Sequence * rhs);

/// Copy an array of srv/SrvArduino messages.
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
cv_msg__srv__SrvArduino_Event__Sequence__copy(
  const cv_msg__srv__SrvArduino_Event__Sequence * input,
  cv_msg__srv__SrvArduino_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // CV_MSG__SRV__DETAIL__SRV_ARDUINO__FUNCTIONS_H_
