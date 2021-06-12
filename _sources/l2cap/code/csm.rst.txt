=====================
Channel State Machine
=====================

Channel State
=============

The following enum defines the possible states of a l2cap channel.

.. code-block:: c++

   typedef struct t_l2c_ccb {
     ...
     tL2C_CHNL_STATE chnl_state; /* Channel state */
     ...
   };

   typedef enum {
    CST_CLOSED,                  /* Channel is in closed state */
    CST_ORIG_W4_SEC_COMP,        /* Originator waits security clearence */
    CST_TERM_W4_SEC_COMP,        /* Acceptor waits security clearence */
    CST_W4_L2CAP_CONNECT_RSP,    /* Waiting for peer conenct response */
    CST_W4_L2CA_CONNECT_RSP,     /* Waiting for upper layer connect rsp */
    CST_CONFIG,                  /* Negotiating configuration */
    CST_OPEN,                    /* Data transfer state */
    CST_W4_L2CAP_DISCONNECT_RSP, /* Waiting for peer disconnect rsp */
    CST_W4_L2CA_DISCONNECT_RSP   /* Waiting for upper layer disc rsp */
  } tL2C_CHNL_STATE;


when allocate a new Channel Control Block, the state will be set to `CST_CLOSED`.

  

Channel Timers
==============

there is a timer defined for the state change on a channel.

.. code-block:: c++

   typedef struct t_l2c_ccb {
     ...
     alarm_t* l2c_ccb_timer; /* CCB Timer Entry */
     ...
   };


channel related timeout values are defined as follows:

.. code-block:: c++

   #define L2CAP_CHNL_CONNECT_TIMEOUT_MS (20 * 1000)      /* 20 seconds */
   #define L2CAP_CHNL_CONNECT_EXT_TIMEOUT_MS (120 * 1000) /* 120 seconds */
   #define L2CAP_CHNL_CFG_TIMEOUT_MS (30 * 1000)          /* 30 seconds */
   #define L2CAP_CHNL_DISCONNECT_TIMEOUT_MS (10 * 1000)   /* 10 seconds */
   #define L2CAP_DELAY_CHECK_SM4_TIMEOUT_MS (2 * 1000)    /* 2 seconds */


the timer will be allocated during allocate a new channel control block:

.. code-block:: c++

   alarm_free(p_ccb->l2c_ccb_timer);
   p_ccb->l2c_ccb_timer = alarm_new("l2c.l2c_ccb_timer");

   
Channel Statemachine handler
============================

.. image:: ./images/2018082301.png


L2cap Link Statemachine
=======================

possible link state:

.. code-block:: c++

   /* Define the possible L2CAP link states
   */
   typedef enum {
     LST_DISCONNECTED,
     LST_CONNECT_HOLDING,
     LST_CONNECTING_WAIT_SWITCH,
     LST_CONNECTING,
     LST_CONNECTED,
     LST_DISCONNECTING
   } tL2C_LINK_STATE;


timeout value:

.. code-block:: c++

   /*
    * Timeout values (in milliseconds).
    */
   #define L2CAP_LINK_ROLE_SWITCH_TIMEOUT_MS (10 * 1000)  /* 10 seconds */
   #define L2CAP_LINK_CONNECT_TIMEOUT_MS (20 * 1000)      /* 20 seconds */
   #define L2CAP_LINK_CONNECT_EXT_TIMEOUT_MS (120 * 1000) /* 120 seconds */
   #define L2CAP_ECHO_RSP_TIMEOUT_MS (30 * 1000)          /* 30 seconds */
   #define L2CAP_LINK_FLOW_CONTROL_TIMEOUT_MS (2 * 1000)  /* 2 seconds */
   #define L2CAP_LINK_DISCONNECT_TIMEOUT_MS (30 * 1000)   /* 30 seconds */                

   
l2cap link will report l2cap events to the l2cap statemachine. 
