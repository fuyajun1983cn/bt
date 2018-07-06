=============
STATE MACHINE
=============

GENERAL RULES FOR THE STATE MACHINE
===================================

The following states have been defined to clarify the protocol; the actual
number of states and naming in a given implementation is outside the scope of
this specification:

- CLOSED – channel not connected.

- WAIT_CONNECT – a connection request has been received, but only a
  connection response with indication “pending” can be sent.

- WAIT_CONNECT_RSP – a connection request has been sent, pending a
  positive connect response.

- CONFIG – the different options are being negotiated for both sides; this
  state comprises a number of substates

- OPEN – user data transfer state.

- WAIT_DISCONNECT – a disconnect request has been sent, pending a
  disconnect response.

- WAIT_CREATE – a channel creation request has been received, but only a
  response with indication “pending” can be sent. This state is similar to
  WAIT_CONNECT.

- WAIT_CREATE_RSP – a channel creation request has been sent, pending
  a channel creation response. This state is similar to WAIT_CONNECT_RSP.

- WAIT_MOVE – a request to move the current channel to another Controller
  has been received, but only a response with indication “pending” can be
  sent.

- WAIT_MOVE_RSP – a request to move a channel to another Controller has
  been sent, pending a move response

- WAIT_MOVE_CONFIRM – a response to the move channel request has
  been sent, waiting for a confirmation of the move operation by the initiator
  side

- WAIT_CONFIRM_RSP – a move channel confirm has been sent, waiting for
  a move channel confirm response.

There is a single state machine for each L2CAP connection-oriented channel
that is active. A state machine is created for each new L2CAP_ConnectReq
received. The state machine always starts in the CLOSED state.

TIMERS EVENTS
=============

RTX
---

The Response Timeout eXpired (RTX) timer is used to terminate the channel
when the remote endpoint is unresponsive to signaling requests.

This timer is started when a signaling request is sent to the remote device.
This timer is disabled when the response is received.

If a duplicate Request message is sent, the RTX
timeout value shall be reset to a new value at least double the previous value.
When retransmitting the Request message, the context of the same state shall
be assumed as with the original transmission.

Implementations have the responsibility to decide on the maximum number of
Request retransmissions performed at the L2CAP level before terminating the
channel identified by the Requests. The exception is fixed channel CIDs since
they can never be terminated.

The value of this timer is implementation-dependent but the minimum initial
value is 1 second and the maximum initial value is 60 seconds.

One RTX timer shall exist for each outstanding signaling request, including each Echo
Request.

ERTX
----

The Extended Response Timeout eXpired (ERTX) timer is used in place of the
RTX timer when it is suspected the remote endpoint is performing additional
processing of a request signal.

This timer is started when the remote endpoint
responds that a request is pending, e.g., when an L2CAP_ConnectRsp event
with a “connect pending” result (0x0001) is received.

The value of this timer is implementation-dependent but the minimum initial
value is 60 seconds and the maximum initial value is 300 seconds. Similar to
RTX, there MUST be at least one ERTX timer for each outstanding request that
received a Pending response. There should be at most one (RTX or ERTX)
associated with each outstanding request.

