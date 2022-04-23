import 'package:ffi/ffi.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'dart:ffi';
import 'dart:io';
import 'dart:ffi' as ffi;

final DynamicLibrary plugin_linuxLib = Platform.isAndroid
    ? DynamicLibrary.open('libplugin_linux.so')
    : DynamicLibrary.process();

final int Function(Pointer<Utf8> str) fun_check = plugin_linuxLib
    .lookup<NativeFunction<Int32 Function(ffi.Pointer<Utf8>)>>("_check")
    .asFunction();

final int Function(Pointer<Utf8> str1, Pointer<Utf8> str2) fun_sign_in_linux =
    plugin_linuxLib
        .lookup<
            NativeFunction<
                Int32 Function(
                    ffi.Pointer<Utf8>, ffi.Pointer<Utf8>)>>("_sign_in_linux")
        .asFunction();

final Pointer<Utf8> Function() fun_print_user_linux = plugin_linuxLib
    .lookupFunction<Pointer<Utf8> Function(), Pointer<Utf8> Function()>(
        '_print_user_linux');
