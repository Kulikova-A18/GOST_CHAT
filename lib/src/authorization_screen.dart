import '../dynamic_library/dynamic_library_linux.dart';

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
  @override
  void initState() {
    super.initState();
  }

  void performNavigator_SignInPage() {
    runApp(
      MaterialApp(
        home: SignInPage(),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        debugShowCheckedModeBanner: false,
        home: Scaffold(body: LayoutBuilder(builder: (context, constraints) {
          return DecoratedBox(
            decoration: const BoxDecoration(
              image: DecorationImage(
                  image: AssetImage("images/oranzhevyy_fon.jpg"),
                  fit: BoxFit.cover),
            ),
            child: Center(
              child: BackdropFilter(
                filter: ImageFilter.blur(sigmaX: 1.0, sigmaY: 1.0),
                child: Container(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Container(
                        width: 300,
                        height: 50,
                      ),
                      SizedBox(
                          child: Column(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Container(
                            padding: const EdgeInsets.symmetric(
                                vertical: 30.0, horizontal: 25.0),
                            width: 900,
                            height: 450,
                            //color: Colors.white.withOpacity(0.9),
                            child: Column(children: [
                              Container(
                                width: 800,
                                height: 380,
                                child: Column(children: [
                                  ElevatedButton(
                                      child: Image.asset(
                                        "images/logo.gif",
                                        width: 900,
                                        height: 380,
                                      ),
                                      style: ElevatedButton.styleFrom(
                                        primary: Colors.white,
                                      ),
                                      onPressed: () {
                                        performNavigator_SignInPage();
                                      })
                                ]),
                              ),
                            ]),
                          ),
                        ],
                      )),
                      Container(
                        width: 300,
                        height: 50,
                      ),
                    ],
                  ),
                ),
              ),
            ),
          );
        })));
  }
}
