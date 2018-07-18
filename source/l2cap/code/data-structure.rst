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


- ``l2cap_trace_level``

  log debug level.  use `L2CA_SetTraceLevel` to set it's value,
  in `l2c_init1`, the default value is set as follows:

  .. code-block:: c++

     #if defined(L2CAP_INITIAL_TRACE_LEVEL)
       l2cb.l2cap_trace_level = L2CAP_INITIAL_TRACE_LEVEL;
     #else
       l2cb.l2cap_trace_level = BT_TRACE_LEVEL_NONE; /* No traces */
     #endif

- ``controller_xmit_window``

  Total ACL window for all links. it's the controller buffer size(window).
  if its value is zero, it means the controller window is full, then host can't send packest to the controller.

  it's value mean that how many packets doest the host can transmit to the controller.

  this value is initialized when receiving "Controller Buffer Size" event.

  .. code-block:: c++

     /*******************************************************************************
      *
      * Function         l2c_link_processs_num_bufs
      *
      * Description      This function is called when a "controller buffer size"
      *                  event is first received from the controller. It updates
      *                  the L2CAP values.
      *
      * Returns          void
      *
      ******************************************************************************/
      void l2c_link_processs_num_bufs(uint16_t num_lm_acl_bufs) {
        l2cb.num_lm_acl_bufs = l2cb.controller_xmit_window = num_lm_acl_bufs;
      }

  this value is updated when receiving **Number of Completed Packets Event**.

  .. code-block:: c++

     void l2c_link_process_num_completed_pkts(uint8_t* p) {
       ...
       l2cb.controller_xmit_window += num_sent;
       ...
     }

- ``round_robin_quota``
- ``round_robin_unacked``
- ``check_round_robin``

  ``round_robin_quota`` is total usable controller buffer when each low priority link cannot have at least one buffer.

  ``round_robin_uacked`` is the total packets sent  out but  not acked by controller, this  value will  be updated in ``l2c_link_process_num_completed_pkts``.

  ``check_round_robin`` is set true when we were doing round-robin for low priority links.

- ``is_cong_cback_context``

  control if we can sent the packets to the controller now.

- ``lcb_pool``

  Link Control Block pool, we can always iterate all the existing link through the following code snippets:

  .. code-block:: c++

    p_lcb = &l2cb.lcb_pool[0];
    for (ii = 0; ii < MAX_L2CAP_LINKS; ii++, p_lcb++) {
      if (p_lcb->in_use) {
         ...
      }
      ...
    }

- ``ccb_pool``

  Channel Control Block pool. this  array will hold all the channel control blocks. the maxize is 20.

  .. code-block:: c++

       /* Put all the channel control blocks on the free queue */
        for (xx = 0; xx < MAX_L2CAP_CHANNELS - 1; xx++) {
          l2cb.ccb_pool[xx].p_next_ccb = &l2cb.ccb_pool[xx + 1];
        }
     
- ``rcb_pool``

  Registration info pool. when an ``L2CA_Register`` called, it will allocate one element for it.
  this arrays hold an element for every PSM currently registered to the L2CAP layer.

  The maximum number of simultaneous applications(ER/EDR) that can register with L2CAP is MAX_L2CAP_CLIENTS(19)

- ``p_free_ccb_first``
- ``p_free_ccb_last``

  this is the shortcut to find a free CCB,  it also maintain the list of free CCB.

  see ``l2cu_allocate_ccb`` and ``l2cu_release_ccb``.

  at ``l2c_init()``, it's initialized as follows:

  .. code-block:: c++

       l2cb.p_free_ccb_first = &l2cb.ccb_pool[0];
       l2cb.p_free_ccb_last = &l2cb.ccb_pool[MAX_L2CAP_CHANNELS - 1];
  
- ``desire_role``

  desire to be master/slave when accepting a connection. generally, the device who initialize a connection will be the master.

- ``disallow_switch``

  default to set to ``false``. wether to allow switch at create conn.

- ``num_lm_acl_bufs``

  the number of the ACL buffers on controller. ``controller_xmit_window`` should never exceed this value. 
  
- ``idle_timeout``

  The number of seconds of link inactivity before a link is disconnected.initilized during ``l2c_init()``, the default value is 4s. 

  use ``L2CA_SetIdleTimeout()`` to change the default value.

- ``rcv_pending_q``
- ``receive_hold_timer``

  ``rcv_pending_q`` is a queue for holding any L2CAP packets that arrived before the HCI Complete Event arrived.

  ``receive_holder_timer`` is a timer for processing the packets in the above queue.

  both vars are initialzed during ``l2c_init()``. 

- ``p_cur_hcit_lcb``

  Current HCI Transport buffer.

- ``num_links_active``

  Number of links active. updated when ``l2cu_allocate_lcb`` and ``l2cu_release_lcb``.

- ``non_flushable_pbf``
- ``is_flush_active``

  these two vars are related to l2cap flush setting.

- ``fixed_reg``

  Reg info for fixed channels

  using ``L2CA_RegisterFixedChannel`` and ``L2CA_RemoveFixedChnl`` to add and remove fixed channel registration.

- ``num_ble_links_active``

  Number of LE links active. updated when ``l2cu_allocate_lcb`` and ``l2cu_release_lcb``.

- ``is_ble_connecting``
- ``ble_connecting_bda``

  state for ble connection progress and the remote device address we're going to connect.

  refer to ``l2cble_init_direct_conn``

- ``controller_le_xmit_window``

  tramsmit window for LE links.

  LE Fixed Channel Mask which shows what fixed channels support by the DUT.

  during ``l2c_init``, we have the following settings:

  .. code-block:: c++

     l2cb.l2c_ble_fixed_chnls_mask = L2CAP_FIXED_CHNL_ATT_BIT |
                  L2CAP_FIXED_CHNL_BLE_SIG_BIT |
                  L2CAP_FIXED_CHNL_SMP_BIT;

- ``num_lm_ble_bufs``

  ACL buffers on controller for LE device.

- ``ble_round_robin_quota``
- ``ble_round_robin_unacked``
- ``ble_check_round_robin``

  vars for ajusting ble link quota.

- ``ble_rcb_pool``

  Registration info pool for connected ble application, The maximum number of simultaneous applications that can register with LE L2CAP
  is **BLE_MAX_L2CAP_CLIENTS(15)**.

- ``p_echo_data_cb``

  pointer to the callback for echo request.
  
  Hihger layer application can send echo request to the peer device with specific data,
  this callback will be called when peer send echo response to the DUT. 

- ``high_pri_min_xmit_quota``

  if Number of ACL buffers to use high priority channel is configurable, this value can be adjusted dynmamically,
  its initial value is **L2CAP_HIGH_PRI_MIN_XMIT_QUOTA(5)**. 


tL2C_LCB
========

.. code-block:: c++

      /* Define a link control block. There is one link control block between
       * this device and any other device (i.e. BD ADDR).
      */
      typedef struct t_l2c_linkcb {
        bool in_use; /* true when in use, false when not */
        tL2C_LINK_STATE link_state;
      
        alarm_t* l2c_lcb_timer; /* Timer entry for timeout evt */
        uint16_t handle;        /* The handle used with LM */
      
        tL2C_CCB_Q ccb_queue; /* Queue of CCBs on this LCB */
      
        tL2C_CCB* p_pending_ccb;  /* ccb of waiting channel during link disconnect */
        alarm_t* info_resp_timer; /* Timer entry for info resp timeout evt */
        RawAddress remote_bd_addr; /* The BD address of the remote */
      
        uint8_t link_role; /* Master or slave */
        uint8_t id;
        uint8_t cur_echo_id;              /* Current id value for echo request */
        tL2CA_ECHO_RSP_CB* p_echo_rsp_cb; /* Echo response callback */
        uint16_t idle_timeout;            /* Idle timeout */
        bool is_bonding;                  /* True - link active only for bonding */
      
        uint16_t link_flush_tout; /* Flush timeout used */
      
        uint16_t link_xmit_quota; /* Num outstanding pkts allowed */
        uint16_t sent_not_acked;  /* Num packets sent but not acked */
      
        bool partial_segment_being_sent; /* Set true when a partial segment */
                                         /* is being sent. */
        bool w4_info_rsp;                /* true when info request is active */
        uint8_t info_rx_bits;            /* set 1 if received info type */
        uint32_t peer_ext_fea;           /* Peer's extended features mask */
        list_t* link_xmit_data_q;        /* Link transmit data buffer queue */
      
        uint8_t peer_chnl_mask[L2CAP_FIXED_CHNL_ARRAY_SIZE];
      #if (L2CAP_UCD_INCLUDED == TRUE)
        uint16_t ucd_mtu; /* peer MTU on UCD */
        fixed_queue_t*
            ucd_out_sec_pending_q; /* Security pending outgoing UCD packet */
        fixed_queue_t*
            ucd_in_sec_pending_q; /* Security pending incoming UCD packet */
      #endif
      
        BT_HDR* p_hcit_rcv_acl;   /* Current HCIT ACL buf being rcvd */
        uint16_t idle_timeout_sv; /* Save current Idle timeout */
        uint8_t acl_priority;     /* L2C_PRIORITY_NORMAL or L2C_PRIORITY_HIGH */
        tL2CA_NOCP_CB* p_nocp_cb; /* Num Cmpl pkts callback */
      
      #if (L2CAP_NUM_FIXED_CHNLS > 0)
        tL2C_CCB* p_fixed_ccbs[L2CAP_NUM_FIXED_CHNLS];
        uint16_t disc_reason;
      #endif
      
        tBT_TRANSPORT transport;
        uint8_t initiating_phys;  // LE PHY used for connection initiation
        tBLE_ADDR_TYPE ble_addr_type;
        uint16_t tx_data_len; /* tx data length used in data length extension */
        fixed_queue_t* le_sec_pending_q; /* LE coc channels waiting for security check
                                            completion */
        uint8_t sec_act;
      #define L2C_BLE_CONN_UPDATE_DISABLE \
        0x1                              /* disable update connection parameters */
      #define L2C_BLE_NEW_CONN_PARAM 0x2 /* new connection parameter to be set */
      #define L2C_BLE_UPDATE_PENDING                  \
        0x4 /* waiting for connection update finished \
               */
      #define L2C_BLE_NOT_DEFAULT_PARAM \
        0x8 /* not using default connection parameters */
        uint8_t conn_update_mask;
      
        uint16_t min_interval; /* parameters as requested by peripheral */
        uint16_t max_interval;
        uint16_t latency;
        uint16_t timeout;
      
      #if (L2CAP_ROUND_ROBIN_CHANNEL_SERVICE == TRUE)
        /* each priority group is limited burst transmission */
        /* round robin service for the same priority channels */
        tL2C_RR_SERV rr_serv[L2CAP_NUM_CHNL_PRIORITY];
        uint8_t rr_pri; /* current serving priority group */
      #endif
      
      } tL2C_LCB;


- ``in_use``
- ``link_state``

  the max number of the link is **MAX_L2CAP_LINKS(7)**, for every link, there is an array element(**lcb_pool**) for it.
  if it's allocated, *in_use* will be set to true.

  the *link_state* can be the one of the following:

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

- ``l2c_lcb_timer``

  Timer entry for timeout evt for a link.

- ``handle``

   used with LM. handle identify a l2cap link between local DUT with the remote device. handle value(0xedc) is specific for SoC debug loggin.

   handle value is returned from controller.  when the HCI Connection Complete event is received from the controller,
   it will return the handle value to the upper layer and save it to this var. 
   

- ``ccb_queue``

  Queue of CCBs on this LCB. often use the following code snippets to iterate CCB on it:

  .. code-block:: c++

                  for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; p_ccb = p_ccb->p_next_ccb) {
                     ...
                  }

- ``p_pending_ccb``

  ccb of waiting channel during link disconnect. after disconnection complete, we can restart the channel for CCB.

- ``info_resp_timer``

  Timer entry for info resp timeout evt.

- ``remote_bd_addr``

  The BD address of the remote in this link. 

- ``link_role``

  the DUT's role in this link.  Master or Slave.

- ``id``

  this is the identifier value for every l2cap request/response on signaling channel between local DUT and remote device.

  this value should be the same for each request and response pair. this value should not be 0.

- ``cur_echo_id``

  Current id value for echo request.

- ``p_echo_rsp_cb``

  Echo response callback.

- ``idle_timeout``

  timeout value for Idle timeout.

- ``idle_timeout``

  use this ``L2CA_SetIdleTimeout`` to update this value.

- ``is_bonding``

  when this value is true, it means this link is only active for bonding.

- ``link_flush_tout``

  Flush timeout used. use ``L2CA_SetFlushTimeout`` to update it.

- ``link_xmit_quota``
- ``sent_not_acked``

  Num outstanding pkts allowed  and Num packets sent but not acked.

- ``partial_segment_being_sent``

  Set true when a partial segment is being sent. 

- ``w4_info_rsp``

  true when info request is active.

- ``info_rx_bits``

  set to 1 for received info type. 
  
- ``peer_ext_fea``

  hold peer's extended feature mask. 

  .. image:: ./images/2018071501.png

- ``peer_chnl_mask``

  peer supported fixed channel type.

- ``ucd_mtu``
- ``ucd_out_sec_pending_q``
- ``ucd_in_sec_pending_q``

  Security pending outgoing/incoming UCD(Unicast Connectionless Data) packet. 

- ``p_hcit_rcv_acl``

  Current HCIT ACL buf being rcvd.

- ``idle_timeout_sv``

  Save current Idle timeout.

- ``acl_priority``

  **L2C_PRIORITY_NORMAL** or **L2C_PRIORITY_HIGH**.

- ``p_nocp_cb``

  callback for Number of Completed Packets.

  use *L2CA_RegForNoCPEvt* to register the callback.

- ``p_fixed_ccbs``
- ``disc_reason``

  the number of the fixed channels is **L2CAP_NUM_FIXED_CHNLS(32)**.

- ``transport``

  transport type: LE or ED/EDR.

- ``initiating_phys``

  LE PHY used for connection initiation.

- ``ble_addr_type``

  .. image:: ./images/2018071502.png

- ``tx_data_len``

  tx data length used in data length extension.

- ``le_sec_pending_q``

  Queue for LE CoC(Connection Oriented Channel) channels waiting for security check completion.

  refer to https://blog.csdn.net/Wendell_Gong/article/details/54956499.


