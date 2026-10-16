#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvAddint_Request() -> *const std::ffi::c_void;
}

#[link(name = "cv_msg__rosidl_generator_c")]
extern "C" {
    fn cv_msg__srv__SrvAddint_Request__init(msg: *mut SrvAddint_Request) -> bool;
    fn cv_msg__srv__SrvAddint_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SrvAddint_Request>, size: usize) -> bool;
    fn cv_msg__srv__SrvAddint_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SrvAddint_Request>);
    fn cv_msg__srv__SrvAddint_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SrvAddint_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SrvAddint_Request>) -> bool;
}

// Corresponds to cv_msg__srv__SrvAddint_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SrvAddint_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub a: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub b: i64,

}



impl Default for SrvAddint_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cv_msg__srv__SrvAddint_Request__init(&mut msg as *mut _) {
        panic!("Call to cv_msg__srv__SrvAddint_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SrvAddint_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvAddint_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvAddint_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvAddint_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SrvAddint_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SrvAddint_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cv_msg/srv/SrvAddint_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvAddint_Request() }
  }
}


#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvAddint_Response() -> *const std::ffi::c_void;
}

#[link(name = "cv_msg__rosidl_generator_c")]
extern "C" {
    fn cv_msg__srv__SrvAddint_Response__init(msg: *mut SrvAddint_Response) -> bool;
    fn cv_msg__srv__SrvAddint_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SrvAddint_Response>, size: usize) -> bool;
    fn cv_msg__srv__SrvAddint_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SrvAddint_Response>);
    fn cv_msg__srv__SrvAddint_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SrvAddint_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SrvAddint_Response>) -> bool;
}

// Corresponds to cv_msg__srv__SrvAddint_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SrvAddint_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub sum: i64,

}



impl Default for SrvAddint_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cv_msg__srv__SrvAddint_Response__init(&mut msg as *mut _) {
        panic!("Call to cv_msg__srv__SrvAddint_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SrvAddint_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvAddint_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvAddint_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvAddint_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SrvAddint_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SrvAddint_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cv_msg/srv/SrvAddint_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvAddint_Response() }
  }
}


#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvArduino_Request() -> *const std::ffi::c_void;
}

#[link(name = "cv_msg__rosidl_generator_c")]
extern "C" {
    fn cv_msg__srv__SrvArduino_Request__init(msg: *mut SrvArduino_Request) -> bool;
    fn cv_msg__srv__SrvArduino_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SrvArduino_Request>, size: usize) -> bool;
    fn cv_msg__srv__SrvArduino_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SrvArduino_Request>);
    fn cv_msg__srv__SrvArduino_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SrvArduino_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SrvArduino_Request>) -> bool;
}

// Corresponds to cv_msg__srv__SrvArduino_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SrvArduino_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub dir: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: i64,

}



impl Default for SrvArduino_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cv_msg__srv__SrvArduino_Request__init(&mut msg as *mut _) {
        panic!("Call to cv_msg__srv__SrvArduino_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SrvArduino_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvArduino_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvArduino_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvArduino_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SrvArduino_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SrvArduino_Request where Self: Sized {
  const TYPE_NAME: &'static str = "cv_msg/srv/SrvArduino_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvArduino_Request() }
  }
}


#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvArduino_Response() -> *const std::ffi::c_void;
}

#[link(name = "cv_msg__rosidl_generator_c")]
extern "C" {
    fn cv_msg__srv__SrvArduino_Response__init(msg: *mut SrvArduino_Response) -> bool;
    fn cv_msg__srv__SrvArduino_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SrvArduino_Response>, size: usize) -> bool;
    fn cv_msg__srv__SrvArduino_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SrvArduino_Response>);
    fn cv_msg__srv__SrvArduino_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SrvArduino_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SrvArduino_Response>) -> bool;
}

// Corresponds to cv_msg__srv__SrvArduino_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SrvArduino_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub answer: i64,

}



impl Default for SrvArduino_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cv_msg__srv__SrvArduino_Response__init(&mut msg as *mut _) {
        panic!("Call to cv_msg__srv__SrvArduino_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SrvArduino_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvArduino_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvArduino_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__srv__SrvArduino_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SrvArduino_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SrvArduino_Response where Self: Sized {
  const TYPE_NAME: &'static str = "cv_msg/srv/SrvArduino_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cv_msg__srv__SrvArduino_Response() }
  }
}






#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cv_msg__srv__SrvAddint() -> *const std::ffi::c_void;
}

// Corresponds to cv_msg__srv__SrvAddint
#[allow(missing_docs, non_camel_case_types)]
pub struct SrvAddint;

impl rosidl_runtime_rs::Service for SrvAddint {
    type Request = SrvAddint_Request;
    type Response = SrvAddint_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cv_msg__srv__SrvAddint() }
    }
}




#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__cv_msg__srv__SrvArduino() -> *const std::ffi::c_void;
}

// Corresponds to cv_msg__srv__SrvArduino
#[allow(missing_docs, non_camel_case_types)]
pub struct SrvArduino;

impl rosidl_runtime_rs::Service for SrvArduino {
    type Request = SrvArduino_Request;
    type Response = SrvArduino_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__cv_msg__srv__SrvArduino() }
    }
}


