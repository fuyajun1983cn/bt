========================
AVRCP Code Flow Analysis
========================

- AVRCP interface callback

  .. image:: ./images/2018072701.png

- update playback status

  1. add a new avrcp device to the connected device list

     **setAvrcpConnectedDevice**

     this is mainly for dual a2dp cases.

  2. whenever we need to update media state, call **updateCurrentMediaState**

     it will call **updatePlaybackState** further to update the playback status to the stack through **registerNotificationRspPlayStatusNative**.

     it's notification response to the remote carkit.

     .. image:: ./images/2018072702.png

     note that, before send notification response to the remote. we'll check if remote send suspend request to us before,
     if yes, we'll check if the current playback status is changed to playing state or not, if it's the playing state, we need to
     send a2dp start request from our side, because audio side will never send a2dp start request in such case. 

     
