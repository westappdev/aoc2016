<?php

/*
 * Advent of Code 2016
 * Day 4 (part 1 and 2)
 */

function extractRoomInfo($input_line) {
	if(preg_match("/(\S+)-(\d+)\[([^\]]*)\]/", $input_line, $output_array)) {
		return array(
			'room_name' => $output_array[1], 
			'sector_id' => $output_array[2], 
			'checksum' => $output_array[3]
		);
	}
	return false;
}

function generateChecksum($room_name) {
	// calculate char occurrences
	$char_count_array = count_chars(str_replace('-', '', $room_name), 1);

	// sort by occurrence count
	arsort($char_count_array);

	// group chars into occurrence count
	$dedupe = array();
	foreach($char_count_array as $char => $occurrence) {
		$dedupe[$occurrence][] = $char;
	}
	
	// cross my fingers and hope this actually works
	$checksum = '';
	foreach($dedupe as $occurrence => $chars) {
		sort($chars);
		for($i = 0; $i < count($chars); $i++) {
			$checksum .= chr($chars[$i]);
		}
	}
	
	// cut off the excess and return
	return substr($checksum, 0, 5);
}

function decryptRoomName($name, $sector_id) {
	$key = $sector_id % 26; // this should work right?
	$a_start = ord('a');
	$output = '';

	for($i = 0; $i < strlen($name); $i++) {
		$a = ord(substr($name, $i, 1));
		if($a == ord('-'))
			$output .= ' ';
		else
			$output .= chr($a_start + ((($a - $a_start) + $key) % 26));
	}

	return $output;
}

$input = file('day4_input.txt');
//$input = array("aaaaa-bbb-z-y-x-123[abxyz]", "a-b-c-d-e-f-g-h-987[abcde]", "not-a-real-room-404[oarel]");

// Part 1
$valid_room_sum = 0;
$valid_rooms = array();
foreach($input as $line) {
	$room_info = extractRoomInfo($line);
	$generated_checksum = generateChecksum($room_info['room_name']);
	if($generated_checksum == $room_info['checksum']) {
		$valid_rooms[] = $room_info;
		$valid_room_sum += (int)$room_info['sector_id'];
	}
}
echo "valid room sum: $valid_room_sum<br />\n";

// Part 2
foreach($valid_rooms as $room) {
	$decrypted_name = decryptRoomName($room['room_name'], (int)$room['sector_id']);
	echo "room name: $decrypted_name, sector: {$room['sector_id']}<br />\n";
}
