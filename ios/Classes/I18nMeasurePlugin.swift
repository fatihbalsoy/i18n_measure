import Flutter
import UIKit

public class I18nMeasurePlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "i18n_measure", binaryMessenger: registrar.messenger())
    let instance = I18nMeasurePlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    switch call.method {
    case "getMeasurementSystem":
      if #available(iOS 16.0, *) {
        let measurementSystem = NSLocale.current.measurementSystem
        result(measurementSystem == .metric ? "metric" : "imperial")
      } else {
        let isMetric = NSLocale.current.usesMetricSystem
        result(isMetric ? "metric" : "imperial")
      }
      default:
      result(FlutterMethodNotImplemented)
    }
  }
}
