<?php

set_time_limit(0);

/*
 * Advent of Code 2016
 * Day 5 (part 1 and 2)
 */

function calculateHashes($salt, $max = 8) {
	$result = array();
	$count = 0;
	$start = 0;

	$cache_file = md5($salt).".cache";
	if(file_exists($cache_file)) {
		$result = file($cache_file);
		if(count($result) >= $max)
			return $result;
	}

	for($i = 0; $i < 1000000000; $i++) {
		$hash = md5($salt.$i);
		if(substr($hash, 0, 5) === '00000') {
			$result[$count++] = $hash;
			if($count >= $max)
				break;
		}
	}

	file_put_contents($cache_file, implode("\n", $result));
	return $result;
}

$puzzle_input = 'reyedfim';
$hashes = calculateHashes($puzzle_input, 30);

// Part 1
$password = '';
for($i = 0; $i < 8; $i++) {
	$password .= substr($hashes[$i], 5, 1);
}
echo "Step 1 Password: $password\n";

// Part 2
$password = array_fill(0, 8, '_');
for($i = 0; $i < count($hashes); $i++) {
	$pos = substr($hashes[$i], 5, 1);
	$char = substr($hashes[$i], 6, 1);
	if (is_numeric($pos) && (int)$pos < 8 && $password[(int)$pos] === '_') 
		$password[(int)$pos] = $char;

}
echo "Step 2 Password: ".implode($password);