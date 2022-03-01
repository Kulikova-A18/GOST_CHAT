import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

Widget buildContent() {
  return Container(
      color: Color.fromARGB(255, 255, 81, 0),
      alignment: Alignment.center,
      padding: EdgeInsets.all(10),
      child: Column(
        children: const [
          CircleAvatar(
            radius: 50.0,
            backgroundImage: AssetImage("images/sfu.png"),
            backgroundColor: Colors.transparent,
          ),
          Text('Younan Nowzaradan | Dr. Now',
              style: TextStyle(
                  fontWeight: FontWeight.bold,
                  color: Colors.black87,
                  fontSize: 25)),
        ],
      ));
}
