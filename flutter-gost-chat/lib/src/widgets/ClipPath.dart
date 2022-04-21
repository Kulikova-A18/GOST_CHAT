import 'dart:ui';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class ClipPathClass_Other extends CustomClipper<Path> {
  late final double bubbleRadius = 60.0;
  late final double fourthEdgeRadius = 0.0;

  @override
  Path getClip(Size size) {
    var path = Path();
    path.addRRect(RRect.fromLTRBR(
        size.height * 5.5, size.height, 10, 20, Radius.circular(bubbleRadius)));

    var path2 = Path();
    path2.addRRect(RRect.fromLTRBAndCorners(
        size.height * (-10), size.height - bubbleRadius, -40, 0,
        bottomRight: Radius.circular(fourthEdgeRadius)));
    path.addPath(path2, Offset(size.width - 60, size.height - 45));
    path.close();
    return path;
  }

  @override
  bool shouldReclip(CustomClipper<Path> oldClipper) {
    return true;
  }
}

class ClipPathClass extends CustomClipper<Path> {
  late final double bubbleRadius = 60.0;
  late final double fourthEdgeRadius = 0.0;

  @override
  Path getClip(Size size) {
    var path = Path();
    path.addRRect(RRect.fromLTRBR(
        20, 10, size.width - 10, size.height, Radius.circular(bubbleRadius)));
    var path2 = Path();
    path2.addRRect(RRect.fromLTRBAndCorners(0, 0, bubbleRadius, bubbleRadius,
        bottomRight: Radius.circular(fourthEdgeRadius)));
    path.addPath(
        path2, Offset(size.width - bubbleRadius, size.height - bubbleRadius));
    path.close();
    return path;
  }

  @override
  bool shouldReclip(CustomClipper<Path> oldClipper) {
    return true;
  }
}

class ClipPathClass_Auth extends CustomClipper<Path> {
  @override
  Path getClip(Size size) {
    Offset firstEndPoint = Offset(size.width * .5, size.height - 20);
    Offset firstControlPoint = Offset(size.width * .25, size.height - 30);
    Offset secondEndPoint = Offset(size.width, size.height - 50);
    Offset secondControlPoint = Offset(size.width * .75, size.height - 10);

    final path = Path()
      ..lineTo(0.0, size.height)
      ..quadraticBezierTo(firstControlPoint.dx, firstControlPoint.dy,
          firstEndPoint.dx, firstEndPoint.dy)
      ..quadraticBezierTo(secondControlPoint.dx, secondControlPoint.dy,
          secondEndPoint.dx, secondEndPoint.dy)
      ..lineTo(size.width, 0.0)
      ..close();
    return path;
  }

  @override
  bool shouldReclip(CustomClipper<Path> oldClipper) {
    return true;
  }
}
