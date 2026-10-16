#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "cv_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cv_msg__msg__MsgCenter() -> *const std::ffi::c_void;
}

#[link(name = "cv_msg__rosidl_generator_c")]
extern "C" {
    fn cv_msg__msg__MsgCenter__init(msg: *mut MsgCenter) -> bool;
    fn cv_msg__msg__MsgCenter__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MsgCenter>, size: usize) -> bool;
    fn cv_msg__msg__MsgCenter__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MsgCenter>);
    fn cv_msg__msg__MsgCenter__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MsgCenter>, out_seq: *mut rosidl_runtime_rs::Sequence<MsgCenter>) -> bool;
}

// Corresponds to cv_msg__msg__MsgCenter
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MsgCenter {

    // This member is not documented.
    #[allow(missing_docs)]
    pub x: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: i64,

}



impl Default for MsgCenter {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cv_msg__msg__MsgCenter__init(&mut msg as *mut _) {
        panic!("Call to cv_msg__msg__MsgCenter__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MsgCenter {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__msg__MsgCenter__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__msg__MsgCenter__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cv_msg__msg__MsgCenter__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MsgCenter {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MsgCenter where Self: Sized {
  const TYPE_NAME: &'static str = "cv_msg/msg/MsgCenter";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cv_msg__msg__MsgCenter() }
  }
}


