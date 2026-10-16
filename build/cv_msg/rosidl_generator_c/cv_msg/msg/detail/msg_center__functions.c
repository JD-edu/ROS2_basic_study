// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cv_msg:msg/MsgCenter.idl
// generated code does not contain a copyright notice
#include "cv_msg/msg/detail/msg_center__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
cv_msg__msg__MsgCenter__init(cv_msg__msg__MsgCenter * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  return true;
}

void
cv_msg__msg__MsgCenter__fini(cv_msg__msg__MsgCenter * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
}

bool
cv_msg__msg__MsgCenter__are_equal(const cv_msg__msg__MsgCenter * lhs, const cv_msg__msg__MsgCenter * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  return true;
}

bool
cv_msg__msg__MsgCenter__copy(
  const cv_msg__msg__MsgCenter * input,
  cv_msg__msg__MsgCenter * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  return true;
}

cv_msg__msg__MsgCenter *
cv_msg__msg__MsgCenter__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__msg__MsgCenter * msg = (cv_msg__msg__MsgCenter *)allocator.allocate(sizeof(cv_msg__msg__MsgCenter), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cv_msg__msg__MsgCenter));
  bool success = cv_msg__msg__MsgCenter__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cv_msg__msg__MsgCenter__destroy(cv_msg__msg__MsgCenter * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cv_msg__msg__MsgCenter__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cv_msg__msg__MsgCenter__Sequence__init(cv_msg__msg__MsgCenter__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__msg__MsgCenter * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cv_msg__msg__MsgCenter)) {
      return false;
    }
    data = (cv_msg__msg__MsgCenter *)allocator.zero_allocate(size, sizeof(cv_msg__msg__MsgCenter), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cv_msg__msg__MsgCenter__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cv_msg__msg__MsgCenter__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cv_msg__msg__MsgCenter__Sequence__fini(cv_msg__msg__MsgCenter__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cv_msg__msg__MsgCenter__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cv_msg__msg__MsgCenter__Sequence *
cv_msg__msg__MsgCenter__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__msg__MsgCenter__Sequence * array = (cv_msg__msg__MsgCenter__Sequence *)allocator.allocate(sizeof(cv_msg__msg__MsgCenter__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cv_msg__msg__MsgCenter__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cv_msg__msg__MsgCenter__Sequence__destroy(cv_msg__msg__MsgCenter__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cv_msg__msg__MsgCenter__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cv_msg__msg__MsgCenter__Sequence__are_equal(const cv_msg__msg__MsgCenter__Sequence * lhs, const cv_msg__msg__MsgCenter__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cv_msg__msg__MsgCenter__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cv_msg__msg__MsgCenter__Sequence__copy(
  const cv_msg__msg__MsgCenter__Sequence * input,
  cv_msg__msg__MsgCenter__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cv_msg__msg__MsgCenter)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cv_msg__msg__MsgCenter);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cv_msg__msg__MsgCenter * data =
      (cv_msg__msg__MsgCenter *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cv_msg__msg__MsgCenter__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cv_msg__msg__MsgCenter__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cv_msg__msg__MsgCenter__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
