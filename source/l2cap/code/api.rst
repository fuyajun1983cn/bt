=============================
 L2CAP API for Higher Layers
=============================

.. function:: uint16_t L2CA_Register(uint16_t psm, tL2CAP_APPL_INFO* p_cb_info)

   Other layers call this function to register for L2CAP services

   :param psm: uint16_t
   :param p_cb_info: tL2CAP_APPL_INFO
   :rtype: PSM to use or zero if error.

.. function:: void L2CA_Deregister(uint16_t psm)

   Other layers call this function to de-register for L2CAP services

   :param psm: uint16_t
   :rtype: return nothing.

.. function:: uint16_t L2CA_AllocatePSM(void)

   Other layers call this function to find an unused PSM for L2CAP services

   :rtype: PSM to use.

.. function:: uint16_t L2CA_ConnectReq(uint16_t psm, const RawAddress& p_bd_addr)

   Higher layers call this function to create an L2CAP connection.

   :param psm: uint16_t
   :param p_bd_addr: RawAddress
   :rtype: the CID of the connection, or 0 if it failed to start

.. function:: uint16_t L2CA_ErtmConnectReq(uint16_t psm, const RawAddress& p_bd_addr, tL2CAP_ERTM_INFO* p_ertm_info)

   Higher layers call this function to create an L2CAP connection.

   :param psm: uint16_t
   :param p_bd_addr: RawAddress
   :rtype: the CID of the connection, or 0 if it failed to start

.. function:: uint16_t L2CA_RegisterLECoc(uint16_t psm, tL2CAP_APPL_INFO* p_cb_info)

   Other layers call this function to register for L2CAP Connection Oriented Channel.

   :param psm: uint16_t
   :param p_cb_info: tL2CAP_APPL_INFO
   :rtype: PSM to use or zero if error.

.. function:: void L2CA_DeregisterLECoc(uint16_t psm)

   Other layers call this function to de-register for L2CAP Connection Oriented Channel.

   :param psm: uint16_t
   :rtype: void.

.. function:: uint16_t L2CA_ConnectLECocReq(uint16_t psm, const RawAddress& p_bd_addr, tL2CAP_LE_CFG_INFO* p_cfg)

    Higher layers call this function to create an L2CAP connection.

   :param psm: uint16_t
   :param p_bd_addr: RawAddress
   :param p_cfg: tL2CAP_LE_CFG_INFO
   :rtype: the CID of the connection, or 0 if it failed to start

.. function:: bool L2CA_ConnectLECocRsp(const RawAddress& p_bd_addr, uint8_t id, uint16_t lcid, uint16_t result, uint16_t status, tL2CAP_LE_CFG_INFO* p_cfg)

   Higher layers call this function to accept an incoming L2CAP COC connection, for which they had gotten an connect indication callback.

   :param p_bd_addr: RawAddress
   :param id: uint8_t, transaction id
   :param lcid: uint16_t, local CID
   :param result: uint16_t, l2cap connection result code
   :param status: uint16_t, L2CAP status
   :param p_cfg: tL2CAP_LE_CFG_INFO, config for ble connection oriented channel
   :rtype: bool, true for success, false for failure

.. function:: bool L2CA_GetPeerLECocConfig(uint16_t lcid, tL2CAP_LE_CFG_INFO* peer_cfg)

   Get a peers configuration for LE Connection Oriented Channel

   :param lcid: uint16_t, local CID
   :param peer_cfg: Pointers to peers configuration storage area.
   :rtype: true if peer is connected.

.. function:: bool L2CA_SetConnectionCallbacks(uint16_t local_cid, const tL2CAP_APPL_INFO* callbacks)

   set the callback functions for an upper layer on top of l2cap.

   :param local_cid: uint16_t, local CID
   :param callbacks: tL2CAP_APPL_INFO
   :rtype: bool

.. function:: bool L2CA_ConnectRsp(const RawAddress& p_bd_addr, uint8_t id, uint16_t lcid, uint16_t result, uint16_t status)

   Higher layers call this function to accept an incoming L2CAP connection, for which they had gotten an connect indication callback.

   :param p_bd_addr: RawAddress
   :param id: uint8_t, transaction ID.
   :param lcid: uint16_t, local CID.
   :param result: uint16_t, l2cap connection result code.
   :param status: uint16_t, l2cap connection status.
   :rtype: bool, true for success, false for failure.

.. function:: bool L2CA_ErtmConnectRsp(const RawAddress& p_bd_addr, uint8_t id, uint16_t lcid, uint16_t result, uint16_t status, tL2CAP_ERTM_INFO* p_ertm_info)

   Higher layers call this function to accept an incoming L2CAP connection, for which they had gotten an connect indication callback.

   :param p_ertm_info: tL2CAP_ERTM_INFO, information about ERTM mode.
   :rtype: true for success, false for failure. 

.. function:: bool L2CA_ConfigReq(uint16_t cid, tL2CAP_CFG_INFO* p_cfg)

   Higher layers call this function to send configuration.

   .. note::
      The FCR options of p_cfg are not used.

   :param cid: local CID.
   :param p_cfg: local configuration parameters.
   :rtype: true if configuration sent, else false

.. function:: bool L2CA_ConfigRsp(uint16_t cid, tL2CAP_CFG_INFO* p_cfg)

   Higher layers call this function to send a configuration response.

   :param cid: local CID.
   :param p_cfg: local configuration parameters.
   :rtype: true if configuration response sent, else false.

.. function:: bool L2CA_DisconnectReq(uint16_t cid)

   Higher layers call this function to disconnect a channel.

   :param cid: local CID
   :rtype: true if disconnect sent, else false.

.. function:: bool L2CA_DisconnectRsp(uint16_t cid)

   Higher layers call this function to acknowledge the disconnection of a channel.

   :param cid: local CID.
   :rtype: void.

.. function:: bool L2CA_Ping(const RawAddress& p_bd_addr, tL2CA_ECHO_RSP_CB* p_callback)

   Higher layers call this function to send an echo request.

   :param p_bd_addr: RawAddress
   :param p_callback: tL2CA_ECHO_RSP_CB
   :rtype: true if echo request sent, else false.

.. function:: bool L2CA_Echo(const RawAddress& p_bd_addr, BT_HDR* p_data, tL2CA_ECHO_DATA_CB* p_callback)

   Higher layers call this function to send an echo request with application-specific data.

   :param p_bd_addr: RawAddress
   :param p_data: BT_HDR
   :param p_callback: tL2CA_ECHO_DATA_CB
   :rtype: true if echo request sent, else false.

.. function:: bool L2CA_GetIdentifiers(uint16_t lcid, uint16_t* rcid, uint16_t* handle)

   get connection handle for a l2cap link.

   :param lcid: local CID.
   :param rcid: remote CID.
   :param handle: l2cap link handle.
   :rtype: bool.

.. function:: bool L2CA_SetIdleTimeout(uint16_t cid, uint16_t timeout, bool is_global)

   Higher layers call this function to set the idle timeout for a connection, or for all future connections.

   .. note::

      This timeout takes effect after at least 1 channel has been
      established and removed. L2CAP maintains its own timer from
      when a connection is established till the first channel is set up.

   :param cid: local CID.
   :param timeout: l2cap link idle timeout, in seconds.
   :param is_global: bool, true for all l2cap links.
   :rtype: bool.

.. function:: bool L2CA_SetIdleTimeoutByBdAddr(const RawAddress& bd_addr, uint16_t timeout, tBT_TRANSPORT transport)

   Higher layers call this function to set the idle timeout for a connection.

   .. note::

      This timeout applies to all logical channels active on the ACL link.

   :param bd_addr: RawAddress.
   :param timeout: uint16_t.
   :param transport: tBT_TRANSPORT.
   :rtype: bool.

.. function:: uint8_t L2CA_SetDesireRole(uint8_t new_role)

   This function sets the desire role for L2CAP.

   .. note::

      If the new role is L2CAP_ROLE_ALLOW_SWITCH, allow switch on
      HciCreateConnection.
      If the new role is L2CAP_ROLE_DISALLOW_SWITCH, do not allow
      switch on HciCreateConnection.

      If the new role is a valid role (HCI_ROLE_MASTER or
      HCI_ROLE_SLAVE), the desire role is set to the new value.
      Otherwise, it is not changed.

   :param new_role: uint8_t
   :rtype: uint8_t, the new (current) role.

.. function:: bool L2CA_SetAclPriority(const RawAddress& bd_addr, uint8_t priority)

   Sets the transmission priority for a channel.
   (For initial implementation only two values are valid. `L2CAP_PRIORITY_NORMAL` and `L2CAP_PRIORITY_HIGH`).

   :param bd_addr: RawAddress
   :param priority: uint8_t
   :rtype: bool.

.. function:: bool L2CA_SetTxPriority(uint16_t cid, tL2CAP_CHNL_PRIORITY priority)

   Sets the transmission priority for a channel.

   :param cid: local CID.
   :param priority: tL2CAP_CHNL_PRIORITY.
   :rtype: true if a valid channel, else false.

.. function:: bool L2CA_SetFlushTimeout(const RawAddress& bd_addr, uint16_t flush_tout)

   This function set the automatic flush time out in Baseband for ACL-U packets.

   .. note::

      This flush timeout applies to all logical channels active on the ACL link.

   :param bd_addr: the remote BD address of ACL link. If it is BT_DB_ANY then the flush time out will be applied to all ACL links.
   :param flush_tout: flush time out in ms. 
   :rtype: true if command succeeded, false if failed.

.. function:: bool L2CA_GetPeerFeatures(const RawAddress& bd_addr, uint32_t* p_ext_feat, uint8_t* p_chnl_mask)

   Get a peers features and fixed channel map

   :param bd_addr: BD address of the peer.
   :param p_ext_feat: Pointers to features.
   :param p_chnl_mask: Pointers to channel mask storage area.
   :rtype: true if peer is connected.

.. function:: bool L2CA_RegisterFixedChannel(uint16_t fixed_cid, tL2CAP_FIXED_CHNL_REG* p_freg)

   Register a fixed channel.

   :param fixed_cid: fixed channel id.
   :param p_freg: Channel Callbacks and config.
   :rtype: bool.

.. function:: bool L2CA_ConnectFixedChnl(uint16_t fixed_cid, const RawAddress& rem_bda)

   Connect an fixed signalling channel to a remote device.

   :param fixed_cid: see above.
   :param rem_bda: remote BD ADDRESS.
   :rtype: true if connection started.

.. function:: bool L2CA_ConnectFixedChnl(uint16_t fixed_cid, const RawAddress& rem_bda, uint8_t initiating_phys)

   Connect an fixed signalling channel to a remote device.

   :param initiating_phys: Initial Transportation. EDEDR or LE.

.. function:: uint16_t L2CA_SendFixedChnlData(uint16_t fixed_cid, const RawAddress& rem_bda, BT_HDR* p_buf)

   Write data on a fixed channel.

   :param p_buf: data packets.

.. function:: bool L2CA_RemoveFixedChnl(uint16_t fixed_cid, const RawAddress& rem_bda)

   Remove a fixed channel to a remote device.

   :rtype: true if channel removed.

.. function:: bool L2CA_SetFixedChannelTout(const RawAddress& rem_bda, uint16_t fixed_cid, uint16_t idle_tout)

   Higher layers call this function to set the idle timeout for a fixed channel. The "idle timeout" is the amount of time
   that a connection can remain up with no L2CAP channels on
   it. A timeout of zero means that the connection will be torn
   down immediately when the last channel is removed.

   :param idle_tout: A timeout of 0xFFFF means no timeout. Values are in seconds.

.. function:: bool L2CA_GetCurrentConfig(uint16_t lcid, tL2CAP_CFG_INFO** pp_our_cfg, tL2CAP_CH_CFG_BITS* p_our_cfg_bits, tL2CAP_CFG_INFO** pp_peer_cfg, tL2CAP_CH_CFG_BITS* p_peer_cfg_bits)

   This function returns configurations of L2CAP channel.

   :param pp_our_cfg: pointer of our saved configuration options.
   :param p_our_cfg_bits: valid config in bitmap.
   :param pp_peer_cfg: pointer of peer's saved configuration options.
   :param p_peer_cfg_bits: valid config in bitmap.
   :rtype: true if successful.

.. function:: bool L2CA_GetConnectionConfig(uint16_t lcid, uint16_t* mtu, uint16_t* rcid, uint16_t* handle)

   This function returns configurations of L2CAP channel.

   :param lcid: local CID.
   :param mtu: MTU.
   :param rcid: remote CID.
   :param handle: ACL handle for a link.
   :rtype: true if successful.

.. function:: uint8_t L2CA_DataWrite(uint16_t cid, BT_HDR* p_data)

   Higher layers call this function to write data.

   :param cid: local CID.
   :param p_data: data to write.
   :rtype: uint8_t.
           - L2CAP_DW_SUCCESS, if data accepted, else false
           - L2CAP_DW_CONGESTED, if data accepted and the channel is congested.
           - L2CAP_DW_FAILED, if error.

.. function:: bool L2CA_SetChnlFlushability(uint16_t cid, bool is_flushable)

   Higher layers call this function to set a channel's flushability flags.

   :param cid: local CID.
   :param is_flushable: flushability flags.
   :rtype: true if CID found, else false.

.. function:: uint8_t L2CA_DataWriteEx(uint16_t cid, BT_HDR* p_data, uint16_t flags)

   Higher layers call this function to write data with extended
   flags.

   :param flags: flags : L2CAP_FLUSHABLE_CH_BASED, L2CAP_FLUSHABLE_PKT, L2CAP_NON_FLUSHABLE_PKT.

.. function:: uint16_t L2CA_FlushChannel(uint16_t lcid, uint16_t num_to_flush)

   This function flushes none, some or all buffers queued up
   for xmission for a particular CID. If called with
   L2CAP_FLUSH_CHANS_GET (0), it simply returns the number
   of buffers queued for that CID L2CAP_FLUSH_CHANS_ALL (0xffff)
   flushes all buffers.  All other values specifies the maximum
   buffers to flush.

   :rtype: Number of buffers left queued for that CID.

.. function:: void L2CA_SetMediaStreamChannel(uint16_t local_media_cid, bool status)

   This function is called to set/reset the ccb of active media streaming channel.

   :param local_media_cid: The local cid provided to A2DP to be used for streaming.
   :param status: The status of media streaming on this channel.

.. function:: bool L2CA_isMediaChannel(uint16_t handle, uint16_t channel_id, bool is_local_cid)

   This function returns if the channel id passed as parameter is an A2DP streaming channel.

   :param handle: Connection handle with the remote device.
   :param channel_id: Channel ID.
   :param is_local_cid: Signifies if the channel id passed is local cid or remote cid (true if local, remote otherwise).
