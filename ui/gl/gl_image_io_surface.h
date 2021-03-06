// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_IMAGE_IO_SURFACE_H_
#define UI_GL_GL_IMAGE_IO_SURFACE_H_

#include <IOSurface/IOSurfaceAPI.h>

#include "base/mac/scoped_cftyperef.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gl/gl_image.h"

namespace gfx {

class GL_EXPORT GLImageIOSurface : public GLImage {
 public:
  explicit GLImageIOSurface(const gfx::Size& size);

  bool Initialize(IOSurfaceRef io_surface);

  // Overridden from GLImage:
  virtual void Destroy(bool have_context) OVERRIDE;
  virtual gfx::Size GetSize() OVERRIDE;
  virtual bool BindTexImage(unsigned target) OVERRIDE;
  virtual void ReleaseTexImage(unsigned target) OVERRIDE {}
  virtual bool CopyTexImage(unsigned target) OVERRIDE;
  virtual void WillUseTexImage() OVERRIDE {}
  virtual void DidUseTexImage() OVERRIDE {}
  virtual void WillModifyTexImage() OVERRIDE {}
  virtual void DidModifyTexImage() OVERRIDE {}
  virtual bool ScheduleOverlayPlane(gfx::AcceleratedWidget widget,
                                    int z_order,
                                    OverlayTransform transform,
                                    const Rect& bounds_rect,
                                    const RectF& crop_rect) OVERRIDE;

 protected:
  virtual ~GLImageIOSurface();

 private:
  base::ScopedCFTypeRef<IOSurfaceRef> io_surface_;
  const gfx::Size size_;

  DISALLOW_COPY_AND_ASSIGN(GLImageIOSurface);
};

}  // namespace gfx

#endif  // UI_GL_GL_IMAGE_IO_SURFACE_H_
