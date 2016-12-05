package main

import (
	"fmt"
	"strings"
	"strconv"
)

func main() {

  getDistance("R2, L3") // 5
  getDistance("R2, R2, R2") // 2
  getDistance("R5, L5, R5, R3") // 12
  getDistance("R1, L3, R5, R5, R5, L4, R5, R1, R2, L1, L1, R5, R1, L3, L5, L2, R4, L1, R4, R5, L3, R5, L1, R3, L5, R1, L2, R1, L5, L1, R1, R4, R1, L1, L3, R3, R5, L3, R4, L4, R5, L5, L1, L2, R4, R3, R3, L185, R3, R4, L5, L4, R48, R1, R2, L1, R1, L4, L4, R77, R5, L2, R192, R2, R5, L4, L5, L3, R2, L4, R1, L5, R5, R4, R1, R2, L3, R4, R4, L2, L4, L3, R5, R4, L2, L1, L3, R1, R5, R5, R2, L5, L2, L3, L4, R2, R1, L4, L1, R1, R5, R3, R3, R4, L1, L4, R1, L2, R3, L3, L2, L1, L2, L2, L1, L2, R3, R1, L4, R1, L1, L4, R1, L2, L5, R3, L5, L2, L2, L3, R1, L4, R1, R1, R2, L1, L4, L4, R2, R2, R2, R2, R5, R1, L1, L4, L5, R2, R4, L3, L5, R2, R3, L4, L1, R2, R3, R5, L2, L3, R3, R1, R3") // 298
}

func intAbs(i int) int {
  
  if (i < 0) { i = -i }
  return i
}

func getDistance (input string) {
  
  curr_dir := 'N'
	vector := [2]int{0, 0}
	
	moves := strings.Split(input, ", ")
	for _, move := range moves {
	  
	  move_array := strings.SplitAfterN(move, "", 2)
	  distance, err := strconv.Atoi(move_array[1])
	  if (err != nil) { fmt.Println(err) }
	  
	  switch move_array[0] {
	    
	    case "R":
	      switch curr_dir {
	        case 'N':
	          curr_dir = 'E'
	          vector[0] += distance
	        case 'E':
	          curr_dir = 'S'
	          vector[1] -= distance
	        case 'S':
	          curr_dir = 'W'
	          vector[0] -= distance
	        case 'W':
	          curr_dir = 'N'
	          vector[1] += distance
	        default:
	          panic("Non cardinal direction.")
	      }
	      
	    case "L":
	      switch curr_dir {
	        case 'N':
	          curr_dir = 'W'
	          vector[0] -= distance
	        case 'E':
	          curr_dir = 'N'
	          vector[1] += distance
	        case 'S':
	          curr_dir = 'E'
	          vector[0] += distance
	        case 'W':
	          curr_dir = 'S'
	          vector[1] -= distance
	        default:
	          panic("Non cardinal direction.")
	      }
	      
	    default:
	      panic("Not R or L.")
	  }
	}
	
	distance := intAbs(vector[0]) + intAbs(vector[1])
	fmt.Println(distance)
}
