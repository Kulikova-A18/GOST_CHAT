import 'dart:io';
import 'dart:async';
import 'dart:convert';
import 'dart:ui';

import 'package:ffi/ffi.dart';
import 'package:flutter/material.dart';

import '../dynamic_library/dynamic_library_linux.dart';
import 'widgets/ClipPath.dart';

void main() {
  runApp(Home());
}

class Home extends StatefulWidget {
  @override
  _HomeState createState() => _HomeState();
}

List<String> litems_name = [];
List<String> litems_message = [];
List<String> litems_time = [];
ScrollController _scrollController = ScrollController();

class _HomeState extends State<Home> {
  final TextEditingController _messageController = TextEditingController();

  final _TextStyle = const TextStyle(
      color: Colors.black, fontSize: 18, fontFamily: 'Source_Code_Pro');
  final _TextStyle_message_user = const TextStyle(
      color: Colors.black, fontSize: 18, fontFamily: 'Source_Code_Pro');
  final _TextStyle_me = const TextStyle(
      color: Color.fromARGB(255, 255, 81, 0),
      fontSize: 18,
      fontFamily: 'Source_Code_Pro');

  late Timer _timer;
  int _start = 10;
  var now;

  bool isMe = false;

  void send_message(var message) {
    fun_encrypted_message(StringUtf8Pointer(message).toNativeUtf8());
  }

  var Kulikova_Alyona = false;
  var Maximov_Oleg = false;
  var Konovalov_Grigory = false;

  void create_false_list() {
    Kulikova_Alyona = false;
    Maximov_Oleg = false;
    Konovalov_Grigory = false;
  }

  String getSender() {
    final ptr = fun_get_sender();
    final result = ptr.toDartString();
    calloc.free(ptr);
    return result;
  }

  String getMessage() {
    final ptr = fun_get_message();
    final result = ptr.toDartString();
    calloc.free(ptr);
    return result;
  }

  String getUser() {
    final ptr = fun_get_user();
    final result = ptr.toDartString();
    calloc.free(ptr);
    return result;
  }

  void startTimer() {
    const oneSec = Duration(seconds: 1);
    _timer = Timer.periodic(
      oneSec,
      (Timer timer) {
        if (_start == 0) {
          create_false_list();
          setState(() {
            _start = 60; // 60 sec
          });
        } else {
          setState(() {
            _start--;
          });
        }
      },
    );
  }

  void startTimer_RawDatagramSocket() {
    const oneSec = Duration(seconds: 1);
    _timer = Timer.periodic(
      oneSec,
      (Timer timer) {
        if (_start == 0) {
          _RawDatagramSocket();
          setState(() {
            _start = 1;
          });
        } else {
          setState(() {
            _start--;
          });
        }
      },
    );
  }

// ----------- udp -----------
  //var DESTINATION_ADDRESS = InternetAddress("255.255.255.255");
  var first_getSender;
  var first_getMessage;

  var last_getSender = "";
  var last_getMessage = "";

  void _RawDatagramSocket() {
    first_getSender = getSender();
    first_getMessage = getMessage();
    now = DateTime.now();
    if ((first_getMessage != last_getMessage) ||
        (first_getSender != last_getSender)) {
      litems_name.add(getSender());
      litems_message.add(getMessage());
      litems_time.add("${now.hour}:${now.minute}:${now.second}");
      if (getSender() == "kulikova@gost_chat.com") Kulikova_Alyona = true;
      if (getSender() == "maximov@gost_chat.com") Maximov_Oleg = true;
      if (getSender() == "konovalov@gost_chat.com") Konovalov_Grigory = true;
      last_getMessage = first_getMessage;
      last_getSender = first_getSender;
    }
  }

  @override
  void initState() {
    startTimer();
    //_RawDatagramSocket();
    startTimer_RawDatagramSocket();
    super.initState();
  }

  @override
  void dispose() {
    _timer.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        home: Scaffold(
      appBar: AppBar(
        elevation: 0.0,
        //backgroundColor: Color.fromARGB(255, 255, 81, 0).withOpacity(0.9),
        backgroundColor: Colors.white,
        title: Text(
          'GOST CHAT',
          style: _TextStyle,
        ),
        actions: <Widget>[
          IconButton(
            icon: Icon(
              Icons.keyboard_return,
              color: Colors.black,
            ),
            onPressed: () {},
          ),
          IconButton(
            icon: Icon(
              Icons.exit_to_app,
              color: Colors.black,
            ),
            onPressed: () {
              exit(0);
            },
          ),
        ],
      ),
      body: LayoutBuilder(builder: (context, constraints) {
        return Container(
          alignment: Alignment.centerLeft,
          //color: Color.fromARGB(255, 255, 81, 0),
          color: Colors.white,
          child: Column(
            children: [
              SizedBox(
                  child: Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Column(children: [
                    Container(
                      //margin: const EdgeInsets.all(15.0),
                      //padding: const EdgeInsets.all(3.0),
                      padding: EdgeInsets.all(2),
                      color: Colors.white,
                      height: 650,
                      width: 300,
                      child: Column(
                        children: [
                          Column(
                            children: [
                              const CircleAvatar(
                                radius: 50.0,
                                backgroundImage: AssetImage("images/sfu.png"),
                                backgroundColor: Colors.transparent,
                              ),
                              Text(
                                getUser(),
                                style: _TextStyle,
                              ),
                            ],
                          ),
                          const SizedBox(
                            height: 20,
                          ),
                          Container(
                            child: Column(
                              children: [
                                IconButton(
                                  icon: Icon(
                                    Icons.people,
                                  ),
                                  iconSize: 50,
                                  onPressed: () {
                                    _messageController.text =
                                        "[${getUser()} from kulikova@gost_chat.com]";
                                  },
                                ),
                                Text(
                                  "kulikova@gost_chat.com",
                                  style: !isMe ? _TextStyle : _TextStyle_me,
                                ),
                                const SizedBox(
                                  width: 10,
                                ),
                                !Maximov_Oleg
                                    ? Text(
                                        "(не в сети)",
                                        style:
                                            !isMe ? _TextStyle : _TextStyle_me,
                                      )
                                    : Text(
                                        "(в сети)",
                                        style:
                                            !isMe ? _TextStyle : _TextStyle_me,
                                      ),
                                const SizedBox(
                                  height: 10,
                                ),
                              ],
                            ),
                            width: 300,
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: Colors.black,
                                width: 2,
                              ),
                              borderRadius: BorderRadius.circular(12),
                            ),
                          ),
                          const SizedBox(
                            height: 20,
                          ),
                          Container(
                            child: Column(
                              children: [
                                IconButton(
                                  icon: Icon(
                                    Icons.people,
                                  ),
                                  iconSize: 50,
                                  onPressed: () {
                                    _messageController.text =
                                        "[${getUser()} from maximov@gost_chat.com]";
                                  },
                                ),
                                Text(
                                  "maximov@gost_chat.com",
                                  style: !isMe ? _TextStyle : _TextStyle_me,
                                ),
                                const SizedBox(
                                  width: 10,
                                ),
                                !Maximov_Oleg
                                    ? Text(
                                        "(не в сети)",
                                        style:
                                            !isMe ? _TextStyle : _TextStyle_me,
                                      )
                                    : Text(
                                        "(в сети)",
                                        style:
                                            !isMe ? _TextStyle : _TextStyle_me,
                                      ),
                                const SizedBox(
                                  height: 10,
                                ),
                              ],
                            ),
                            width: 300,
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: Colors.black,
                                width: 2,
                              ),
                              borderRadius: BorderRadius.circular(12),
                            ),
                          ),
                          const SizedBox(
                            height: 20,
                          ),
                          Container(
                            child: Column(
                              children: [
                                IconButton(
                                  icon: Icon(
                                    Icons.people,
                                  ),
                                  iconSize: 50,
                                  onPressed: () {
                                    _messageController.text =
                                        "[${getUser()} from konovalov@gost_chat.com]";
                                  },
                                ),
                                Text(
                                  "konovalov@gost_chat.com",
                                  style: !isMe ? _TextStyle : _TextStyle_me,
                                ),
                                const SizedBox(
                                  width: 10,
                                ),
                                !Maximov_Oleg
                                    ? Text(
                                        "(не в сети)",
                                        style:
                                            !isMe ? _TextStyle : _TextStyle_me,
                                      )
                                    : Text(
                                        "(в сети)",
                                        style:
                                            !isMe ? _TextStyle : _TextStyle_me,
                                      ),
                                const SizedBox(
                                  height: 10,
                                ),
                              ],
                            ),
                            width: 300,
                            decoration: BoxDecoration(
                              border: Border.all(
                                color: Colors.black,
                                width: 2,
                              ),
                              borderRadius: BorderRadius.circular(12),
                            ),
                          ),
                        ],
                      ),
                    )
                  ]),
                  const SizedBox(
                    width: 20,
                  ),
                  Container(
                    decoration: BoxDecoration(
                      color: Colors.white,
                      border: Border.all(
                        color: Colors.black,
                        width: 2,
                      ),
                      borderRadius: BorderRadius.circular(12),
                    ),
                    padding: EdgeInsets.all(20),
                    child: Column(
                      children: [
                        Container(
                          alignment: Alignment.bottomCenter,
                          width: 1300,
                          height: 550,
                          //color: Colors.red.withOpacity(0.9),
                          child: Row(
                            children: [
                              Expanded(
                                  child: ListView.builder(
                                      itemCount: litems_message.length,
                                      itemExtent: 170.0,
                                      itemBuilder:
                                          (BuildContext ctxt, int Index) {
                                        return Row(
                                          mainAxisAlignment:
                                              MainAxisAlignment.end,
                                          children: <Widget>[
                                            Container(width: 10),
                                            if (litems_name[Index] != getUser())
                                              Column(
                                                mainAxisAlignment:
                                                    MainAxisAlignment.end,
                                                children: [
                                                  const SizedBox(
                                                    width: 60.0,
                                                  ),
                                                  const Icon(
                                                    Icons.people,
                                                    color: Colors.black,
                                                    size: 50.0,
                                                  ),
                                                  Text(
                                                    litems_name[Index],
                                                    style:
                                                        _TextStyle_message_user,
                                                  ),
                                                  Text(
                                                    litems_time[Index],
                                                    style:
                                                        _TextStyle_message_user,
                                                  ),
                                                ],
                                              )
                                            else
                                              ClipPath(
                                                clipper: ClipPathClass(),
                                                child: Container(
                                                  padding: EdgeInsets.all(30),
                                                  height: 140,
                                                  color: Colors.orange
                                                      .withOpacity(0.5),
                                                  margin: EdgeInsets.only(
                                                      left: 15, right: 15),
                                                  alignment: Alignment.center,
                                                  child: SizedBox(
                                                      width: 1000,
                                                      height: 240,
                                                      child: Column(
                                                        crossAxisAlignment:
                                                            CrossAxisAlignment
                                                                .start,
                                                        children: [
                                                          Container(
                                                            height: 10,
                                                            width: 10,
                                                          ),
                                                          Flexible(
                                                            flex: 1,
                                                            child: Text(
                                                              litems_message[
                                                                  Index],
                                                              style: _TextStyle,
                                                            ),
                                                          ),
                                                        ],
                                                      )),
                                                ),
                                              ),
                                            const SizedBox(
                                              width: 10.0,
                                            ),
                                            if (litems_name[Index] != getUser())
                                              ClipPath(
                                                clipper: ClipPathClass_Other(),
                                                child: Container(
                                                  padding: EdgeInsets.all(30),
                                                  height: 140,
                                                  color: Colors.yellow
                                                      .withOpacity(0.5),
                                                  margin: EdgeInsets.only(
                                                      left: 15, right: 15),
                                                  alignment: Alignment.center,
                                                  child: SizedBox(
                                                      width: 1000,
                                                      height: 240,
                                                      child: Column(
                                                        crossAxisAlignment:
                                                            CrossAxisAlignment
                                                                .start,
                                                        children: [
                                                          Container(
                                                            height: 10,
                                                            width: 10,
                                                          ),
                                                          Flexible(
                                                            flex: 1,
                                                            child: Text(
                                                              litems_message[
                                                                  Index],
                                                              style: _TextStyle,
                                                            ),
                                                          ),
                                                        ],
                                                      )),
                                                ),
                                              )
                                            else
                                              Column(
                                                children: [
                                                  const SizedBox(
                                                    height: 60.0,
                                                  ),
                                                  const Icon(
                                                    Icons.people,
                                                    color: Colors.black,
                                                    size: 50.0,
                                                  ),
                                                  Text(
                                                    litems_name[Index],
                                                    style:
                                                        _TextStyle_message_user,
                                                  ),
                                                  Text(
                                                    litems_time[Index],
                                                    style:
                                                        _TextStyle_message_user,
                                                  ),
                                                ],
                                              ),
                                          ],
                                        );
                                      })),
                            ],
                          ),
                        ),
                        const SizedBox(
                          height: 20,
                        ),
                        Container(
                            padding: const EdgeInsets.all(5),
                            decoration: BoxDecoration(
                              color: Colors.white,
                              border: Border.all(
                                color: Colors.black,
                                width: 2,
                              ),
                              borderRadius: BorderRadius.circular(12),
                            ),
                            // color: Colors.green.withOpacity(0.9),
                            child: Row(
                              mainAxisAlignment: MainAxisAlignment.center,
                              mainAxisSize: MainAxisSize.min,
                              children: [
                                //Container(width: 100),
                                Container(
                                  width: 1200,
                                  height: 60,
                                  child: Column(
                                    children: [
                                      Container(
                                        child: TextFormField(
                                          style: _TextStyle,
                                          autofocus: true,
                                          controller: _messageController,
                                          decoration: const InputDecoration(
                                            border: InputBorder.none,
                                          ),
                                        ),
                                        height: 50,
                                        width: 1100.0,
                                        padding:
                                            const EdgeInsets.only(top: 10.0),
                                      ),
                                    ],
                                  ),
                                ),
                                Container(width: 10),
                                IconButton(
                                  onPressed: () {
                                    send_message(_messageController.text);
                                  },
                                  icon: const Icon(Icons.send),
                                  iconSize: 25,
                                ),
                              ],
                            )),
                      ],
                    ),
                  ),
                ],
              )),
            ],
          ),
        );
      }),
    ));
  }
}
