=================
General Operation
=================

L2CAP is based around the concept of **channels**. Each one of the endpoints of
an L2CAP channel is referred to by a channel identifier (CID).

CHANNEL IDENTIFIERS
===================

A channel identifier (CID) is the local name representing a logical channel
endpoint on the device.The null identifier (0x0000) shall never be used as a
destination endpoint. Identifiers from 0x0001 to 0x003F are reserved for
specific L2CAP functions. These channels are referred to as Fixed Channels.

The characteristics of each fixed channel are defined on a per channel basis.
Fixed channel characteristics include configuration parameters (e.g., reliability,
MTU size, QoS), security, and the ability to change parameters using the
L2CAP configuration mechanism.

OPERATION BETWEEN DEVICES
=========================

.. image:: images/l2cap_cids.png
           :alt: Channels between devices


OPERATION BETWEEN LAYERS
========================

L2CAP implementations transfer data between upper layer protocols
and the lower layer protocol. This document lists a number of services that
should be exported by any L2CAP implementation. Each implementation shall
also support a set of signaling commands for use between L2CAP
implementations. L2CAP implementations should also be prepared to accept
certain types of events from lower layers and generate events to upper layers.

.. image:: images/l2cap_layers.png
           :alt: L2CAP transaction model

MODES OF OPERATION
==================

L2CAP channels may operate in one of five different modes as selected for
each L2CAP channel.

The modes are:

- Basic L2CAP Mode
  used by default if no other modes are agreed.
- Flow Control Mode  
- Retransmission Mode
  Flow Control Mode and Retransmission mode shall only be enabled when
  communicating with L2CAP entities that do not support either Enhanced
  Retransmission mode or Streaming mode.
- Enhanced Retransmission Mode
- Streaming Mode
- LE Credit Based Flow Control Mode
  This is the only mode that shall be used for LE L2CAP
  connection oriented channels.

MAPPING CHANNELS TO LOGICAL LINKS
=================================

L2CAP maps channels to Controller logical links, which in turn run over
Controller physical links. All logical links going between a local Controller and
remote Controller run over a single physical link. There is one ACL-U logical
link per BR/EDR physical link and one LE-U logical link per LE physical link,
while there may be multiple AMP-U logical links per AMP physical link.
