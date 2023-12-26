#include "i18n_measure_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

// Enum representing measurement systems
enum class UnitSystem
{
  METRIC,
  IMPERIAL,
  IMPERIAL_US,
  UNKNOWN
};

// Function to get measurement system based on country code
UnitSystem getUnitSystem(const std::wstring &countryCode)
{
  // Mapping country codes to measurement systems
  std::map<std::wstring, UnitSystem> countryToUnitSystem = {
      {L"US", UnitSystem::IMPERIAL_US},
      {L"GB", UnitSystem::IMPERIAL},
      {L"MM", UnitSystem::IMPERIAL},
      {L"LR", UnitSystem::IMPERIAL},
      // Add more country codes and corresponding measurement systems as needed
  };

  // Look up the country code in the mapping
  auto it = countryToUnitSystem.find(countryCode);
  if (it != countryToUnitSystem.end())
  {
    return it->second; // Return the corresponding measurement system
  }

  return UnitSystem::METRIC; // Default to metric if country code not found
}

namespace i18n_measure
{

  // static
  void I18nMeasurePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarWindows *registrar)
  {
    auto channel =
        std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(), "i18n_measure",
            &flutter::StandardMethodCodec::GetInstance());

    auto plugin = std::make_unique<I18nMeasurePlugin>();

    channel->SetMethodCallHandler(
        [plugin_pointer = plugin.get()](const auto &call, auto result)
        {
          plugin_pointer->HandleMethodCall(call, std::move(result));
        });

    registrar->AddPlugin(std::move(plugin));
  }

  I18nMeasurePlugin::I18nMeasurePlugin() {}

  I18nMeasurePlugin::~I18nMeasurePlugin() {}

  void I18nMeasurePlugin::HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
  {
    if (method_call.method_name().compare("getMeasurementSystem") == 0)
    {
      // Get the user's default locale
      wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
      if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) > 0)
      {
        // Extract the country code from the locale name
        std::wstring userCountryCode(localeName + 3, 2);

        // Determine the measurement system based on the user's country code
        UnitSystem system = getUnitSystem(userCountryCode);
        if (system == UnitSystem::IMPERIAL || system == UnitSystem::IMPERIAL_US)
        {
          // std::wcout << L"The user's preferred measurement system is Imperial.\n";
          result->Success(flutter::EncodableValue("imperial"));
        }
        else if (system == UnitSystem::METRIC)
        {
          // std::wcout << L"The user's preferred measurement system is Metric (SI).\n";
          result->Success(flutter::EncodableValue("metric"));
        }
        else
        {
          // std::wcout << L"Unknown measurement system.\n";
        }
      }
      else
      {
        // std::wcerr << L"Failed to retrieve the user's default locale name.\n";
      }
    }
    else
    {
      result->NotImplemented();
    }
  }

} // namespace i18n_measure
