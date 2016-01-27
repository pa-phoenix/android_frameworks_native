/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <binder/IMediaResourceMonitor.h>
#include <binder/Parcel.h>
#include <utils/Errors.h>
#include <sys/types.h>

namespace android {

// ----------------------------------------------------------------------

class BpMediaResourceMonitor : public BpInterface<IMediaResourceMonitor> {
public:
    BpMediaResourceMonitor(const sp<IBinder>& impl)
        : BpInterface<IMediaResourceMonitor>(impl) {}

    virtual void notifyResourceGranted(/*in*/ int32_t pid, /*in*/ const String16& type,
            /*in*/ const String16& subType, /*in*/ int64_t value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IMediaResourceMonitor::getInterfaceDescriptor());
        data.writeInt32(pid);
        data.writeString16(type);
        data.writeString16(subType);
        data.writeInt64(value);
        remote()->transact(NOTIFY_RESOURCE_GRANTED, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(MediaResourceMonitor, "android.media.IMediaResourceMonitor");

// ----------------------------------------------------------------------

status_t BnMediaResourceMonitor::onTransact( uint32_t code, const Parcel& data, Parcel* reply,
        uint32_t flags) {
    switch(code) {
        case NOTIFY_RESOURCE_GRANTED: {
            CHECK_INTERFACE(IMediaResourceMonitor, data, reply);
            int32_t pid = data.readInt32();
            const String16 type = data.readString16();
            const String16 subType = data.readString16();
            int64_t value = data.readInt64();
            notifyResourceGranted(/*in*/ pid, /*in*/ type, /*in*/ subType, /*in*/ value);
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

// ----------------------------------------------------------------------

}; // namespace android