=======================
A2DP Code Flow Analysis
=======================


- a2dp sink delay reporting

  Keys to check if the delay reporting is working or not.

  OMR1 Branch:

  1) snoop log

     .. code-block:: sh

        529                         2                              Single Packet     Slave     DELAYREPORT   2500       2              13           00:00:00.002000                5/23/2018 1:05:34.020000 AM  
        530                         2                              Single Packet     Master DELAYREPORT                   2              10           00:00:00.003000                5/23/2018 1:05:34.023000 AM

  2) Key logs for BT host stack processing Delay report:

     .. code-block:: sh

        bt_btif : bta_av_ssm_execute(): AV Sevent(0x41)=0x1229(AVDT_DELAY_RPT) state=2(OPENING)
        bt_btif : bta_av_co_audio_delay: handle: x41, delay:0x96
        bt_btif : btif_av_get_sink_latency, return sink latency: 150

  3) Key logs for audio fetching sink delay (Split A2dp)

     .. code-block:: sh

        bthost_ipc: audio_get_a2dp_sink_latency: state = AUDIO_A2DP_STATE_STARTED

  4) Key logs for audio fetch sink delay (Non-split A2dp)

     .. code-block:: sh

        A2DP_CTRL_GET_SINK_LATENCY


  P Branch:

  1) Snoop log:

     .. code-block:: sh

        529         2                              Single Packet     Slave     DELAYREPORT   2500       2              13           00:00:00.002000                5/23/2018 1:05:34.020000 AM
        530	        2                              Single Packet     Master DELAYREPORT                   2              10           00:00:00.003000        5/23/2018 1:05:34.023000 AM  


  2) Key logs for BT host stack processing Delay report:

     .. code-block:: sh

        bt_btif : bta_av_ssm_execute(): AV Sevent(0x42)=0x1229(AVDT_DELAY_RPT) state=2(OPENING)
        bt_btif : bta_av_delay_rpt: delay report value: 1500
        bt_btif : bta_av_co_audio_delay: handle: x42, delay:0x5dc


  3) Key logs for audio fetching sink delay (Split A2dp)

     .. code-block:: sh

        btif_a2dp_audio_interface: a2dp_get_sink_latency
        bt_btif : btif_a2dp_control_get_audio_delay: DELAY: 150 ms, index: 1
        btif_a2dp_audio_interface: send_sink_latency = 150

  4) Key logs for audio fetch sink delay (Non-split A2dp)

     .. code-block:: sh

        btif_a2dp_recv_ctrl_data: A2DP_CTRL_GET_PRESENTATION_POSITION
        Delay Rpt: total bytes read



