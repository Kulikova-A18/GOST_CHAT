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

const String _text = 'The relevance of the topic is determined by the fact that cloud messages have become the main communication channel between two or more people. Confidential information (personal messages, bank card details, etc.) is transmitted through these channels, and commercial information can also be transferred inadvertently or purposefully. Therefore, the security and confidentiality of messages are of great importance.\n' +
    'In order to avoid trouble for the organization, a secure instant messaging system with GOST encryption will be created for its employees in a specific territory. Thus, the creation of a special instant messaging system for the organization will reduce the risk of leakage of commercial information.\n' +
    'The purpose of this work is to develop an instant messaging system with GOST encryption for employees of the organization.\n' +
    'Based on the set goal , the following tasks can be distinguished:\n' +
    '1. Get the terms of reference from the consultant;\n' +
    '2. Explore the instant messaging system;\n' +
    '3. Study GOST encryption;\n' +
    '4. Analyze the requirements for the expedient use of an instant messaging system with GOST encryption for employees of the organization;\n' +
    '5. Choose a method of software implementation of an instant messaging system with GOST encryption for employees of the organization;\n' +
    '6. Implement an instant messaging system with GOST encryption for employees of the organization.';

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

  final _TextStyle_Label = const TextStyle(
      color: Colors.black, fontSize: 40, fontFamily: 'Source_Code_Pro');

  final _TextStyle_Button = const TextStyle(
      color: Colors.white, fontSize: 30, fontFamily: 'Source_Code_Pro');

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        debugShowCheckedModeBanner: false,
        home: Scaffold(body: LayoutBuilder(builder: (context, constraints) {
          return DecoratedBox(
            decoration: const BoxDecoration(
              image: DecorationImage(
                  image: AssetImage("images/ai_image_gen_with_woombo_art.jpg"),
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
                        width: 200,
                        height: 100,
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
                            color: Colors.white.withOpacity(0.9),
                            child: Column(children: [
                              const Text("GOST CHAT",
                                  style: TextStyle(
                                      color: Color.fromARGB(255, 88, 12, 104),
                                      fontSize: 65,
                                      fontFamily: 'Source_Code_Pro')),
                              Container(
                                height: 10,
                              ),
                              Container(
                                height: 250,
                                child: AnimatedTextKit(
                                  //totalRepeatCount: 4,
                                  //pause: const Duration(milliseconds: 1000),
                                  displayFullTextOnTap: true,
                                  stopPauseOnTap: true,
                                  animatedTexts: [
                                    TyperAnimatedText(
                                      _text,
                                      speed: const Duration(milliseconds: 5),
                                      textStyle: const TextStyle(
                                          fontSize: 11,
                                          fontFamily: 'Source_Code_Pro',
                                          fontWeight: FontWeight.bold),
                                    ),
                                  ],
                                ),
                              ),
                              Container(
                                height: 10,
                              ),
                              Row(
                                children: [
                                  Container(
                                    width: 550,
                                  ),
                                  Container(
                                      height: 50,
                                      padding: const EdgeInsets.all(0.0),
                                      child: ElevatedButton(
                                          child: Text("Continue",
                                              style: _TextStyle_Button),
                                          style: ButtonStyle(
                                              backgroundColor:
                                                  MaterialStateProperty.all<
                                                          Color>(
                                                      Color.fromARGB(
                                                          255, 88, 12, 104)),
                                              shape: MaterialStateProperty.all<
                                                      RoundedRectangleBorder>(
                                                  RoundedRectangleBorder(
                                                borderRadius:
                                                    BorderRadius.circular(20.0),
                                              ))),
                                          onPressed: () {
                                            performNavigator_SignInPage();
                                          })),
                                ],
                              )
                            ]),
                          ),
                        ],
                      )),
                    ],
                  ),
                ),
              ),
            ),
          );
        })));
  }
}
