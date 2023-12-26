import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:i18n_measure/i18n_measure.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  MeasurementSystem? _measurementSystem;
  final _i18nMeasurePlugin = I18nMeasure();

  @override
  void initState() {
    super.initState();
    initPlatformState();
  }

  // Platform messages are asynchronous, so we initialize in an async method.
  Future<void> initPlatformState() async {
    MeasurementSystem? measurementSystem;
    // Platform messages may fail, so we use a try/catch PlatformException.
    // We also handle the message potentially returning null.
    try {
      measurementSystem =
          await _i18nMeasurePlugin.getMeasurementSystem();
    } on PlatformException {
      print('Failed to get measurement system.');
    }

    // If the widget was removed from the tree while the asynchronous platform
    // message was in flight, we want to discard the reply rather than calling
    // setState to update our non-existent appearance.
    if (!mounted) return;

    setState(() {
      _measurementSystem = measurementSystem;
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: _measurementSystem != null
              ? Text('Measurement System: ${_measurementSystem == MeasurementSystem.metric ? "Metric" : "Imperial"}')
              : const Text("ERROR"),
        ),
      ),
    );
  }
}
