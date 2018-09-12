

/******************************************************************************
 *
 *  this file contains the functions relating to link management. A "link"
 *  is a connection between this device and another device. Only ACL links
 *  are managed.
 *
 ******************************************************************************/


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

/*
 * Timeout values (in milliseconds).
 */
#define L2CAP_LINK_ROLE_SWITCH_TIMEOUT_MS (10 * 1000)  /* 10 seconds */
#define L2CAP_LINK_CONNECT_TIMEOUT_MS (20 * 1000)      /* 20 seconds */
#define L2CAP_LINK_CONNECT_EXT_TIMEOUT_MS (120 * 1000) /* 120 seconds */
#define L2CAP_ECHO_RSP_TIMEOUT_MS (30 * 1000)          /* 30 seconds */
#define L2CAP_LINK_FLOW_CONTROL_TIMEOUT_MS (2 * 1000)  /* 2 seconds */
#define L2CAP_LINK_DISCONNECT_TIMEOUT_MS (30 * 1000)   /* 30 seconds */



l2c_link_hci_conn_req 
    -> LST_DISCONNECTING
		-> l2c_link_hci_conn_comp
		   -> LST_CONNECTED
		      -> L2CEVT_LP_CONNECT_CFM //update the status to higher layer.


l2c_link_sec_comp
	-> l2c_link_sec_comp2
		-> L2CEVT_SEC_COMP/L2CEVT_SEC_COMP_NEG //update the status to higher layer.
		

l2c_link_hci_disc_comp
	-> LST_DISCONNECTING

l2c_link_hci_qos_violation
    -> L2CEVT_LP_QOS_VIOLATION_IND //update the status to l2cap
	

l2c_link_timeout
	-> L2CEVT_LP_DISCONNECT_IND




