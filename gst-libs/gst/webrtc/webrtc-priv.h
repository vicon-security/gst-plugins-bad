/* GStreamer
 * Copyright (C) 2017 Matthew Waters <matthew@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __GST_WEBRTC_PRIV_H__
#define __GST_WEBRTC_PRIV_H__

#include <gst/gst.h>
#include <gst/webrtc/webrtc_fwd.h>
#include <gst/webrtc/rtpsender.h>
#include <gst/webrtc/rtpreceiver.h>

G_BEGIN_DECLS

/**
 * GstWebRTCRTPTransceiver:
 * @mline: the mline number this transceiver corresponds to
 * @mid: The media ID of the m-line associated with this
 * transceiver. This association is established, when possible,
 * whenever either a local or remote description is applied. This
 * field is NULL if neither a local or remote description has been
 * applied, or if its associated m-line is rejected by either a remote
 * offer or any answer.
 * @stopped: Indicates whether or not sending and receiving using the paired
 * #GstWebRTCRTPSender and #GstWebRTCRTPReceiver has been permanently disabled,
 * either due to SDP offer/answer
 * @sender: The #GstWebRTCRTPSender object responsible sending  data to the
 * remote peer
 * @receiver: The #GstWebRTCRTPReceiver object responsible for receiver data from
 * the remote peer.
 * @direction: The transceiver's desired direction.
 * @current_direction: The transceiver's current direction (read-only)
 * @codec_preferences: A caps representing the codec preferences (read-only)
 * @kind: Type of media (Since: 1.20)
 *
 * Mostly matches the WebRTC RTCRtpTransceiver interface.
 *
 * Since: 1.16
 */
/**
 * GstWebRTCRTPTransceiver.kind:
 *
 * Type of media
 *
 * Since: 1.20
 */
struct _GstWebRTCRTPTransceiver
{
  GstObject                         parent;
  guint                             mline;
  gchar                            *mid;
  gboolean                          stopped;

  GstWebRTCRTPSender               *sender;
  GstWebRTCRTPReceiver             *receiver;

  GstWebRTCRTPTransceiverDirection  direction;
  GstWebRTCRTPTransceiverDirection  current_direction;

  GstCaps                          *codec_preferences;
  GstWebRTCKind                     kind;

  gpointer                          _padding[GST_PADDING];
};

struct _GstWebRTCRTPTransceiverClass
{
  GstObjectClass        parent_class;

  /* FIXME; reset */
  gpointer              _padding[GST_PADDING];
};

/**
 * GstWebRTCRTPSender:
 * @transport: The transport for RTP packets
 * @send_encodings: Unused
 * @priority: The priority of the stream (Since: 1.20)
 *
 * An object to track the sending aspect of the stream
 *
 * Mostly matches the WebRTC RTCRtpSender interface.
 *
 * Since: 1.16
 */
/**
 * GstWebRTCRTPSender.priority:
 *
 * The priority of the stream
 *
 * Since: 1.20
 */
struct _GstWebRTCRTPSender
{
  GstObject                          parent;

  /* The MediStreamTrack is represented by the stream and is output into @transport as necessary */
  GstWebRTCDTLSTransport            *transport;

  GArray                            *send_encodings;
  GstWebRTCPriorityType              priority;

  gpointer                          _padding[GST_PADDING];
};

struct _GstWebRTCRTPSenderClass
{
  GstObjectClass        parent_class;

  gpointer              _padding[GST_PADDING];
};

GST_WEBRTC_API
GstWebRTCRTPSender *        gst_webrtc_rtp_sender_new                   (void);

/**
 * GstWebRTCRTPReceiver:
 * @transport: The transport for RTP packets
 *
 * An object to track the receiving aspect of the stream
 *
 * Mostly matches the WebRTC RTCRtpReceiver interface.
 *
 * Since: 1.16
 */
struct _GstWebRTCRTPReceiver
{
  GstObject                          parent;

  /* The MediStreamTrack is represented by the stream and is output into @transport as necessary */
  GstWebRTCDTLSTransport            *transport;

  gpointer                          _padding[GST_PADDING];
};

struct _GstWebRTCRTPReceiverClass
{
  GstObjectClass            parent_class;

  gpointer                  _padding[GST_PADDING];
};

GST_WEBRTC_API
GstWebRTCRTPReceiver *      gst_webrtc_rtp_receiver_new                 (void);


/**
 * GstWebRTCICETransport:
 */
struct _GstWebRTCICETransport
{
  GstObject                          parent;

  GstWebRTCICERole                   role;
  GstWebRTCICEComponent              component;

  GstWebRTCICEConnectionState        state;
  GstWebRTCICEGatheringState         gathering_state;

  /* Filled by subclasses */
  GstElement                        *src;
  GstElement                        *sink;

  gpointer                          _padding[GST_PADDING];
};

struct _GstWebRTCICETransportClass
{
  GstObjectClass               parent_class;

  gboolean                  (*gather_candidates)        (GstWebRTCICETransport * transport);

  gpointer                  _padding[GST_PADDING];
};

GST_WEBRTC_API
void            gst_webrtc_ice_transport_connection_state_change    (GstWebRTCICETransport * ice,
                                                                     GstWebRTCICEConnectionState new_state);
GST_WEBRTC_API
void            gst_webrtc_ice_transport_gathering_state_change     (GstWebRTCICETransport * ice,
                                                                     GstWebRTCICEGatheringState new_state);
GST_WEBRTC_API
void            gst_webrtc_ice_transport_selected_pair_change       (GstWebRTCICETransport * ice);
GST_WEBRTC_API
void            gst_webrtc_ice_transport_new_candidate              (GstWebRTCICETransport * ice, guint stream_id, GstWebRTCICEComponent component, gchar * attr);


G_END_DECLS

#endif /* __GST_WEBRTC_PRIV_H__ */