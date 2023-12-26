#include "include/i18n_measure/i18n_measure_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>
#include <stdlib.h>
#include <locale.h>

#include "i18n_measure_plugin_private.h"

#define I18N_MEASURE_PLUGIN(obj)                                     \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), i18n_measure_plugin_get_type(), \
                              I18nMeasurePlugin))

struct _I18nMeasurePlugin
{
  GObject parent_instance;
};

G_DEFINE_TYPE(I18nMeasurePlugin, i18n_measure_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void i18n_measure_plugin_handle_method_call(
    I18nMeasurePlugin *self,
    FlMethodCall *method_call)
{
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar *method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getMeasurementSystem") == 0)
  {
    response = get_measurement_system();
  }
  else
  {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

FlMethodResponse *get_measurement_system()
{
  setlocale(LC_ALL, "");
  char *locale = setlocale(LC_ALL, NULL);
  char countryCode[3];
  countryCode[0] = locale[3];
  countryCode[1] = locale[4];
  countryCode[2] = '\0';

  const char *imperialCountries[] = {"GB", "US", "MM", "LR"};
  size_t numImperialCountries = sizeof(imperialCountries) / sizeof(imperialCountries[0]);
  g_autofree gchar *unit_system = NULL;
  for (size_t i = 0; i < numImperialCountries; ++i)
  {
    if (strcmp(countryCode, imperialCountries[i]) == 0)
    {
      unit_system = g_strdup_printf("imperial");
    }
  }
  if (unit_system == NULL)
  {
    unit_system = g_strdup_printf("metric");
  }
  g_autoptr(FlValue) result = fl_value_new_string(unit_system);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

static void i18n_measure_plugin_dispose(GObject *object)
{
  G_OBJECT_CLASS(i18n_measure_plugin_parent_class)->dispose(object);
}

static void i18n_measure_plugin_class_init(I18nMeasurePluginClass *klass)
{
  G_OBJECT_CLASS(klass)->dispose = i18n_measure_plugin_dispose;
}

static void i18n_measure_plugin_init(I18nMeasurePlugin *self) {}

static void method_call_cb(FlMethodChannel *channel, FlMethodCall *method_call,
                           gpointer user_data)
{
  I18nMeasurePlugin *plugin = I18N_MEASURE_PLUGIN(user_data);
  i18n_measure_plugin_handle_method_call(plugin, method_call);
}

void i18n_measure_plugin_register_with_registrar(FlPluginRegistrar *registrar)
{
  I18nMeasurePlugin *plugin = I18N_MEASURE_PLUGIN(
      g_object_new(i18n_measure_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "i18n_measure",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
