// Copyright (c) 2017 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_API_ATOM_API_BROWSER_VIEW_H_
#define SHELL_BROWSER_API_ATOM_API_BROWSER_VIEW_H_

#include <memory>
#include <string>

#include "content/public/browser/web_contents_observer.h"
#include "native_mate/handle.h"
#include "shell/browser/api/trackable_object.h"
#include "shell/browser/native_browser_view.h"

namespace gfx {
class Rect;
}

namespace mate {
class Arguments;
class Dictionary;
}  // namespace mate

namespace electron {

class NativeBrowserView;

namespace api {

class WebContents;

class BrowserView : public mate::TrackableObject<BrowserView>,
                    public content::WebContentsObserver {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  WebContents* web_contents() const { return api_web_contents_; }
  NativeBrowserView* view() const { return view_.get(); }

  int32_t ID() const;

 protected:
  BrowserView(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              const mate::Dictionary& options);
  ~BrowserView() override;

  // content::WebContentsObserver:
  void WebContentsDestroyed() override;

 private:
  void Init(v8::Isolate* isolate,
            v8::Local<v8::Object> wrapper,
            const mate::Dictionary& options);

  void SetAutoResize(AutoResizeFlags flags);
  void SetBounds(const gfx::Rect& bounds);
  void SetBackgroundColor(const std::string& color_name);

  v8::Local<v8::Value> GetWebContents();

  v8::Global<v8::Value> web_contents_;
  class WebContents* api_web_contents_ = nullptr;

  std::unique_ptr<NativeBrowserView> view_;

  DISALLOW_COPY_AND_ASSIGN(BrowserView);
};

}  // namespace api

}  // namespace electron

#endif  // SHELL_BROWSER_API_ATOM_API_BROWSER_VIEW_H_
