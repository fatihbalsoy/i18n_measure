//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <i18n_measure/i18n_measure_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) i18n_measure_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "I18nMeasurePlugin");
  i18n_measure_plugin_register_with_registrar(i18n_measure_registrar);
}
