import 'dynamic_library/dynamic_library_linux.dart';
import 'src/authorization_screen.dart';
import 'src/home_screen.dart';
import 'src/sign_in_screen.dart';

import 'package:flutter/material.dart';
import 'dart:io';

import 'package:window_size/window_size.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  if (Platform.isLinux) {
    setWindowMaxSize(const Size(1850, 900));
    setWindowMinSize(const Size(1850, 900));
  }
  runApp(SignInPage());
  //runApp(AuthorizationPage());
  //runApp(Home());
}
