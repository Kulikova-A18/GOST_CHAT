import 'dart:io';
import 'dart:async';
import 'dart:convert';

import 'package:flutter/material.dart';

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
  final _TextStyle = const TextStyle(
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

  void startTimer() {
    const oneSec = Duration(seconds: 1);
    _timer = Timer.periodic(
      oneSec,
      (Timer timer) {
        if (_start == 0) {
          create_false_list();
          setState(() {
            //timer.cancel(); // stop timer
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
  var username = "Lena";

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
                      padding: EdgeInsets.all(10),
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
                                "Куликова Алена",
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
                                "Куликова Алена",
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
                                "Максимов Олег",
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
                                "Коновалов Григорий",
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
                                "Киселёва Амелия",
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
                                "Воронин Константин",
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
                                "Касаткина Амелия",
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
                                "Родина Матвея",
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
                                "Глебов Олег",
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
                                "Григорьев Олег",
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
                                "Павлов Матвей",
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
                                "Антипов Григорий",
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
                                "Ильина Дарья",
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
                                "Климов Сергей",
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
                                "Куликов Никита",
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
                                "Илькин Григорий",
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
                                "Марков Сергей",
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
                                "Попова Дарья",
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
                                "Сидоров Дмитрий",
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
                                "Сипоров Григорий",
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
                                "Богданова Амелия",
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
                          Text("timer: $_start"), //delete me
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
                          width: 900,
                          height: 550,
                          //color: Colors.red.withOpacity(0.9),
                          child: Row(
                            children: [
                              Expanded(
                                  child: ListView.builder(
                                      itemCount: litems_message.length,
                                      itemExtent: 150.0,
                                      itemBuilder:
                                          (BuildContext ctxt, int Index) {
                                        return Row(
                                          mainAxisAlignment:
                                              MainAxisAlignment.center,
                                          //mainAxisSize: MainAxisSize.min,
                                          children: <Widget>[
                                            Container(width: 20),
                                            if (litems_name[Index] != username)
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
                                                    style: _TextStyle,
                                                  ),
                                                  Text(
                                                    litems_time[Index],
                                                    style: _TextStyle,
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
                                                      width: 700,
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
                                            if (litems_name[Index] != username)
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
                                                      width: 700,
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
                                                    style: _TextStyle,
                                                  ),
                                                  Text(
                                                    litems_time[Index],
                                                    style: _TextStyle,
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
                                  width: 820,
                                  height: 60,
                                  decoration: BoxDecoration(
                                    border: Border.all(
                                      color: Colors.black,
                                      width: 1,
                                    ),
                                    borderRadius:
                                        BorderRadius.all(Radius.circular(30.0)),
                                  ),
                                  child: Column(
                                    children: [
                                      Container(
                                        child: TextFormField(
                                          style: _TextStyle,
                                          autofocus: true,
                                          //controller: _messageController,
                                          decoration: const InputDecoration(
                                            border: InputBorder.none,
                                          ),
                                        ),
                                        height: 50,
                                        width: 700.0,
                                        padding:
                                            const EdgeInsets.only(top: 10.0),
                                      ),
                                    ],
                                  ),
                                ),
                                Container(width: 10),
                                IconButton(
                                  onPressed: () {},
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
