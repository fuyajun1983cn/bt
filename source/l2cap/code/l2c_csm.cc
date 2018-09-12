

/******************************************************************************
 *
 *  This file contains the L2CAP channel state machine
 *
 ******************************************************************************/
 /*l2c_ccb_timer相关的一些超时值*/
 {
	#define L2CAP_CHNL_CONNECT_TIMEOUT_MS (20 * 1000)      /* 20 seconds */
	#define L2CAP_CHNL_CONNECT_EXT_TIMEOUT_MS (120 * 1000) /* 120 seconds */
	#define L2CAP_CHNL_CFG_TIMEOUT_MS (30 * 1000)          /* 30 seconds */
	#define L2CAP_CHNL_DISCONNECT_TIMEOUT_MS (10 * 1000)   /* 10 seconds */
	#define L2CAP_DELAY_CHECK_SM4_TIMEOUT_MS (2 * 1000)    /* 2 seconds */
 }

/* Define the possible L2CAP channel states. The names of
 * the states may seem a bit strange, but they are taken from
 * the Bluetooth specification.
*/
typedef enum {
  CST_CLOSED,                  /* Channel is in closed state */
    --> l2c_csm_closed
  CST_ORIG_W4_SEC_COMP,        /* Originator waits security clearence */
    --> l2c_csm_orig_w4_sec_comp
  CST_TERM_W4_SEC_COMP,        /* Acceptor waits security clearence */
    --> l2c_csm_term_w4_sec_comp
  CST_W4_L2CAP_CONNECT_RSP,    /* Waiting for peer conenct response */
    --> l2c_csm_w4_l2cap_connect_rsp
  CST_W4_L2CA_CONNECT_RSP,     /* Waiting for upper layer connect rsp */
    --> l2c_csm_w4_l2ca_connect_rsp
  CST_CONFIG,                  /* Negotiating configuration */
    --> l2c_csm_config
  CST_OPEN,                    /* Data transfer state */
    --> l2c_csm_open
  CST_W4_L2CAP_DISCONNECT_RSP, /* Waiting for peer disconnect rsp */
    --> l2c_csm_w4_l2cap_disconnect_rsp
  CST_W4_L2CA_DISCONNECT_RSP   /* Waiting for upper layer disc rsp */
    --> l2c_csm_w4_l2ca_disconnect_rsp
} tL2C_CHNL_STATE;




/*******************************************************************************
 *
 * Function         l2c_csm_execute
 *
 * Description      This function executes the state machine.
 *
 * Returns          void
 *
 ******************************************************************************/
void l2c_csm_execute(tL2C_CCB* p_ccb, uint16_t event, void* p_data) {
  if (!l2cu_is_ccb_active(p_ccb)) {
    L2CAP_TRACE_WARNING("%s CCB not in use, event (%d) cannot be processed",
                        __func__, event);
    return;
  }

  switch (p_ccb->chnl_state) {
    case CST_CLOSED:
      l2c_csm_closed(p_ccb, event, p_data);
      break;

    case CST_ORIG_W4_SEC_COMP:
      l2c_csm_orig_w4_sec_comp(p_ccb, event, p_data);
      break;

    case CST_TERM_W4_SEC_COMP:
      l2c_csm_term_w4_sec_comp(p_ccb, event, p_data);
      break;

    case CST_W4_L2CAP_CONNECT_RSP:
      l2c_csm_w4_l2cap_connect_rsp(p_ccb, event, p_data);
      break;

    case CST_W4_L2CA_CONNECT_RSP:
      l2c_csm_w4_l2ca_connect_rsp(p_ccb, event, p_data);
      break;

    case CST_CONFIG:
      l2c_csm_config(p_ccb, event, p_data);
      break;

    case CST_OPEN:
      l2c_csm_open(p_ccb, event, p_data);
      break;

    case CST_W4_L2CAP_DISCONNECT_RSP:
      l2c_csm_w4_l2cap_disconnect_rsp(p_ccb, event, p_data);
      break;

    case CST_W4_L2CA_DISCONNECT_RSP:
      l2c_csm_w4_l2ca_disconnect_rsp(p_ccb, event, p_data);
      break;

    default:
      L2CAP_TRACE_DEBUG("Unhandled event! event = %d", event);
      break;
  }
}

/* 流程分析 */
{
	1. 任何时候，当有l2cap层的事件发生时，通过执行 l2c_csm_execute 把对应的事件route到相应的状态机处理函数中去。 
	
	2. CLOSED状态
	L2CEVT_LP_CONNECT_CFM/L2CEVT_L2CA_CONNECT_REQ/L2CEVT_L2CAP_CONNECT_REQ
	{
		p_ccb->chnl_state = CST_ORIG_W4_SEC_COMP;
		go to security authentication process.
		if (BTM_SUCCESS) {
			event = L2CEVT_SEC_COMP; 
		} else (BTM_DELAY_CHECK) {
			event = L2CEVT_TIMEOUT;
		} else {
			event = L2CEVT_SEC_COMP_NEG;
		}
	}
	
	3. ORIG_W4_SEC_COMP状态 
	L2CEVT_SEC_COMP
	{
		p_ccb->chnl_state = CST_W4_L2CAP_CONNECT_RSP;
		l2cu_send_peer_connect_req //send connection request 
	}
	
	4. W4_L2CAP_CONNECT_RSP状态 
	L2CEVT_L2CAP_CONNECT_RSP
	{
		if (BLE) {
			p_ccb->chnl_state = CST_OPEN;
		} else {
			p_ccb->chnl_state = CST_CONFIG;
		}
	}
	5. CONFIG状态 
	L2CEVT_L2CAP_CONFIG_REQ
	{
		l2cu_process_peer_cfg_req
		if (L2CAP_PEER_CFG_OK) {
			indicate to upper layer 
		} else if(L2CAP_PEER_CFG_DISCONNECT) {
			l2cu_disconnect_chnl
		} else {
			config is imcompatible, re-config
			l2cu_send_peer_config_rsp(p_ccb, p_cfg);
		}
	}
	L2CEVT_L2CAP_CONFIG_RSP
	{
		l2cu_process_peer_cfg_rsp
		if (p_cfg->result != L2CAP_CFG_PENDING) {
			p_ccb->config_done |= OB_CFG_DONE;  //received peer config
			if (p_ccb->config_done & IB_CFG_DONE) {//upper layer already send config response to peer
				if (mode is imcompatible) {
					l2cu_send_peer_disc_req
					l2cu_release_ccb
				}
				
				p_ccb->config_done |= RECONFIG_FLAG; //true after initial config 
				p_ccb->chnl_state = CST_OPEN;
			}
	}
	6. OPEN
	L2CEVT_L2CAP_DATA //receive peer data
	{
		pL2CA_DataInd_Cb
	}
	L2CEVT_L2CA_DATA_WRITE //upper layer write data
	{
		l2c_enqueue_peer_data
		l2c_link_check_send_pkts
	}
	L2CEVT_L2CAP_CONFIG_REQ/L2CEVT_L2CA_CONFIG_REQ
	{
		p_ccb->chnl_state = CST_CONFIG;
	}
	
}

/* message exchange between link and channel */
{
	1. L2CEVT_LP_DISCONNECT_IND
	{
		send by l2c_link_hci_disc_comp /* handler for HCI Disconnect Complete */
		        l2c_link_timeout   /* link timeout */
	}
	
	2. L2CEVT_LP_CONNECT_CFM
	
	
	3. L2CEVT_LP_CONNECT_CFM_NEG
}


bit_rate = 8 * frame_length * fs / nrof_subbands / nrof_blocks,
where fs, nrof_subbands and nrof_blocks denote sampling frequency, number of subbands and number of blocks, respectively. Bit Rate is expressed in kb/s, because fs is expressed in kHz. The Frame Length (frame_length) is expressed in bytes as
frame_length = 4 + (4 * nrof_subbands * nrof_channels ) / 8 + nrof_blocks * nrof_channels * bitpool / 8 .
for the MONO and DUAL_CHANNEL channel modes, and
frame_length = 4 + (4 * nrof_subbands * nrof_channels ) / 8 + (join * nrof_subbands + nrof_blocks * bitpool ) / 8.
for the STEREO and JOINT_ STEREO channel modes.
Here, nrof_channels and bitpool denote number of channels and bitpool value, respectively. When joint stereo is used, join = 1, otherwise 0. 