/*
 * Copyright (C) 2007 The Android Open Source Project
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
#pragma once

#include <sys/types.h>

#include <cstdint>

#include "Layer.h"

namespace android {

class ColorLayer : public Layer {
public:
    explicit ColorLayer(const LayerCreationArgs&);
    ~ColorLayer() override;

    virtual const char* getTypeId() const { return "ColorLayer"; }
    virtual void onDraw(const RenderArea& renderArea, const Region& clip,
                        bool useIdentityTransform);
    bool isVisible() const override;

    void setPerFrameData(DisplayId displayId, const ui::Transform& transform, const Rect& viewport,
                         int32_t supportedPerFrameMetadata) override;

    bool onPreComposition(nsecs_t /*refreshStartTime*/) override { return false; }

protected:
    FloatRect computeCrop(const Rect& /*windowbounds*/) const override { return {}; }
};

} // namespace android