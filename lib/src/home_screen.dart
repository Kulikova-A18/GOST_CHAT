import '../dynamic_library/dynamic_library_linux.dart';

import 'package:flutter/material.dart';
import 'package:ffi/ffi.dart';
import 'dart:ui';
import 'dart:async';
import 'dart:io';
import 'dart:convert';

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
    fontSize: 10,
    fontFamily: 'Source_Code_Pro',
    height: 1.5,
  );

  late bool _passwordVisible = false;

  List<String> litems = [];
  ScrollController _scrollController = ScrollController();

  @override
  void initState() {
    _RawDatagramSocket();
    super.initState();
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
          print("received ${String.fromCharCodes(dg.data)}");
          setState(() => litems.add(String.fromCharCodes(dg.data)));
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
                              width: 900,
                              height: 500,
                              color: Colors.white.withOpacity(0.9),
                              child: Column(
                                mainAxisAlignment: MainAxisAlignment.center,
                                children: [
                                  Expanded(
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
                                                const Icon(
                                                  Icons.people,
                                                  color: Colors.black,
                                                  size: 50.0,
                                                ),
                                                const SizedBox(
                                                  width: 10.0,
                                                ),
                                                Container(
                                                    margin:
                                                        const EdgeInsets.all(
                                                            10),
                                                    decoration: BoxDecoration(
                                                      border: Border.all(
                                                          width: 5,
                                                          color: Colors.black),
                                                      //color: Colors.grey,
                                                    ),
                                                    width: 700,
                                                    child: Column(
                                                      crossAxisAlignment:
                                                          CrossAxisAlignment
                                                              .start,
                                                      children: [
                                                        Container(
                                                          height: 2,
                                                        ),
                                                        Flexible(
                                                          child: Text(
                                                              litems[Index],
                                                              style:
                                                                  _TextStyle),
                                                        ),
                                                      ],
                                                    ))
                                              ],
                                            );
                                          })),
                                  Container(
                                      width: 900.0,
                                      child: Row(
                                        children: [
                                          Container(width: 200),
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
                                                    controller:
                                                        _messageController,
                                                    decoration:
                                                        const InputDecoration(
                                                      border: InputBorder.none,
                                                    ),
                                                  ),
                                                  height: 50,
                                                  width: 300.0,
                                                  padding:
                                                      const EdgeInsets.only(
                                                          top: 10.0),
                                                ),
                                              ],
                                            ),
                                          ),
                                          Container(width: 15),
                                          IconButton(
                                            onPressed: () {
                                              var a = _messageController.text;
                                              fun_check(StringUtf8Pointer(a)
                                                  .toNativeUtf8());
                                            },
                                            icon: const Icon(
                                                Icons.arrow_forward_ios),
                                            iconSize: 50,
                                          ),
                                        ],
                                      )),
                                  Container(height: 20),
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
