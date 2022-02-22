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

  final _TextStyle = const TextStyle(
      color: Colors.black, fontSize: 30, fontFamily: 'Source_Code_Pro');
  final _TextStyle_Button = const TextStyle(
      color: Colors.white, fontSize: 30, fontFamily: 'Source_Code_Pro');
  late bool _passwordVisible = false;

  @override
  void initState() {
    //printController();
    super.initState();
  }

  void performNavigator_HomePage() {
    runApp(
      MaterialApp(
        home: HomePage(),
      ),
    );
  }

  var message = "";

  void _fun_sign(var argv1, var argv2) {
    int a = fun_sign_in_linux(StringUtf8Pointer(argv1).toNativeUtf8(),
        StringUtf8Pointer(argv2).toNativeUtf8());
    switch (a) {
      case 0:
        message = "successfully";
        performNavigator_HomePage();
        break;
      case 1:
        message = "fields are empty";
        break;
      case 2:
        message = "login field is empty";
        break;
      case 3:
        message = "password field is empty";
        break;
      default:
        break;
    }
    simpleDialog(context);
  }

// simpleDialog(context);
  Future simpleDialog(BuildContext context) {
    return showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          //title: Text('Title'),
          content: Text(message),
          actions: <Widget>[
            FlatButton(
              child: Text('Ok'),
              onPressed: () {
                Navigator.of(context).pop();
              },
            ),
          ],
        );
      },
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
                        height: 50,
                      ),
                      SizedBox(
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Container(
                              padding: const EdgeInsets.symmetric(
                                  vertical: 30.0, horizontal: 25.0),
                              width: 400,
                              height: 500,
                              color: Colors.white.withOpacity(0.9),
                              child: Column(
                                mainAxisAlignment: MainAxisAlignment.center,
                                children: [
                                  Text("Sign in to \nGOST CHAT",
                                      style: const TextStyle(
                                          color:
                                              Color.fromARGB(255, 88, 12, 104),
                                          fontSize: 35,
                                          fontFamily: 'Source_Code_Pro')),
                                  const SizedBox(
                                    height: 40,
                                  ),
                                  Text(
                                    "Login",
                                    style: _TextStyle,
                                  ),
                                  Container(
                                    width: 350,
                                    height: 60,
                                    decoration: BoxDecoration(
                                      border: Border.all(
                                        color: Colors.black,
                                        width: 5,
                                      ),
                                    ),
                                    child: Column(
                                      children: [
                                        Container(
                                          child: TextFormField(
                                            autofocus: true,
                                            style: _TextStyle,
                                            controller: _loginController,
                                            decoration: const InputDecoration(
                                              border: InputBorder.none,
                                            ),
                                          ),
                                          height: 50,
                                          width: 300.0,
                                          padding:
                                              const EdgeInsets.only(top: 10.0),
                                        ),
                                      ],
                                    ),
                                  ),
                                  const SizedBox(
                                    height: 20,
                                  ),
                                  Text(
                                    "Password",
                                    style: _TextStyle,
                                  ),
                                  Container(
                                    width: 350,
                                    height: 70,
                                    decoration: BoxDecoration(
                                      border: Border.all(
                                        color: Colors.black,
                                        width: 5,
                                      ),
                                    ),
                                    child: Column(
                                      children: [
                                        Container(
                                          child: TextFormField(
                                            autofocus: true,
                                            style: _TextStyle,
                                            controller: _passwordController,
                                            obscureText: !_passwordVisible,
                                            decoration: InputDecoration(
                                              border: InputBorder.none,
                                              suffixIcon: IconButton(
                                                icon: Icon(
                                                  _passwordVisible
                                                      ? Icons.mood_bad
                                                      : Icons.mood,
                                                  color: Colors.black,
                                                  size: 25,
                                                ),
                                                onPressed: () {
                                                  // Update the state i.e. toogle the state of passwordVisible variable
                                                  setState(() {
                                                    _passwordVisible =
                                                        !_passwordVisible;
                                                  });
                                                },
                                              ),
                                            ),
                                          ),
                                          height: 55,
                                          width: 300,
                                          padding:
                                              const EdgeInsets.only(top: 10.0),
                                        ),
                                      ],
                                    ),
                                  ),
                                  const SizedBox(
                                    height: 20,
                                  ),
                                  Container(
                                      height: 50,
                                      padding: const EdgeInsets.all(0.0),
                                      child: ElevatedButton(
                                          child: Text("Sign in".toUpperCase(),
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
                                            _fun_sign(_loginController.text,
                                                _passwordController.text);
                                          }))
                                ],
                              ),
                            ),
                          ],
                        ),
                      ),
                      Container(
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
