==================
GENERAL PROCEDURES
==================

CONFIGURATION PROCESS
=====================

Configuration consists of two processes, the Standard process and the
Lockstep process. The Lockstep process shall be used if both L2CAP entities
support the Extended Flow Specification option otherwise the Standard
process shall be used.

For both processes, configuring the channel parameters shall be done
independently for both directions. Both configurations may be done in parallel.

two sides will sennd configuration request/response independently.

If a device needs to establish the value of a configuration parameter the remote
device will accept, then it must wait for a configuration request containing that
configuration parameter to be sent from the remote device.

If an L2CAP entity receives a Configuration Request while it is waiting for a response it shall not
block sending the Configuration Response, otherwise the configuration
process may deadlock.

Standard Configuration Process
------------------------------

For the Standard process the following general procedure shall be used for
each direction:

1. Local device informs the remote device of the parameters that the local
   device will accept using a Configuration Request.

2. Remote device responds, agreeing or disagreeing with these values,
   including the default ones, using a Configuration Response.

3. The local and remote devices repeat steps (1) and (2) until agreement on all
   parameters is reached.

The decision on the amount of time (or messages) spent configuring the
channel parameters before terminating the configuration is left to the
implementation, but it shall not last more than ``120`` seconds.


OPERATION COLLISION RESOLUTION
==============================

When two devices request the same operation by sending a request packet
with the same code, a collision can occur. Some operations require collision
resolution.The following algorithm shall be used by both devices to determine
which request to reject.

1. Set i=0 (representing the least significant octet of the BD_ADDR).

2. Compare the octet[i] of the BD_ADDR of both devices. If the octets
   are not equal go to step 4.

3. Increment i by 1. Go to step 2.

4. The device with the larger BD_ADDR octet shall reject the request
   from the other device.

PRIORITIZING DATA OVER HCI
==========================

In order for guaranteed channels to meet their guarantees, L2CAP should
prioritize traffic over the HCI transport in devices that support HCI. Packets for
Guaranteed channels should receive higher priority than packets for Best Effort
channels.




