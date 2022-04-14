import '../dynamic_library/dynamic_library_linux.dart';
import 'widgets/ClipPath.dart';

import 'sign_in_screen.dart';

import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';
import 'dart:ui';

//flutter pub add animated_text_kit
import 'package:animated_text_kit/animated_text_kit.dart';

void main() {
  runApp(AuthorizationPage());
}

class AuthorizationPage extends StatefulWidget {
  @override
  createState() => AuthorizationPageState();
}

class AuthorizationPageState extends State<AuthorizationPage> {
  void performNavigator_SignPage() {
    runApp(
      MaterialApp(
        home: SignInPage(),
      ),
    );
  }

//child: Image.asset("images/5d3d40efed8e2.jpg", fit: BoxFit.fill),
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        body: Stack(
          children: [
            ClipPath(
                clipper: ClipPathClass_Auth(),
                child: Container(
                  height: 700,
                  width: 1400,
                  child:
                      Image.asset("images/5d3d40efed8e2.jpg", fit: BoxFit.fill),
                )),
            Align(
                alignment: FractionalOffset(0.97, 0.85),
                child: Text('ГОСТ ЧАТ'.toUpperCase(),
                    textDirection: TextDirection.ltr, // текст слева направо
                    style: const TextStyle(
                      fontSize: 200,
                      color: Colors.white,
                      fontFamily: 'Code_Auth',
                      height: 1.5,
                    ))),
            Align(
                alignment: FractionalOffset(0.1, 0.9),
                child: Container(
                    height: 90,
                    width: 450,
                    padding: const EdgeInsets.all(0.0),
                    child: ElevatedButton(
                        child: Text(
                          "начать".toUpperCase(),
                          style: const TextStyle(
                            fontSize: 70,
                            color: Colors.white,
                            fontFamily: 'Code_Auth',
                          ),
                        ),
                        style: ButtonStyle(
                            backgroundColor:
                                MaterialStateProperty.all<Color>(Colors.black),
                            shape: MaterialStateProperty.all<
                                RoundedRectangleBorder>(RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(20.0),
                            ))),
                        onPressed: () {
                          performNavigator_SignPage();
                        })))
          ],
        ),
      ),
    );
  }
}
