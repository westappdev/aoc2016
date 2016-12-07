//
// Created by Kevin Murray on 12/6/16.
// Copyright (c) 2016 Kevin Murray. All rights reserved.
//

import Foundation

class Day1 {
   enum Direction: Int {
      case North = 0
      case East = 1
      case South = 2
      case West = 3
   }
   static var firstIntersection = 0;
   static var intersection = "";

   public static func process() -> String {
      var xpos = 0;
      var ypos = 0;
      let vectors = NSMutableSet();

      findPosition(xpos: &xpos, ypos: &ypos, vectors: vectors);

      print("Ending position x = \(xpos) y = \(ypos)");
      let distance = Swift.abs(xpos) + Swift.abs(ypos);
      print("Resulting distance from Easter Bunny = \(distance)");

      var result = "Ending position x = \(xpos) y = \(ypos) distance = \(distance)\n";
      result += "\(intersection)\n";
      return result;
   }

   static func findPosition(xpos: inout Int, ypos: inout Int, vectors: NSMutableSet) {
      var position = Direction.North;

      do {
         var data = try String(contentsOfFile: "/Users/kmurray/src/aoc/aoc/Day1.txt", encoding: String.Encoding.utf8).replacingOccurrences(of: " ", with: "");

         let moveArr = data.characters.split{$0 == ","}.map(String.init);


         for move in moveArr {

            let dIndex = move.index(move.startIndex, offsetBy: 1);
            let dMove = Int(move.substring(from: dIndex));

            if (move.substring(to: dIndex) == "R") {

               switch position {
               case Direction.North:
                  AddPoint(xpos: xpos, ypos: ypos, move: dMove!, xMove: 1, vectors: vectors);
                  xpos += dMove!;
                  position = Direction.East;
               case Direction.East:
                  AddPoint(xpos: xpos, ypos: ypos, move: -dMove!, xMove: 0, vectors: vectors);
                  ypos -= dMove!;
                  position = Direction.South;
               case Direction.South:
                  AddPoint(xpos: xpos, ypos: ypos, move: -dMove!, xMove: 1, vectors: vectors);
                  xpos -= dMove!;
                  position = Direction.West;
               case Direction.West:
                  AddPoint(xpos: xpos, ypos: ypos, move: dMove!, xMove: 0, vectors: vectors);
                  ypos += dMove!;
                  position = Direction.North;
               }
            }

            else if (move.substring(to: dIndex) == "L") {
               switch position {
               case Direction.North:
                  AddPoint(xpos: xpos, ypos: ypos, move: -dMove!, xMove: 1, vectors: vectors);
                  xpos -= dMove!;
                  position = Direction.West;
               case Direction.East:
                  AddPoint(xpos: xpos, ypos: ypos, move: dMove!, xMove: 0, vectors: vectors);
                  ypos += dMove!;
                  position = Direction.North;
               case Direction.South:
                  AddPoint(xpos: xpos, ypos: ypos, move: dMove!, xMove: 1, vectors: vectors);
                  xpos += dMove!;
                  position = Direction.East;
               case Direction.West:
                  AddPoint(xpos: xpos, ypos: ypos, move: -dMove!, xMove: 0, vectors: vectors);
                  ypos -= dMove!;
                  position = Direction.South;
               }
            }
         }
      }
      catch {}

   }

   static func AddPoint(xpos: Int, ypos: Int, move: Int, xMove: Int, vectors: NSMutableSet) {
      var count = 0;
      let direction = (move < 0) ? -1 : 1;

      if (firstIntersection == 0) {
         while (count < Swift.abs(move)) {
            if (xMove == 0) {
               let index = "\(xpos),\(ypos + (count * direction))";

               if (vectors.contains(index)) {
                  let distance = Swift.abs(xpos) + Swift.abs(ypos + count);
                  intersection = "Intersection at \(index) distace from home = \(distance)";
                  firstIntersection = 1;
               }
               vectors.add(index);
            } else if (xMove == 1) {
               let index = "\(xpos + (count * direction)),\(ypos)";
               if (vectors.contains(index)) {
                  let distance = Swift.abs(xpos + count) + Swift.abs(ypos);
                  intersection = "Intersection2 at \(index) distance from home = \(distance)";
                  firstIntersection = 1;
               }
               vectors.add(index);
            }
            count += 1;
         }
      }
   }
}
