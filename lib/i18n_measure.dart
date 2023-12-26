import 'i18n_measure_platform_interface.dart';

enum MeasurementSystem { metric, imperial }

class I18nMeasure {
  Future<MeasurementSystem?> getMeasurementSystem() {
    return I18nMeasurePlatform.instance.getMeasurementSystem();
  }
}
