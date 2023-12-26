import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:i18n_measure/i18n_measure.dart';

import 'i18n_measure_platform_interface.dart';

/// An implementation of [I18nMeasurePlatform] that uses method channels.
class MethodChannelI18nMeasure extends I18nMeasurePlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('i18n_measure');

  @override
  Future<MeasurementSystem?> getMeasurementSystem() async {
    final measurementSystem =
        await methodChannel.invokeMethod<String>('getMeasurementSystem');
    return measurementSystem == null
        ? null
        : measurementSystem == "imperial"
            ? MeasurementSystem.imperial
            : MeasurementSystem.metric;
  }
}
