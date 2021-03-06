/*
 *  Copyright 2017 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "sdk/android/src/jni/pc/rtpsender.h"

#include "sdk/android/generated_peerconnection_jni/jni/RtpSender_jni.h"
#include "sdk/android/native_api/jni/java_types.h"
#include "sdk/android/src/jni/jni_helpers.h"
#include "sdk/android/src/jni/pc/rtpparameters.h"

namespace webrtc {
namespace jni {

ScopedJavaLocalRef<jobject> NativeToJavaRtpSender(
    JNIEnv* env,
    rtc::scoped_refptr<RtpSenderInterface> sender) {
  if (!sender)
    return nullptr;
  // Sender is now owned by the Java object, and will be freed from
  // RtpSender.dispose(), called by PeerConnection.dispose() or getSenders().
  return Java_RtpSender_Constructor(env, jlongFromPointer(sender.release()));
}

static jboolean JNI_RtpSender_SetTrack(JNIEnv* jni,
                                       const JavaParamRef<jclass>&,
                                       jlong j_rtp_sender_pointer,
                                       jlong j_track_pointer) {
  return reinterpret_cast<RtpSenderInterface*>(j_rtp_sender_pointer)
      ->SetTrack(reinterpret_cast<MediaStreamTrackInterface*>(j_track_pointer));
}

jlong JNI_RtpSender_GetTrack(JNIEnv* jni,
                             const JavaParamRef<jclass>&,
                             jlong j_rtp_sender_pointer) {
  return jlongFromPointer(
      reinterpret_cast<RtpSenderInterface*>(j_rtp_sender_pointer)
          ->track()
          .release());
}

jlong JNI_RtpSender_GetDtmfSender(JNIEnv* jni,
                                  const JavaParamRef<jclass>&,
                                  jlong j_rtp_sender_pointer) {
  return jlongFromPointer(
      reinterpret_cast<RtpSenderInterface*>(j_rtp_sender_pointer)
          ->GetDtmfSender()
          .release());
}

jboolean JNI_RtpSender_SetParameters(
    JNIEnv* jni,
    const JavaParamRef<jclass>&,
    jlong j_rtp_sender_pointer,
    const JavaParamRef<jobject>& j_parameters) {
  if (IsNull(jni, j_parameters)) {
    return false;
  }
  RtpParameters parameters = JavaToNativeRtpParameters(jni, j_parameters);
  return reinterpret_cast<RtpSenderInterface*>(j_rtp_sender_pointer)
      ->SetParameters(parameters)
      .ok();
}

ScopedJavaLocalRef<jobject> JNI_RtpSender_GetParameters(
    JNIEnv* jni,
    const JavaParamRef<jclass>&,
    jlong j_rtp_sender_pointer) {
  RtpParameters parameters =
      reinterpret_cast<RtpSenderInterface*>(j_rtp_sender_pointer)
          ->GetParameters();
  return NativeToJavaRtpParameters(jni, parameters);
}

ScopedJavaLocalRef<jstring> JNI_RtpSender_GetId(JNIEnv* jni,
                                                const JavaParamRef<jclass>&,
                                                jlong j_rtp_sender_pointer) {
  return NativeToJavaString(
      jni, reinterpret_cast<RtpSenderInterface*>(j_rtp_sender_pointer)->id());
}

}  // namespace jni
}  // namespace webrtc
