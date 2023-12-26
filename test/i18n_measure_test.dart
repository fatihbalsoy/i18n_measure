// import 'package:flutter_test/flutter_test.dart';
// import 'package:i18n_measure/i18n_measure.dart';
// import 'package:i18n_measure/i18n_measure_platform_interface.dart';
// import 'package:i18n_measure/i18n_measure_method_channel.dart';
// import 'package:plugin_platform_interface/plugin_platform_interface.dart';

// class MockI18nMeasurePlatform
//     with MockPlatformInterfaceMixin
//     implements I18nMeasurePlatform {

//   @override
//   Future<String?> getPlatformVersion() => Future.value('42');
// }

// void main() {
//   final I18nMeasurePlatform initialPlatform = I18nMeasurePlatform.instance;

//   test('$MethodChannelI18nMeasure is the default instance', () {
//     expect(initialPlatform, isInstanceOf<MethodChannelI18nMeasure>());
//   });

//   test('getPlatformVersion', () async {
//     I18nMeasure i18nMeasurePlugin = I18nMeasure();
//     MockI18nMeasurePlatform fakePlatform = MockI18nMeasurePlatform();
//     I18nMeasurePlatform.instance = fakePlatform;

//     expect(await i18nMeasurePlugin.getPlatformVersion(), '42');
//   });
// }
