==========================
L2CAP Main Data Structures
==========================

L2CAP Main Data Structure
=========================

.. image:: ./images/2018070601.png

tL2C_CB
=======

.. code-block:: c++

   /* Define the L2CAP control structure
   */
   typedef struct {
     uint8_t l2cap_trace_level;
     uint16_t controller_xmit_window; /* Total ACL window for all links */
   
     uint16_t round_robin_quota;   /* Round-robin link quota */
     uint16_t round_robin_unacked; /* Round-robin unacked */
     bool check_round_robin;       /* Do a round robin check */
   
     bool is_cong_cback_context;
   
     tL2C_LCB lcb_pool[MAX_L2CAP_LINKS];    /* Link Control Block pool */
     tL2C_CCB ccb_pool[MAX_L2CAP_CHANNELS]; /* Channel Control Block pool */
     tL2C_RCB rcb_pool[MAX_L2CAP_CLIENTS];  /* Registration info pool */
   
     tL2C_CCB* p_free_ccb_first; /* Pointer to first free CCB */
     tL2C_CCB* p_free_ccb_last;  /* Pointer to last  free CCB */
   
     uint8_t
         desire_role; /* desire to be master/slave when accepting a connection */
     bool disallow_switch;     /* false, to allow switch at create conn */
     uint16_t num_lm_acl_bufs; /* # of ACL buffers on controller */
     uint16_t idle_timeout;    /* Idle timeout */
   
     list_t* rcv_pending_q;       /* Recv pending queue */
     alarm_t* receive_hold_timer; /* Timer entry for rcv hold */
   
     tL2C_LCB* p_cur_hcit_lcb;  /* Current HCI Transport buffer */
     uint16_t num_links_active; /* Number of links active */
   
   #if (L2CAP_NON_FLUSHABLE_PB_INCLUDED == TRUE)
     uint16_t non_flushable_pbf; /* L2CAP_PKT_START_NON_FLUSHABLE if controller
                                    supports */
     /* Otherwise, L2CAP_PKT_START */
     bool is_flush_active; /* true if an HCI_Enhanced_Flush has been sent */
   #endif
   
   #if (L2CAP_CONFORMANCE_TESTING == TRUE)
     uint32_t test_info_resp; /* Conformance testing needs a dynamic response */
   #endif
   
   #if (L2CAP_NUM_FIXED_CHNLS > 0)
     tL2CAP_FIXED_CHNL_REG
         fixed_reg[L2CAP_NUM_FIXED_CHNLS]; /* Reg info for fixed channels */
   #endif
   
     uint16_t num_ble_links_active; /* Number of LE links active */
     bool is_ble_connecting;
     RawAddress ble_connecting_bda;
     uint16_t controller_le_xmit_window; /* Total ACL window for all links */
     tL2C_BLE_FIXED_CHNLS_MASK l2c_ble_fixed_chnls_mask;  // LE fixed channels mask
     uint16_t num_lm_ble_bufs;         /* # of ACL buffers on controller */
     uint16_t ble_round_robin_quota;   /* Round-robin link quota */
     uint16_t ble_round_robin_unacked; /* Round-robin unacked */
     bool ble_check_round_robin;       /* Do a round robin check */
     tL2C_RCB ble_rcb_pool[BLE_MAX_L2CAP_CLIENTS]; /* Registration info pool */
   
     tL2CA_ECHO_DATA_CB* p_echo_data_cb; /* Echo data callback */
   
   #if (L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE == TRUE)
     uint16_t high_pri_min_xmit_quota; /* Minimum number of ACL credit for high
                                          priority link */
   #endif /* (L2CAP_HIGH_PRI_CHAN_QUOTA_IS_CONFIGURABLE == TRUE) */
   
     uint16_t dyn_psm;
   } tL2C_CB;


- l2cap_trace_level

  log debug level.  use `L2CA_SetTraceLevel` to set it's value,
  in `l2c_init1`, the default value is set as follows:

  .. code-block:: c++

     #if defined(L2CAP_INITIAL_TRACE_LEVEL)
       l2cb.l2cap_trace_level = L2CAP_INITIAL_TRACE_LEVEL;
     #else
       l2cb.l2cap_trace_level = BT_TRACE_LEVEL_NONE; /* No traces */
     #endif
