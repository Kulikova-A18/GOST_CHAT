import '../dynamic_library/dynamic_library_linux.dart';

import 'home_screen.dart';

import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';
import 'dart:ui';

void main() {
  runApp(SignInPage());
}

class SignInPage extends StatefulWidget {
  @override
  createState() => SignInPageState();
}

class SignInPageState extends State<SignInPage> {
  final TextEditingController _loginController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();

  @override
  void initState() {
    super.initState();
    _loginController.text = "kulikova@gost_chat.com";
    _passwordController.text = "c0WpF6iK";
  }

  late bool _passwordVisible = false;

  void performNavigator_HomePage() {
    runApp(
      MaterialApp(
        home: Home(),
      ),
    );
  }

  void _fun_sign(var argv1, var argv2) {
    fun_sign_in_linux(StringUtf8Pointer(argv1).toNativeUtf8(),
        StringUtf8Pointer(argv2).toNativeUtf8());
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        body: Stack(
          children: [
            Container(
              width: 1400,
              height: 900,
              color: Colors.white,
            ),
            Align(
                alignment: const FractionalOffset(0.0, 0.3),
                child: Container(
                  height: 1400,
                  width: 1400,
                  color: Colors.white,
                )),
            Align(
                alignment: const FractionalOffset(0.5, 0.7),
                child: Container(
                  padding: const EdgeInsets.symmetric(
                      vertical: 30.0, horizontal: 25.0),
                  width: 650,
                  height: 600,
                  color: Colors.white,
                  child: Column(children: [
                    Text("Добро пожаловать \n       в ГОСТ ЧАТ".toUpperCase(),
                        style: TextStyle(
                            color: Colors.black,
                            fontSize: 60,
                            fontFamily: 'Code_Auth')),
                    const SizedBox(height: 30),
                    Container(
                      width: 450,
                      height: 80,
                      decoration: BoxDecoration(
                        border: Border.all(
                          color: Colors.black,
                          width: 1,
                        ),
                        borderRadius: BorderRadius.all(Radius.circular(30.0)),
                      ),
                      child: Column(
                        children: [
                          Container(
                            color: Colors.white,
                            child: TextFormField(
                              autofocus: true,
                              controller: _loginController,
                              decoration: const InputDecoration(
                                hintText: "логин",
                                border: InputBorder.none,
                              ),
                            ),
                            height: 50,
                            width: 400,
                            padding: const EdgeInsets.only(top: 20.0),
                          ),
                        ],
                      ),
                    ),
                    const SizedBox(
                      height: 10,
                    ),
                    Container(
                      width: 450,
                      height: 80,
                      decoration: BoxDecoration(
                        border: Border.all(
                          color: Colors.black,
                          width: 1,
                        ),
                        borderRadius: BorderRadius.all(Radius.circular(30.0)),
                      ),
                      child: Column(
                        children: [
                          Container(
                            child: TextFormField(
                              autofocus: true,
                              controller: _passwordController,
                              obscureText: !_passwordVisible,
                              decoration: InputDecoration(
                                hintText: "пароль",
                                border: InputBorder.none,
                                suffixIcon: IconButton(
                                  icon: Icon(
                                    _passwordVisible
                                        ? Icons.lock_open
                                        : Icons.lock_outline,
                                    color: Colors.black,
                                    size: 25,
                                  ),
                                  onPressed: () {
                                    // Update the state i.e. toogle the state of passwordVisible variable
                                    setState(() {
                                      _passwordVisible = !_passwordVisible;
                                    });
                                  },
                                ),
                              ),
                            ),
                            height: 55,
                            width: 400,
                            padding: const EdgeInsets.only(top: 20.0),
                          ),
                        ],
                      ),
                    ),
                    const SizedBox(
                      height: 20,
                    ),
                    Container(
                        height: 50,
                        width: 250,
                        padding: const EdgeInsets.all(0.0),
                        child: ElevatedButton(
                            child: Text(
                              "Войти".toUpperCase(),
                              style: const TextStyle(
                                fontSize: 50,
                                color: Colors.white,
                                fontFamily: 'Code_Auth',
                              ),
                            ),
                            style: ButtonStyle(
                                backgroundColor:
                                    MaterialStateProperty.all<Color>(
                                        Color.fromARGB(255, 255, 81, 0)),
                                shape: MaterialStateProperty.all<
                                        RoundedRectangleBorder>(
                                    RoundedRectangleBorder(
                                  borderRadius: BorderRadius.circular(20.0),
                                ))),
                            onPressed: () {
                              _fun_sign(_loginController.text,
                                  _passwordController.text);
                              //performNavigator_HomePage();
                            }))
                  ]),
                )),
          ],
        ),
      ),
    );
  }
}
