package fatih.bal.soy.i18n_measure

import java.util.Locale
import androidx.annotation.NonNull

import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result

enum class UnitSystem {
  METRIC,
  IMPERIAL,
  IMPERIAL_US
}

fun Locale.toUnitSystem(): UnitSystem {
  return when (country.toUpperCase()) {
    // https://en.wikipedia.org/wiki/United_States_customary_units
    // https://en.wikipedia.org/wiki/Imperial_units
    "US" -> UnitSystem.IMPERIAL_US
    // UK, Myanmar, Liberia,
    "GB", "MM", "LR" -> UnitSystem.IMPERIAL
    else -> UnitSystem.METRIC
  }
}

/** I18nMeasurePlugin */
class I18nMeasurePlugin: FlutterPlugin, MethodCallHandler {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private lateinit var channel : MethodChannel

  override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "i18n_measure")
    channel.setMethodCallHandler(this)
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    if (call.method == "getMeasurementSystem") {
      val locale = Locale.getDefault()
      val system: UnitSystem = locale.toUnitSystem()
      result.success(if (system == UnitSystem.METRIC) "metric" else "imperial")
    } else {
      result.notImplemented()
    }
  }

  override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }
}
