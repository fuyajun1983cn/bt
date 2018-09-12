=================
SDP Code Analysis
=================

Main Data Structure
===================

tSDP_CB
-------

.. code-block:: c++

   /*  The main SDP control block */
     typedef struct {
       tL2CAP_CFG_INFO l2cap_my_cfg; /* My L2CAP config     */
       tCONN_CB ccb[SDP_MAX_CONNECTIONS];
     #if (SDP_SERVER_ENABLED == TRUE)
       tSDP_DB server_db;
     #endif
       tL2CAP_APPL_INFO reg_info;    /* L2CAP Registration info */
       uint16_t max_attr_list_size;  /* Max attribute list size to use   */
       uint16_t max_recs_per_search; /* Max records we want per seaarch  */
       uint8_t trace_level;
     } tSDP_CB;

   refer to  the following two functions for data structure init/deinit.

   .. code-block:: c++

      extern void sdp_init(void);
      extern void sdp_free(void);




tCONN_CB
--------

.. code-block:: c++

   /* Define the SDP Connection Control Block */
     typedef struct {
       uint8_t con_state;
     
       uint8_t con_flags;
     
       RawAddress device_address;
       alarm_t* sdp_conn_timer;
       uint16_t rem_mtu_size;
       uint16_t connection_id;
       uint16_t list_len; /* length of the response in the GKI buffer */
       uint16_t bl_update_len; /* length of the attributes to be updated fromfinal sdp response len */
       uint8_t* rsp_list; /* pointer to GKI buffer holding response */
     
       tSDP_DISCOVERY_DB* p_db; /* Database to save info into   */
       tSDP_DISC_CMPL_CB* p_cb; /* Callback for discovery done  */
       tSDP_DISC_CMPL_CB2*
           p_cb2; /* Callback for discovery done piggy back with the user data */
       void* user_data; /* piggy back user data */
       uint32_t
           handles[SDP_MAX_DISC_SERVER_RECS]; /* Discovered server record handles */
       uint16_t num_handles;                  /* Number of server handles     */
       uint16_t cur_handle;                   /* Current handle being processed */
       uint16_t transaction_id;
       uint16_t disconnect_reason; /* Disconnect reason            */
     #if (SDP_BROWSE_PLUS == TRUE)
       uint16_t cur_uuid_idx;
     #endif
     
       uint8_t disc_state;
       uint8_t is_attr_search;
     
     #if (SDP_SERVER_ENABLED == TRUE)
       uint16_t cont_offset;     /* Continuation state data in the server response */
       tSDP_CONT_INFO cont_info; /* structure to hold continuation information for
                                    the server response */
     #endif                      /* SDP_SERVER_ENABLED == TRUE */
     
     } tCONN_CB;
     
     /*  The main SDP control block */
     typedef struct {
       tL2CAP_CFG_INFO l2cap_my_cfg; /* My L2CAP config     */
       tCONN_CB ccb[SDP_MAX_CONNECTIONS];
     #if (SDP_SERVER_ENABLED == TRUE)
       tSDP_DB server_db;
     #endif
       tL2CAP_APPL_INFO reg_info;    /* L2CAP Registration info */
       uint16_t max_attr_list_size;  /* Max attribute list size to use   */
       uint16_t max_recs_per_search; /* Max records we want per seaarch  */
       uint8_t trace_level;
     } tSDP_CB;


- ``con_state``

  SDP connection  state.

  .. code-block:: c++

     #define SDP_STATE_IDLE 0
     #define SDP_STATE_CONN_SETUP 1
     #define SDP_STATE_CFG_SETUP 2
     #define SDP_STATE_CONNECTED 3
     #define SDP_STATE_CONN_PEND 4

- ``con_flags``

  .. code-block:: c++

     #define SDP_FLAGS_IS_ORIG 0x01
     #define SDP_FLAGS_HIS_CFG_DONE 0x02
     #define SDP_FLAGS_MY_CFG_DONE 0x04

- ``sdp_conn_timer``

  inactivity timer.

- ``connection_id``

  L2CAP CID.

- ``p_db``

  database to save information.  

  .. code-block:: c++

     typedef struct {
       uint32_t mem_size;          /* Memory size of the DB        */
       uint32_t mem_free;          /* Memory still available       */
       tSDP_DISC_REC* p_first_rec; /* Addr of first record in DB   */
       uint16_t num_uuid_filters;  /* Number of UUIds to filter    */
       tSDP_UUID uuid_filters[SDP_MAX_UUID_FILTERS]; /* UUIDs to filter      */
       uint16_t num_attr_filters; /* Number of attribute filters  */
       uint16_t attr_filters[SDP_MAX_ATTR_FILTERS]; /* Attributes to filter */
       uint8_t* p_free_mem; /* Pointer to free memory       */
     #if (SDP_RAW_DATA_INCLUDED == TRUE)
       uint8_t*
           raw_data; /* Received record from server. allocated/released by client  */
       uint32_t raw_size; /* size of raw_data */
       uint32_t raw_used; /* length of raw_data used */
     #endif
     } tSDP_DISCOVERY_DB;


