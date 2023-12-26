#ifndef FLUTTER_PLUGIN_I18N_MEASURE_PLUGIN_H_
#define FLUTTER_PLUGIN_I18N_MEASURE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace i18n_measure {

class I18nMeasurePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  I18nMeasurePlugin();

  virtual ~I18nMeasurePlugin();

  // Disallow copy and assign.
  I18nMeasurePlugin(const I18nMeasurePlugin&) = delete;
  I18nMeasurePlugin& operator=(const I18nMeasurePlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace i18n_measure

#endif  // FLUTTER_PLUGIN_I18N_MEASURE_PLUGIN_H_
