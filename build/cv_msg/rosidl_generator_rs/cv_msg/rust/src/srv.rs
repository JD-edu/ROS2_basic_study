#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to cv_msg__srv__SrvAddint_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SrvAddint_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SrvAddint_Request {
  type RmwMsg = super::srv::rmw::SrvAddint_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        a: msg.a,
        b: msg.b,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      a: msg.a,
      b: msg.b,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      a: msg.a,
      b: msg.b,
    }
  }
}


// Corresponds to cv_msg__srv__SrvAddint_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SrvAddint_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub sum: i64,

}



impl Default for SrvAddint_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SrvAddint_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SrvAddint_Response {
  type RmwMsg = super::srv::rmw::SrvAddint_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        sum: msg.sum,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      sum: msg.sum,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      sum: msg.sum,
    }
  }
}


// Corresponds to cv_msg__srv__SrvArduino_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SrvArduino_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SrvArduino_Request {
  type RmwMsg = super::srv::rmw::SrvArduino_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        dir: msg.dir,
        speed: msg.speed,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      dir: msg.dir,
      speed: msg.speed,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      dir: msg.dir,
      speed: msg.speed,
    }
  }
}


// Corresponds to cv_msg__srv__SrvArduino_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SrvArduino_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub answer: i64,

}



impl Default for SrvArduino_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SrvArduino_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SrvArduino_Response {
  type RmwMsg = super::srv::rmw::SrvArduino_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        answer: msg.answer,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      answer: msg.answer,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      answer: msg.answer,
    }
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


