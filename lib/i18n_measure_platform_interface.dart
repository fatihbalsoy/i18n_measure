import 'package:i18n_measure/i18n_measure.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'i18n_measure_method_channel.dart';

abstract class I18nMeasurePlatform extends PlatformInterface {
  /// Constructs a I18nMeasurePlatform.
  I18nMeasurePlatform() : super(token: _token);

  static final Object _token = Object();

  static I18nMeasurePlatform _instance = MethodChannelI18nMeasure();

  /// The default instance of [I18nMeasurePlatform] to use.
  ///
  /// Defaults to [MethodChannelI18nMeasure].
  static I18nMeasurePlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [I18nMeasurePlatform] when
  /// they register themselves.
  static set instance(I18nMeasurePlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<MeasurementSystem?> getMeasurementSystem() {
    throw UnimplementedError('measurementSystem() has not been implemented.');
  }
}
