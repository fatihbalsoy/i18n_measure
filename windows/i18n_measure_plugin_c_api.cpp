#include "include/i18n_measure/i18n_measure_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "i18n_measure_plugin.h"

void I18nMeasurePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  i18n_measure::I18nMeasurePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
