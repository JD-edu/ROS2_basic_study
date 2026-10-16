#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to cv_msg__msg__MsgCenter

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MsgCenter::default())
  }
}

impl rosidl_runtime_rs::Message for MsgCenter {
  type RmwMsg = super::msg::rmw::MsgCenter;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        x: msg.x,
        y: msg.y,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      x: msg.x,
      y: msg.y,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      x: msg.x,
      y: msg.y,
    }
  }
}


