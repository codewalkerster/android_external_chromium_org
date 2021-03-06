// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/quic/quic_flags.h"

// TODO(rtenneti): Remove this.
// Do not flip this flag until the flakiness of the
// net/tools/quic/end_to_end_test is fixed.
// If true, then QUIC connections will track the retransmission history of a
// packet so that an ack of a previous transmission will ack the data of all
// other transmissions.
bool FLAGS_track_retransmission_history = false;

bool FLAGS_quic_allow_oversized_packets_for_test = false;

// When true, the use time based loss detection instead of nack.
bool FLAGS_quic_use_time_loss_detection = false;

// If true, it will return as soon as an error is detected while validating
// CHLO.
bool FLAGS_use_early_return_when_verifying_chlo = true;

// If true, QUIC crypto reject message will include the reasons for rejection.
bool FLAGS_send_quic_crypto_reject_reason = false;

// If true, QUIC connections will support FEC protection of data while sending
// packets, to reduce latency of data delivery to the application. The client
// must also request FEC protection for the server to use FEC.
bool FLAGS_enable_quic_fec = false;

// If true, a QUIC connection with too many unfinished streams will be closed.
bool FLAGS_close_quic_connection_unfinished_streams_2 = false;

// When true, defaults to BBR congestion control instead of Cubic.
bool FLAGS_quic_use_bbr_congestion_control = false;

// If true, only times out QUIC connections when there has been network
// activity; packets sent or received.
bool FLAGS_quic_timeouts_require_activity = false;

// If true, the server will accept slightly more streams than the negotiated
// limit.
bool FLAGS_quic_allow_more_open_streams = false;
