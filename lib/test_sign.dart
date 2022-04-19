import '../dynamic_library/dynamic_library_linux.dart';

//import 'home_screen.dart';

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
      color: Colors.black, fontSize: 15, fontFamily: 'Source_Code_Pro');
  final _TextStyle_Button = const TextStyle(
      color: Colors.white, fontSize: 15, fontFamily: 'Source_Code_Pro');
  late bool _passwordVisible = false;

  @override
  void initState() {
    //printController();
    super.initState();
  }

  void performNavigator_HomePage() {
    runApp(
      MaterialApp(
          ////home: Home()),
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
        message = "unsuccessful";
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
          content: Text(
            message,
            style: _TextStyle,
          ),
          actions: <Widget>[
            FlatButton(
              child: Text(
                'Ok',
                style: _TextStyle,
              ),
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
                  image: AssetImage("images/oranzhevyy_fon_2.jpg"),
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
                              width: 600,
                              height: 550,
                              color: Colors.white.withOpacity(0.9),
                              child: Column(
                                mainAxisAlignment: MainAxisAlignment.center,
                                children: [
                                  Image.asset(
                                    "images/sfu.png",
                                    //width: 900,
                                    height: 180,
                                  ),
                                  Text("Sign in",
                                      style: const TextStyle(
                                          color: Colors.black,
                                          fontSize: 35,
                                          fontFamily: 'Source_Code_Pro')),
                                  SizedBox(
                                    height: 30,
                                  ),
                                  /*Text(
                                    "Login",
                                    style: _TextStyle,
                                  ),*/
                                  Container(
                                    width: 450,
                                    height: 70,
                                    decoration: BoxDecoration(
                                      border: Border.all(
                                        color: Colors.black,
                                        width: 1,
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
                                              hintText: "Login",
                                              border: InputBorder.none,
                                            ),
                                          ),
                                          height: 50,
                                          width: 400,
                                          padding:
                                              const EdgeInsets.only(top: 10.0),
                                        ),
                                      ],
                                    ),
                                  ),
                                  const SizedBox(
                                    height: 10,
                                  ),
                                  /*Text(
                                    "Password",
                                    style: _TextStyle,
                                  ),*/
                                  Container(
                                    width: 450,
                                    height: 70,
                                    decoration: BoxDecoration(
                                      border: Border.all(
                                        color: Colors.black,
                                        width: 1,
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
                                              hintText: "Password",
                                              border: InputBorder.none,
                                              suffixIcon: IconButton(
                                                icon: Icon(
                                                  _passwordVisible
                                                      ? Icons.mood_bad
                                                      : Icons.mood,
                                                  color: Colors.black,
                                                  size: 35,
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
                                          width: 400,
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
                                                          255, 255, 81, 0)),
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
