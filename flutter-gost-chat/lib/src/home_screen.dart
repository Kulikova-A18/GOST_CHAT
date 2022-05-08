import 'dart:io';
import 'dart:async';
import 'dart:convert';

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
      color: Colors.black, fontSize: 16, fontFamily: 'Source_Code_Pro');
  final _TextStyle_message_user = const TextStyle(
      color: Colors.black, fontSize: 16, fontFamily: 'Source_Code_Pro');
  final _TextStyle_me = const TextStyle(
      color: Color.fromARGB(255, 255, 81, 0),
      fontSize: 16,
      fontFamily: 'Source_Code_Pro');

  late Timer _timer;
  int _start = 10;
  var now;

/*
  now = DateTime.now();
  litems_name.add("Lena");
  litems_message.add("Nice to see you, Vadim!");
  litems_time.add("${now.hour}:${now.minute}:${now.second}");
  lena = true;
*/

  void send_message(var message) {
    now = DateTime.now();
    litems_name.add(getUser());
    litems_message.add(message);
    litems_time.add("${now.hour}:${now.minute}:${now.second}");
    if (getUser() == "kulikova@gost_chat.com") Kulikova_Alyona = true;
    if (getUser() == "maximov@gost_chat.com") Maximov_Oleg = true;
    if (getUser() == "konovalov@gost_chat.com") Konovalov_Grigory = true;
    if (getUser() == "kiseleva@gost_chat.com") Kiseleva_Amelia = true;
    if (getUser() == "voronin@gost_chat.com") Voronin_Konstantin = true;
    if (getUser() == "kasatkina@gost_chat.com") Kasatkina_Amelia = true;
    if (getUser() == "homeland@gost_chat.com") Homeland_Matvey = true;
    if (getUser() == "glebov@gost_chat.com") Glebov_Oleg = true;
    if (getUser() == "grigoriev@gost_chat.com") Grigoriev_Oleg = true;
    if (getUser() == "pavlov@gost_chat.com") Pavlov_Matvey = true;
    if (getUser() == "antipova@gost_chat.com") Antipov_Grigory = true;
    if (getUser() == "ilina@gost_chat.com") Ilina_Daria = true;
    if (getUser() == "klimov@gost_chat.com") Klimov_Sergey = true;
    if (getUser() == "kulikov@gost_chat.com") Kulikov_Nikita = true;
    if (getUser() == "ilkina@gost_chat.com") Ilkin_Grigory = true;
    if (getUser() == "markov@gost_chat.com") Markov_Sergey = true;
    if (getUser() == "popova@gost_chat.com") Popova_Daria = true;
    if (getUser() == "sidorov@gost_chat.com") Sidorov_Dmitry = true;
    if (getUser() == "siporov@gost_chat.com") Siporov_Grigory = true;
    if (getUser() == "bogdanova@gost_chat.com") Bogdanova_Amelia = true;
  }

  var Kulikova_Alyona = false;
  var Maximov_Oleg = false;
  var Konovalov_Grigory = false;
  var Kiseleva_Amelia = false;
  var Voronin_Konstantin = false;
  var Kasatkina_Amelia = false;
  var Homeland_Matvey = false;
  var Glebov_Oleg = false;
  var Grigoriev_Oleg = false;
  var Pavlov_Matvey = false;
  var Antipov_Grigory = false;
  var Ilina_Daria = false;
  var Klimov_Sergey = false;
  var Kulikov_Nikita = false;
  var Ilkin_Grigory = false;
  var Markov_Sergey = false;
  var Popova_Daria = false;
  var Sidorov_Dmitry = false;
  var Siporov_Grigory = false;
  var Bogdanova_Amelia = false;

  void create_false_list() {
    Kulikova_Alyona = false;
    Maximov_Oleg = false;
    Konovalov_Grigory = false;
    Kiseleva_Amelia = false;
    Voronin_Konstantin = false;
    Kasatkina_Amelia = false;
    Homeland_Matvey = false;
    Glebov_Oleg = false;
    Grigoriev_Oleg = false;
    Pavlov_Matvey = false;
    Antipov_Grigory = false;
    Ilina_Daria = false;
    Klimov_Sergey = false;
    Kulikov_Nikita = false;
    Ilkin_Grigory = false;
    Markov_Sergey = false;
    Popova_Daria = false;
    Sidorov_Dmitry = false;
    Siporov_Grigory = false;
    Bogdanova_Amelia = false;
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

  bool isMe = false;

  @override
  void initState() {
    startTimer();
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
                          Row(
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
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "kulikova@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Kulikova_Alyona
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
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
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "konovalov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Konovalov_Grigory
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "kiseleva@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Kiseleva_Amelia
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "voronin@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Voronin_Konstantin
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "kasatkina@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Kasatkina_Amelia
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "homeland@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Homeland_Matvey
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "glebov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Glebov_Oleg
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "grigoriev@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Grigoriev_Oleg
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "pavlov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Pavlov_Matvey
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "antipova@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Antipov_Grigory
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "ilina@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Ilina_Daria
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "klimov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Klimov_Sergey
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "kulikov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Kulikov_Nikita
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "ilkina@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Ilkin_Grigory
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "markov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Markov_Sergey
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "popova@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Popova_Daria
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "sidorov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Sidorov_Dmitry
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "siporov@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Siporov_Grigory
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
                          ),
                          Row(
                            children: [
                              Icon(Icons.people),
                              const SizedBox(
                                width: 10,
                              ),
                              Text(
                                "bogdanova@gost_chat.com",
                                style: !isMe ? _TextStyle : _TextStyle_me,
                              ),
                              const SizedBox(
                                width: 10,
                              ),
                              !Bogdanova_Amelia
                                  ? Text(
                                      "(не в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    )
                                  : Text(
                                      "(в сети)",
                                      style: !isMe ? _TextStyle : _TextStyle_me,
                                    ),
                            ],
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
                                            Container(width: 20),
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
                                  // decoration: BoxDecoration(
                                  //   border: Border.all(
                                  //     color: Colors.black,
                                  //     width: 1,
                                  //   ),
                                  //   borderRadius:
                                  //       BorderRadius.all(Radius.circular(30.0)),
                                  // ),
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
