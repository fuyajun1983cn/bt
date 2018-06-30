============
Introduction
============

The *Logical Link Control and Adaptation Layer Protocol*, referred to as **L2CAP**. **L2CAP** provides connectionoriented
and connectionless data services to upper layer protocols with protocol multiplexing capability and segmentation
and reassembly

L2CAP FEATURES
==============

The functional requirements for L2CAP include:

  * protocol/channel multiplexing
  * segmentation and reassembly (SAR)
  * per-channel flow control
  * error control


**L2CAP architectural blocks**

.. image:: images/l2cap_blocks.png

* **Channel Manager**
  provides the control plane functionality and is responsible for all internal signaling, L2CAP peer-to-peer signaling and signaling with higher and lower layers.

* **Resource Manager**
  responsible for providing a frame relay service to the Channel Manager, the Retransmission and Flow Control block and those application data streams that do not require Retransmission and Flow Control services.

  It is responsible for coordinating the transmission and reception of packets related to multiple L2CAP channels over the facilities offered at the lower layer interface.
  
  * **Retransmission and Flow Control**
    provides per-channel flow control and error recovery using packet retransmission.



Protocol/channel multiplexing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

L2CAP supports multiplexing over individual Controllers and across multiple
Controllers. **An L2CAP channel shall operate over one Controller at a time**.

During channel setup, *protocol multiplexing* capability is used to route the
connection to the correct upper layer protocol.

For data transfer, *logical channel multiplexing* is needed to distinguish
between multiple upper layer entities. There may be more than one upper
layer entity using the same protocol.


Segmentation and reassembly
~~~~~~~~~~~~~~~~~~~~~~~~~~~

With the frame relay service offered by the Resource Manager, the length of
transport frames is controlled by the individual applications running over
L2CAP. Many multiplexed applications are better served if L2CAP has
control over the PDU length.


Flow control per L2CAP channel
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Controllers provide error and flow control for data going over the air and HCI
flow control exists for data going over an HCI transport. When several data
streams run over the same Controller using separate L2CAP channels, each
channel requires individual flow control. A window based flow control
scheme is provided.


Error control and retransmissions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When L2CAP channels are moved from one Controller to another data can
be lost. Also, some applications require a residual error rate much smaller
than some Controllers can deliver. L2CAP provides error checks and
retransmissions of L2CAP PDUs.

The error checking in L2CAP protects
against errors due to Controllers falsely accepting packets that contain
errors but pass Controller-based integrity checks. L2CAP error checking and
retransmission also protect against loss of packets due to flushing by the
Controller.

The error control works in conjunction with flow control in the
sense that the flow control mechanism will throttle retransmissions as well
as first transmissions.

Support for Streaming
~~~~~~~~~~~~~~~~~~~~~

Streaming applications such as audio set up an L2CAP channel with an
agreed-upon data rate and do not want flow control mechanisms, including
those in the Controller, to alter the flow of data. A **flush timeout** is used to
keep data flowing on the transmit side. Streaming mode is used to stop HCI
and Controller based flow control from being applied on the receiving side.

Fragmentation and Recombination
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Some Controllers may have limited transmission capabilities and may
require fragment sizes different from those created by L2CAP segmentation.
Therefore layers below L2CAP may further fragment and recombine L2CAP
PDUs to create fragments which fit each layer’s capabilities. During
transmission of an L2CAP PDU, many different levels of fragmentation and
recombination may occur in both peer devices.

Each layer of the protocol stack may pass on different sized fragments of
L2CAP PDUs, and the size of fragments created by a layer may be different
in each peer device. However the PDU is fragmented within the stack, the
receiving L2CAP entity still recombines the fragments to obtain the original
L2CAP PDU.


Quality of Service
~~~~~~~~~~~~~~~~~~~

The L2CAP connection establishment process allows the exchange of
information regarding the quality of service (QoS) expected between two
Bluetooth devices. Each L2CAP implementation monitors the resources
used by the protocol and ensures that QoS contracts are honored.

For a BR/EDR or BR/EDR/LE Controller, L2CAP may support both
isochronous (Guaranteed) and asynchronous (Best Effort) data flows over
the same ACL logical link by marking packets as automatically-flushable or
non-automatically-flushable by setting the appropriate value for the
**Packet_Boundary_Flag** in the HCI ACL Data Packet.

Automatically-flushable L2CAP packets are flushed
according to the automatic flush timeout set for the ACL logical link on which
the L2CAP channels are mapped. Nonautomatically-flushable L2CAP packets are not affected by the automatic
flush timeout and will not be flushed. All L2CAP packets can be flushed by
using the HCI Flush command.


ASSUMPTIONS
===========

The protocol is designed based on the following assumptions:

* Controllers provide orderly delivery of data packets, For devices with a BR/EDR or BR/EDR/LE Controller,
  no more than one ACL-U logical link exists between any two devices. For devices with a
  BR/EDR/LE or LE Controller, no more than one LE-U logical link exists
  between any two devices.

* Controllers always provide the impression of full-duplex communication channels.

* The L2CAP layer provides a channel with a degree of reliability based on the
  mechanisms available in Controllers and with additional packet
  segmentation, error detection, and retransmission that can be enabled in the
  enhanced L2CAP layer.

* Controllers provide error and flow control for data going over the air and HCI
  flow control exists for data going over an HCI transport but some applications will want better error control than some Controllers provide.


SCOPE
=====

The following features are outside the scope of L2CAP’s responsibilities:

- L2CAP does not transport synchronous data designated for SCO or eSCO logical transports.

- L2CAP does not support a reliable broadcast channel.
