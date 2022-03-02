import '../../dynamic_library/dynamic_library_linux.dart';

import 'package:ffi/ffi.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

String getUsername() {
  final ptr = fun_print_user_linux();
  final result = ptr.toDartString();
  calloc.free(ptr);
  return result;
}

Widget buildContent() {
  return Container(
      //color: Color.fromARGB(255, 255, 81, 0),
      alignment: Alignment.center,
      padding: EdgeInsets.all(10),
      child: Column(
        children: [
          CircleAvatar(
            radius: 50.0,
            backgroundImage: AssetImage("images/sfu.png"),
            backgroundColor: Colors.transparent,
          ),
          Text(getUsername(),
              style: TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Colors.black87,
                  fontSize: 25)),
        ],
      ));
}
