import 'package:ffi/ffi.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'dart:ffi';
import 'dart:io';
import 'dart:ffi' as ffi;

typedef _Func = ffi.Pointer<Utf8> Function();

final DynamicLibrary plugin_linuxLib = Platform.isAndroid
    ? DynamicLibrary.open('libplugin_linux.so')
    : DynamicLibrary.process();

final int Function(Pointer<Utf8> str) fun_check = plugin_linuxLib
    .lookup<NativeFunction<Int32 Function(ffi.Pointer<Utf8>)>>("_check")
    .asFunction();

final int Function(int x, int y) nativeAdd = plugin_linuxLib
    .lookup<NativeFunction<Int32 Function(Int32, Int32)>>('native_add')
    .asFunction();
