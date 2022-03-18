import 'dart:math';

import '../dynamic_library/dynamic_library_linux.dart';
import "authorization_screen.dart";

import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';
import 'dart:ui';
import 'dart:async';
import 'dart:io';
import 'dart:convert';

import 'package:path/path.dart';
import 'package:shared_preferences/shared_preferences.dart';

import 'package:flutter/cupertino.dart';

// !!!!!
import 'widgets/about.dart';

void main() {
  runApp(HomePage());
}

class HomePage extends StatefulWidget {
  @override
  createState() => HomePageState();
}

class HomePageState extends State<HomePage> {
  final _TextStyle = const TextStyle(
    color: Colors.black,
    fontSize: 18,
    fontFamily: 'Source_Code_Pro',
    height: 1.5,
  );

  late bool _passwordVisible = false;

  List<String> litems = [];
  ScrollController _scrollController = ScrollController();

  var nameUser = "";

  void performNavigator_AuthorizationPage() {
    runApp(
      MaterialApp(
        home: AuthorizationPage(),
      ),
    );
  }

  @override
  void initState() {
    _RawDatagramSocket();
    super.initState();
  }

  final List<IconData> iconData = <IconData>[
    Icons.airplanemode_active,
    Icons.beach_access,
    Icons.directions_run,
    Icons.public,
    Icons.insert_emoticon,
    Icons.directions_car,
    Icons.brightness_5,
    Icons.pets
  ];
  final Random r = Random();
  Icon randomIcon2() => Icon(iconData[r.nextInt(iconData.length)]);

  late SharedPreferences prefs;
  fun_file_write(var _text) async {
    prefs = await SharedPreferences.getInstance();
    prefs.setString('fname', _text);

    fun_file_read();
  }

  fun_file_read() async {
    prefs = await SharedPreferences.getInstance();
    setState(() {
      var a = prefs.getString('fname');
      print("received ${prefs.getString('fname')}");
      nameUser = "alexey";
      litems.add(a!);
    });
  }

  // ----------- udp -----------
  TextEditingController _messageController = TextEditingController();

  var DESTINATION_ADDRESS = InternetAddress("255.255.255.255");

  void _RawDatagramSocket() {
    RawDatagramSocket.bind(InternetAddress.anyIPv4, 55555)
        .then((RawDatagramSocket udpSocket) {
      udpSocket.broadcastEnabled = true;
      udpSocket.listen((e) {
        Datagram? dg = udpSocket.receive();
        if (dg != null) {
          fun_file_write(String.fromCharCodes(dg.data));
          //print("received ${String.fromCharCodes(dg.data)}");
          //setState(() => litems.add(String.fromCharCodes(dg.data)));
        }
      });
    });
  }

// simpleDialog(context);
  Future simpleDialog(BuildContext context) {
    return showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          //title: Text('Title'),
          content: Text("fun_alert"),
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

  final controller = ScrollController();

  List<String> peopleName = [
    "Kulikova Alyona",
    "Maximov Oleg",
    "Konovalov Grigory",
    "Kiseleva Amelia",
    "Voronin Konstantin",
    "Kasatkina Amelia",
    "Homeland Matvey",
    "Glebov Oleg",
    "Grigoriev Oleg",
    "Pavlov Matvey",
    "Antipova Grigory",
    "Ilina Daria",
    "Klimov Sergey",
    "Kulikov Nikita",
    "Ilkina Grigory",
    "Markov Sergey",
    "Popova Daria",
    "Sidorov Dmitry",
    "Siporov Grigory",
    "Bogdanova Amelia",
  ];

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        debugShowCheckedModeBanner: false,
        home: Scaffold(
            appBar: AppBar(
              elevation: 0.0,
              backgroundColor: Color.fromARGB(255, 255, 81, 0),
              title: const Text('GOST CHAR'),
              actions: <Widget>[
                IconButton(
                  icon: Icon(Icons.keyboard_return),
                  onPressed: () {
                    performNavigator_AuthorizationPage();
                  },
                ),
                IconButton(
                  icon: Icon(Icons.exit_to_app),
                  onPressed: () {},
                ),
              ],
            ),
            body: LayoutBuilder(builder: (context, constraints) {
              return Container(
                color: Colors.white.withOpacity(0.9),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    SizedBox(
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Container(
                            width: 660,
                            height: 540,
                            color: Colors.red.withOpacity(0.9),
                            child: Expanded(
                                child: ListView.builder(
                                    itemCount: litems.length,
                                    itemExtent: 120.0,
                                    itemBuilder:
                                        (BuildContext ctxt, int Index) {
                                      return Row(
                                        mainAxisAlignment:
                                            MainAxisAlignment.start,
                                        mainAxisSize: MainAxisSize.min,
                                        children: <Widget>[
                                          Container(width: 10),
                                          Column(
                                            children: [
                                              const SizedBox(
                                                height: 30.0,
                                              ),
                                              const Icon(
                                                Icons.people,
                                                color: Colors.black,
                                                size: 50.0,
                                              ),
                                              Text(nameUser, style: _TextStyle),
                                            ],
                                          ),
                                          const SizedBox(
                                            width: 10.0,
                                          ),
                                          Container(
                                              margin: const EdgeInsets.all(10),
                                              decoration: BoxDecoration(
                                                border: Border.all(
                                                    width: 2,
                                                    color: Colors.black),
                                                //color: Colors.grey,
                                              ),
                                              width: 560,
                                              child: Column(
                                                crossAxisAlignment:
                                                    CrossAxisAlignment.start,
                                                children: [
                                                  Container(
                                                    height: 2,
                                                  ),
                                                  Flexible(
                                                    child: Text(litems[Index],
                                                        style: _TextStyle),
                                                  ),
                                                ],
                                              ))
                                        ],
                                      );
                                    })),
                          ),
                          Column(
                            children: [
                              buildContent(),
                              Container(
                                  width: 260,
                                  height: 400,
                                  child: Expanded(
                                    child: ListView.builder(
                                      controller: controller,
                                      itemBuilder: (context, index) {
                                        return Container(
                                            //padding: EdgeInsets.symmetric(
                                            //vertical: 10),
                                            child: Column(
                                          crossAxisAlignment:
                                              CrossAxisAlignment.start,
                                          children: [
                                            ListTile(
                                              leading: FittedBox(
                                                fit: BoxFit.fill,
                                                child: Row(
                                                  children: <Widget>[
                                                    Icon(
                                                      Icons.people,
                                                    ),
                                                  ],
                                                ),
                                              ),
                                              title: Text(peopleName[index],
                                                  style: _TextStyle),
                                            ),
                                          ],
                                        ));
                                      },
                                      itemCount: peopleName.length,
                                    ),
                                  )),
                            ],
                          ),
                        ],
                      ),
                    ),
                    Container(
                        color:
                            Color.fromARGB(255, 219, 219, 219).withOpacity(0.9),
                        width: 1000.0,
                        child: Row(
                          children: [
                            Container(width: 100),
                            Container(
                              width: 750,
                              height: 60,
                              decoration: BoxDecoration(
                                border: Border.all(
                                  color: Colors.black,
                                  width: 2,
                                ),
                              ),
                              child: Column(
                                children: [
                                  Container(
                                    child: TextFormField(
                                      autofocus: true,
                                      style: _TextStyle,
                                      controller: _messageController,
                                      decoration: const InputDecoration(
                                        border: InputBorder.none,
                                      ),
                                    ),
                                    height: 50,
                                    width: 700.0,
                                    padding: const EdgeInsets.only(top: 10.0),
                                  ),
                                ],
                              ),
                            ),
                            Container(width: 15),
                            IconButton(
                              onPressed: () {
                                var a = _messageController.text;
                                fun_check(StringUtf8Pointer(a).toNativeUtf8());
                              },
                              icon: const Icon(Icons.arrow_forward_ios),
                              iconSize: 50,
                            ),
                          ],
                        )),
                  ],
                ),
              );
            })));
  }
}
