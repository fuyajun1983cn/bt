===============================================
 Available AT-commands with Hands-Free Profile
===============================================

The AT commands and indications that are available for the Bluetooth Hands-Free profile are listed below.

- **ATA**

  Standard call answer AT command.

- **ATDdd…dd;**

  Standard AT command intended for placing a call to a phone number. Only voice calls are covered in this
  specification.

- **ATD>nnn...;**

  Extension of the standard ATD command, intended for memory dialing. Only voice calls are covered in this
  specification.

- **AT+CCWA**

  Standard “Call Waiting notification” AT command. Within the AT+CCWA=[<n>[,<mode>[,<class>]]]command,
  only enabling/disabling of the Call Waiting notification unsolicited result code +CCWA , using the <n>
  parameter, is covered in this specification.

- **AT+CHLD**

  Standard call hold and multiparty handling AT command.

- **AT+CHUP**

  Standard hang-up AT command. Execution command causes the AG to terminate the currently active call.
  This command shall have no impact on the state of any held call.

- **AT+CIND**

  Standard indicator update AT command.

- **+CIND**

  Standard list of current phone indicators.

- **AT+CLCC**

  Standard list current calls command.

- **+CLCC**

  Standard list current calls result code

- **AT+COPS**

  The AT+COPS=3,0 shall be sent by the HF to the AG prior to sending the AT+COPS? command.
  AT+COPS=3,0 sets the format of the network operator string to the long format alphanumeric.

- **AT+CMEE**

  Standard AT command used to enable the use of result code.

- **AT+CLIP**

  Standard “Calling Line Identification notification” activation AT command. It enables/disables the Calling Line
  Identification notification unsolicited result code +CLIP.

- **+CLIP**

  Standard “Calling Line Identification notification” unsolicited result code.

- **AT+CMER**

  Standard event reporting activation/deactivation AT command.

- **+CIEV**

  Standard “indicator events reporting” unsolicited result code.

- **AT+VTS**

  Standard DTMF generation AT command. Only the AT+VTS=<DTMF> command format is covered in this
  specification.

- **AT+CNUM**

  AT+CNUM (Retrieve Subscriber Number Information)

- **+CNUM**

  Standard Response used for sending the “Subscriber Number Information” from AG to HF.

- **AT+BIA**

  Bluetooth Indicators Activation. Command used by HF to activate / deactivate individual indicators.

- **AT+BINP**

  Command used for requesting some specific data input from the AG4. On reception of this command the AG
  shall perform the proper actions such that the requested information is sent back to the HF using the +BINP
  response.

- **+BINP**

  Command used for requesting some specific data input from the AG4. On reception of this command the AG
  shall perform the proper actions such that the requested information is sent back to the HF using the +BINP
  response.

- **AT+BLDN**

  Bluetooth Last Dialed Number

- **AT+BVRA**

  Bluetooth Voice Recognition Activation

- **+BVRA**

  Bluetooth Voice Recognition Activation. Unsolicited result code used to notify the HF when the voice
  recognition function in the AG is activated/deactivated autonomously from the AG.

- **AT+BRSF**

  (Bluetooth Retrieve Supported Features. Notifies the AG of the supported features available in the HF, and
  requests information about the supported features in the AG. The supported features shall be represented as
  a decimal value.

- **+BRSF**

  Bluetooth Retrieve Supported Features).Result code sent by the AG in response to the AT+BRSF command,
  used to notify the HF what features are supported in the AG. The supported features shall be represented as
  a decimal value.

- **AT+NREC** (Noise Reduction and Echo Canceling)

  Command issued to disable any Echo Canceling and Noise Reduction functions embedded in the AG.
  Only support for execution command is mandated. Neither the read nor test commands are mandatory.

- **AT+VGM**

  Gain of Microphone. Command issued by the HF to report its current microphone gain level setting to the AG.
  <gain> is a decimal numeric constant, relating to a particular (implementation dependent) volume level
  controlled by the HF. This command does not change the microphone gain of the AG; it simply indicates the
  current value of the microphone gain in the HF.

- **AT+VGS** (Gain of Speaker)

  Command issued by the HF to report its current speaker gain level setting to the AG. <gain> is a decimal
  numeric constant, relating to a particular (implementation dependent) volume level controlled by the HF. This
  command does not change the speaker gain of the AG; it simply indicates the current value of the speaker
  volume in the HF.

- **+VGM** (Gain of Microphone)

  Unsolicited result code issued by the AG to set the microphone gain of the HF. <gain> is a decimal numeric
  constant, relating to a particular (implementation dependent) volume level controlled by the HF.

- **+VGS** (Gain of Speaker)

  Unsolicited result code issued by the AG to set the speaker gain of the HF. <gain> is a decimal numeric
  constant, relating to a particular (implementation dependent) volume level controlled by the HF.

- **++BSIR** (Bluetooth Setting of In-band Ring tone)

  Unsolicited result code issued by the AG to indicate to the HF that the in-band ring tone setting has been
  locally changed. The HF may react accordingly by changing its own alert method.

- **AT+BTRH** (Bluetooth Response and Hold Feature)

  Command issued by the HF for the “Response and Hold” feature in the AG. This specification defines the use
  of the set and read command. The AT+BTRH? command shall be used by the HF to query the current
  “Response and Hold” state of the AG.

- **+BTRH** (Bluetooth Response and Hold Feature)

  Result code used to notify the HF when-ever the incoming call is either put on hold or accepted or rejected.
  The AG shall also respond back with this response for the AT+BTRH? command from the HF.


Phonebook specific AT commands
==============================

- **AT+CPBS=?**

  Lists the phonebooks that the phone contains. (Choose phonebook storage)

  Returns: +CPBS: ("ME","SM","MT","ON","DC","MC","RC","EN","AD","QD","SD","FD")

  +CPBS="ME" sets the "retrieve mode" to the internal phonebook.

  +CPBS="SM" sets the "retrieve mode" to the SIM phonebook.

- **AT+CPBR=?**

  Describes the phonebook selected above. (Simple) This gives the max number of entries the phone can
  contain. It also gives the maximum phone number (or email address) length and name length.

  .. note::
     You can substitute +MPBR for any +CPBR command, but the phone returns a much more specific
     (and less intelligible) response containing more fields that may act as internal “programming” flags of some
     sort

  Returns: +CPBR: (1-1000),40,24

- **AT+CPBR=[beginning index],[ending index]**

  Returns a list of numbers with the index between the two numbers entered. Also denotes what TYPE of
  phonebook entry was selected.

  Returns: +CPBR: 9,"18005555555",129,"Contact Name" – 129 refers to a phone number.

  Returns: +CPBR: 18,"user@domain.net",128,"Contact Name" – 128 refers to an email.

- **AT+CPBR=[index]**

  Returns the specified index.

  Returns: +CPBR: 18,"user@domain.net",128,"Contact Name"

- **AT+MPBF="Name"**

  Searches the phonebook for the Name or string.

- **AT+MPBR=?**

  Similar to above, but a more verbose result is displayed.

  Returns: +MPBR: 1-1000,40,24,8,0-1,50,(0,2,4,6,9-30,255),(0),(0-1),(1-30),(255),25,(0-
  1,255),264,(0),0,0,0,0,0,0,0

  - 1-1000 denotes the number of entries that can be stored on the selected (+CPBS) phonebook.

  - 40 represents the number of characters that the email or phone number can have

  - 24 indicates the number of characters the “friendly” name can have.

  - The 8 refers to the different “types” of phonebook entry (i.e. Mobile, Main, Email, Home, Fax, Work …
    etc).

  - The +CPBR command does not list anything after the 24 (as seen above), so there are times when
    the +MPBR may be useful.

- **AT+MPBR=[index]**

  Returns: +MPBR: 18,"user@domain.net",128,"Contact

  Name",6,0,255,0,0,1,255,255,0,"",0,0,"","","","","","","",""

SMS specific AT commands
========================

- **AT+CMGF=1**

  This tells the phone to display the entries as text rather than binary. +CMFG=0 would display the data in
  binary format.

- **AT+CPMS=?**

  This displays all of the locations in which the phone can save the SMS messages.

  Returns: +CPMS: ("MT","IM","OM","BM","DM"),("OM","DM"),("IM")

- **AT+CMGL=?**

  Returns the options on which messages you wish to display.

  Returns: +CMGL: ("REC UNREAD", "REC READ", "STO UNSENT", "STO SENT", "ALL")

- **AT+CMGL="ALL"**

  Selects and displays all of the SMS messages on the selected source.

- **AT#PMODE=1**

  In order to retrieve text messages and other information, Samsung phones must be in this mode.

- **AT#PSRMR=?**

  Returns the parameters to obtain text messages (Samsung).

  Returns: #PSRMR: (0-349)

Apple specific AT commands with Hands-Free profile
==================================================

- HFP Command AT+XAPL

  Enables custom AT commands from a headset.

- HFP Command AT+IPHONEACCEV

  Reports a headset state change.


