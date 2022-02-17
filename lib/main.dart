/* echo "hello" | socat - udp-sendto:127.0.0.1:55555 */

import 'dart:async';

import 'package:flutter/material.dart';
import 'dart:io';
import 'dart:convert';
import 'package:ffi/ffi.dart';

/* 
$ flutter pub add window_size 
$ flutter pub get
*/
import 'package:window_size/window_size.dart';

import 'dynamic_library/dynamic_library_linux.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  /*if (Platform.isLinux) {
    setWindowMaxSize(const Size(520, 800));
    setWindowMinSize(const Size(520, 800));
    /*
    Future<Null>.delayed(Duration(seconds: 1), () {
        setWindowFrame(Rect.fromCenter(center: Offset(1000, 500), width: 600, height: 1000));
    });*/
  }*/
  runApp(new MyApp());
}

// void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext ctxt) {
    return new MaterialApp(
      home: new ListDisplay(),
    );
  }
}

class ListDisplay extends StatefulWidget {
  @override
  State createState() => new DyanmicList();
}

class DyanmicList extends State<ListDisplay> {
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

  void _Send_RawDatagramSocket(var _message) {
    RawDatagramSocket.bind(InternetAddress.anyIPv4, 55555)
        .then((RawDatagramSocket udpSocket) {
      udpSocket.broadcastEnabled = true;
      udpSocket.send(
          _message.codeUnits, InternetAddress('255.255.255.255'), 55555);
    });
  }

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

  @override
  Widget build(BuildContext ctxt) {
    return Scaffold(
        appBar: AppBar(
          title: const Text("Dynamic Demo"),
        ),
        body: Column(
          children: <Widget>[
            Expanded(
                child: ListView.builder(
                    itemCount: litems.length,
                    itemExtent: 90.0,
                    itemBuilder: (BuildContext ctxt, int Index) {
                      return Row(
                        mainAxisAlignment: MainAxisAlignment.start,
                        mainAxisSize: MainAxisSize.min,
                        children: <Widget>[
                          Container(width: 15),
                          const Icon(
                            Icons.people,
                            color: Colors.black,
                            size: 50.0,
                          ),
                          const SizedBox(
                            width: 10.0,
                          ),
                          Container(
                              margin: const EdgeInsets.all(10),
                              decoration: BoxDecoration(
                                border: Border.all(color: Colors.grey),
                                //color: Colors.grey,
                                borderRadius: BorderRadius.circular(12),
                              ),
                              width: 370,
                              child: Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  Container(height: 7),
                                  Flexible(
                                    child: Text(litems[Index],
                                        style: const TextStyle(
                                            color: Colors.black, fontSize: 20)),
                                  ),
                                ],
                              ))
                        ],
                      );
                    })),
            Container(
                width: 500.0,
                child: Row(
                  children: [
                    Container(width: 15),
                    Container(
                      width: 390,
                      child: TextFormField(
                          controller: _messageController,
                          decoration: const InputDecoration(
                            border: OutlineInputBorder(
                                borderRadius:
                                    BorderRadius.all(Radius.circular(12))),
                            hintText: "send message",
                          )),
                    ),
                    Container(width: 15),
                    IconButton(
                        onPressed: () {
                          var a = _messageController.text;
                          var check_a =
                              fun_check(StringUtf8Pointer(a).toNativeUtf8());
                          _Send_RawDatagramSocket(check_a.toString());
                          //_Send_RawDatagramSocket("_text");
                        },
                        icon: const Icon(Icons.send)),
                  ],
                )),
            Container(height: 20),
          ],
        ));
  }
}
