import 'dynamic_library/dynamic_library_linux.dart';
import 'src/authorization_screen.dart';
import 'src/home_screen.dart';
import 'package:flutter/material.dart';
import 'dart:io';

/* 
$ flutter pub add window_size 
$ flutter pub get
*/
import 'package:window_size/window_size.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  if (Platform.isLinux) {
    setWindowMaxSize(const Size(1024, 768));
    setWindowMinSize(const Size(1024, 768));
  }
  //runApp(AuthorizationPage());
  runApp(HomePage());
}
