// In order to *not* need this ignore, consider extracting the "web" version
// of your plugin as a separate package, instead of inlining it in the same
// package as the core of your plugin.
// ignore: avoid_web_libraries_in_flutter
import 'dart:html' as html show window;

import 'package:flutter_web_plugins/flutter_web_plugins.dart';
import 'package:i18n_measure/i18n_measure.dart';

import 'i18n_measure_platform_interface.dart';

/// A web implementation of the I18nMeasurePlatform of the I18nMeasure plugin.
class I18nMeasureWeb extends I18nMeasurePlatform {
  /// Constructs a I18nMeasureWeb
  I18nMeasureWeb();

  static void registerWith(Registrar registrar) {
    I18nMeasurePlatform.instance = I18nMeasureWeb();
  }

  /// Returns a [String] containing the version of the platform.
  @override
  Future<MeasurementSystem?> getMeasurementSystem() async {
    const imperialCountries = ["GB", "US", "MM", "LR"];

    final language = html.window.navigator.language;
    bool isImperial = false;
    for (var code in imperialCountries) {
	isImperial = isImperial || language.contains(code);
    }
    return isImperial
        ? MeasurementSystem.imperial
        : MeasurementSystem.metric;
  }
}
