import 'package:ffi/ffi.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'dart:ffi';
import 'dart:io';
import 'dart:ffi' as ffi;

final DynamicLibrary plugin_linuxLib = Platform.isAndroid
    ? DynamicLibrary.open('libplugin_linux.so')
    : DynamicLibrary.process();

// ============ sign_in.cpp ============
final int Function(Pointer<Utf8> str1) fun_password_check_linux =
    plugin_linuxLib
        .lookup<NativeFunction<Int32 Function(ffi.Pointer<Utf8>)>>(
            "_password_check_linux")
        .asFunction();

final int Function(Pointer<Utf8> str1, Pointer<Utf8> str2) fun_sign_in_linux =
    plugin_linuxLib
        .lookup<
            NativeFunction<
                Int32 Function(
                    ffi.Pointer<Utf8>, ffi.Pointer<Utf8>)>>("_sign_in_linux")
        .asFunction();

// ============ message.cpp ============
// ---- send ----
final int Function(Pointer<Utf8> str1) fun_encrypted_message = plugin_linuxLib
    .lookup<NativeFunction<Int32 Function(ffi.Pointer<Utf8>)>>(
        "encrypted_message")
    .asFunction();
// ---- get ----
final int Function(Pointer<Utf8> str1) fun_decipher_message = plugin_linuxLib
    .lookup<NativeFunction<Int32 Function(ffi.Pointer<Utf8>)>>(
        "decipher_message")
    .asFunction();
// ---- print ----
final Pointer<Utf8> Function() fun_get_sender = plugin_linuxLib.lookupFunction<
    Pointer<Utf8> Function(), Pointer<Utf8> Function()>('get_sender');
final Pointer<Utf8> Function() fun_get_message = plugin_linuxLib.lookupFunction<
    Pointer<Utf8> Function(), Pointer<Utf8> Function()>('get_message');

// ============ user.cpp ============
final Pointer<Utf8> Function() fun_get_user = plugin_linuxLib.lookupFunction<
    Pointer<Utf8> Function(), Pointer<Utf8> Function()>('get_user');
