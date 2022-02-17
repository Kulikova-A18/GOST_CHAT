
import 'dart:async';

import 'package:flutter/services.dart';

class PluginLinux {
  static const MethodChannel _channel = MethodChannel('plugin_linux');

  static Future<String?> get platformVersion async {
    final String? version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
