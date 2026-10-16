// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cv_msg:srv/SrvAddint.idl
// generated code does not contain a copyright notice
#include "cv_msg/srv/detail/srv_addint__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
cv_msg__srv__SrvAddint_Request__init(cv_msg__srv__SrvAddint_Request * msg)
{
  if (!msg) {
    return false;
  }
  // a
  // b
  return true;
}

void
cv_msg__srv__SrvAddint_Request__fini(cv_msg__srv__SrvAddint_Request * msg)
{
  if (!msg) {
    return;
  }
  // a
  // b
}

bool
cv_msg__srv__SrvAddint_Request__are_equal(const cv_msg__srv__SrvAddint_Request * lhs, const cv_msg__srv__SrvAddint_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  return true;
}

bool
cv_msg__srv__SrvAddint_Request__copy(
  const cv_msg__srv__SrvAddint_Request * input,
  cv_msg__srv__SrvAddint_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // a
  output->a = input->a;
  // b
  output->b = input->b;
  return true;
}

cv_msg__srv__SrvAddint_Request *
cv_msg__srv__SrvAddint_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Request * msg = (cv_msg__srv__SrvAddint_Request *)allocator.allocate(sizeof(cv_msg__srv__SrvAddint_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cv_msg__srv__SrvAddint_Request));
  bool success = cv_msg__srv__SrvAddint_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cv_msg__srv__SrvAddint_Request__destroy(cv_msg__srv__SrvAddint_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cv_msg__srv__SrvAddint_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cv_msg__srv__SrvAddint_Request__Sequence__init(cv_msg__srv__SrvAddint_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cv_msg__srv__SrvAddint_Request)) {
      return false;
    }
    data = (cv_msg__srv__SrvAddint_Request *)allocator.zero_allocate(size, sizeof(cv_msg__srv__SrvAddint_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cv_msg__srv__SrvAddint_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cv_msg__srv__SrvAddint_Request__fini(&data[i - 1]);
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
cv_msg__srv__SrvAddint_Request__Sequence__fini(cv_msg__srv__SrvAddint_Request__Sequence * array)
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
      cv_msg__srv__SrvAddint_Request__fini(&array->data[i]);
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

cv_msg__srv__SrvAddint_Request__Sequence *
cv_msg__srv__SrvAddint_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Request__Sequence * array = (cv_msg__srv__SrvAddint_Request__Sequence *)allocator.allocate(sizeof(cv_msg__srv__SrvAddint_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cv_msg__srv__SrvAddint_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cv_msg__srv__SrvAddint_Request__Sequence__destroy(cv_msg__srv__SrvAddint_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cv_msg__srv__SrvAddint_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cv_msg__srv__SrvAddint_Request__Sequence__are_equal(const cv_msg__srv__SrvAddint_Request__Sequence * lhs, const cv_msg__srv__SrvAddint_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cv_msg__srv__SrvAddint_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cv_msg__srv__SrvAddint_Request__Sequence__copy(
  const cv_msg__srv__SrvAddint_Request__Sequence * input,
  cv_msg__srv__SrvAddint_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cv_msg__srv__SrvAddint_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cv_msg__srv__SrvAddint_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cv_msg__srv__SrvAddint_Request * data =
      (cv_msg__srv__SrvAddint_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cv_msg__srv__SrvAddint_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cv_msg__srv__SrvAddint_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cv_msg__srv__SrvAddint_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
cv_msg__srv__SrvAddint_Response__init(cv_msg__srv__SrvAddint_Response * msg)
{
  if (!msg) {
    return false;
  }
  // sum
  return true;
}

void
cv_msg__srv__SrvAddint_Response__fini(cv_msg__srv__SrvAddint_Response * msg)
{
  if (!msg) {
    return;
  }
  // sum
}

bool
cv_msg__srv__SrvAddint_Response__are_equal(const cv_msg__srv__SrvAddint_Response * lhs, const cv_msg__srv__SrvAddint_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sum
  if (lhs->sum != rhs->sum) {
    return false;
  }
  return true;
}

bool
cv_msg__srv__SrvAddint_Response__copy(
  const cv_msg__srv__SrvAddint_Response * input,
  cv_msg__srv__SrvAddint_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // sum
  output->sum = input->sum;
  return true;
}

cv_msg__srv__SrvAddint_Response *
cv_msg__srv__SrvAddint_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Response * msg = (cv_msg__srv__SrvAddint_Response *)allocator.allocate(sizeof(cv_msg__srv__SrvAddint_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cv_msg__srv__SrvAddint_Response));
  bool success = cv_msg__srv__SrvAddint_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cv_msg__srv__SrvAddint_Response__destroy(cv_msg__srv__SrvAddint_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cv_msg__srv__SrvAddint_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cv_msg__srv__SrvAddint_Response__Sequence__init(cv_msg__srv__SrvAddint_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cv_msg__srv__SrvAddint_Response)) {
      return false;
    }
    data = (cv_msg__srv__SrvAddint_Response *)allocator.zero_allocate(size, sizeof(cv_msg__srv__SrvAddint_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cv_msg__srv__SrvAddint_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cv_msg__srv__SrvAddint_Response__fini(&data[i - 1]);
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
cv_msg__srv__SrvAddint_Response__Sequence__fini(cv_msg__srv__SrvAddint_Response__Sequence * array)
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
      cv_msg__srv__SrvAddint_Response__fini(&array->data[i]);
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

cv_msg__srv__SrvAddint_Response__Sequence *
cv_msg__srv__SrvAddint_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Response__Sequence * array = (cv_msg__srv__SrvAddint_Response__Sequence *)allocator.allocate(sizeof(cv_msg__srv__SrvAddint_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cv_msg__srv__SrvAddint_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cv_msg__srv__SrvAddint_Response__Sequence__destroy(cv_msg__srv__SrvAddint_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cv_msg__srv__SrvAddint_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cv_msg__srv__SrvAddint_Response__Sequence__are_equal(const cv_msg__srv__SrvAddint_Response__Sequence * lhs, const cv_msg__srv__SrvAddint_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cv_msg__srv__SrvAddint_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cv_msg__srv__SrvAddint_Response__Sequence__copy(
  const cv_msg__srv__SrvAddint_Response__Sequence * input,
  cv_msg__srv__SrvAddint_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cv_msg__srv__SrvAddint_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cv_msg__srv__SrvAddint_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cv_msg__srv__SrvAddint_Response * data =
      (cv_msg__srv__SrvAddint_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cv_msg__srv__SrvAddint_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cv_msg__srv__SrvAddint_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cv_msg__srv__SrvAddint_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "cv_msg/srv/detail/srv_addint__functions.h"

bool
cv_msg__srv__SrvAddint_Event__init(cv_msg__srv__SrvAddint_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    cv_msg__srv__SrvAddint_Event__fini(msg);
    return false;
  }
  // request
  if (!cv_msg__srv__SrvAddint_Request__Sequence__init(&msg->request, 0)) {
    cv_msg__srv__SrvAddint_Event__fini(msg);
    return false;
  }
  // response
  if (!cv_msg__srv__SrvAddint_Response__Sequence__init(&msg->response, 0)) {
    cv_msg__srv__SrvAddint_Event__fini(msg);
    return false;
  }
  return true;
}

void
cv_msg__srv__SrvAddint_Event__fini(cv_msg__srv__SrvAddint_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  cv_msg__srv__SrvAddint_Request__Sequence__fini(&msg->request);
  // response
  cv_msg__srv__SrvAddint_Response__Sequence__fini(&msg->response);
}

bool
cv_msg__srv__SrvAddint_Event__are_equal(const cv_msg__srv__SrvAddint_Event * lhs, const cv_msg__srv__SrvAddint_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!cv_msg__srv__SrvAddint_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!cv_msg__srv__SrvAddint_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
cv_msg__srv__SrvAddint_Event__copy(
  const cv_msg__srv__SrvAddint_Event * input,
  cv_msg__srv__SrvAddint_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!cv_msg__srv__SrvAddint_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!cv_msg__srv__SrvAddint_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

cv_msg__srv__SrvAddint_Event *
cv_msg__srv__SrvAddint_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Event * msg = (cv_msg__srv__SrvAddint_Event *)allocator.allocate(sizeof(cv_msg__srv__SrvAddint_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cv_msg__srv__SrvAddint_Event));
  bool success = cv_msg__srv__SrvAddint_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cv_msg__srv__SrvAddint_Event__destroy(cv_msg__srv__SrvAddint_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cv_msg__srv__SrvAddint_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cv_msg__srv__SrvAddint_Event__Sequence__init(cv_msg__srv__SrvAddint_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cv_msg__srv__SrvAddint_Event)) {
      return false;
    }
    data = (cv_msg__srv__SrvAddint_Event *)allocator.zero_allocate(size, sizeof(cv_msg__srv__SrvAddint_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cv_msg__srv__SrvAddint_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cv_msg__srv__SrvAddint_Event__fini(&data[i - 1]);
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
cv_msg__srv__SrvAddint_Event__Sequence__fini(cv_msg__srv__SrvAddint_Event__Sequence * array)
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
      cv_msg__srv__SrvAddint_Event__fini(&array->data[i]);
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

cv_msg__srv__SrvAddint_Event__Sequence *
cv_msg__srv__SrvAddint_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cv_msg__srv__SrvAddint_Event__Sequence * array = (cv_msg__srv__SrvAddint_Event__Sequence *)allocator.allocate(sizeof(cv_msg__srv__SrvAddint_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cv_msg__srv__SrvAddint_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cv_msg__srv__SrvAddint_Event__Sequence__destroy(cv_msg__srv__SrvAddint_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cv_msg__srv__SrvAddint_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cv_msg__srv__SrvAddint_Event__Sequence__are_equal(const cv_msg__srv__SrvAddint_Event__Sequence * lhs, const cv_msg__srv__SrvAddint_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cv_msg__srv__SrvAddint_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cv_msg__srv__SrvAddint_Event__Sequence__copy(
  const cv_msg__srv__SrvAddint_Event__Sequence * input,
  cv_msg__srv__SrvAddint_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cv_msg__srv__SrvAddint_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cv_msg__srv__SrvAddint_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cv_msg__srv__SrvAddint_Event * data =
      (cv_msg__srv__SrvAddint_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cv_msg__srv__SrvAddint_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cv_msg__srv__SrvAddint_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cv_msg__srv__SrvAddint_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
