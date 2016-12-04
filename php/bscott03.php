<?php

/*
 * Advent of Code 2016
 * Day 3 (part 1 and 2)
 */

function isValidTriangle($a, $b, $c) {
	return ($a + $b > $c && $a + $c > $b && $b + $c > $a);
}

$input = file('day3_input.txt');

$valid_triangle_count = 0;
foreach($input as $line) {
	$args = array_values(array_filter(explode(' ', $line)));
	if(isValidTriangle((int)$args[0], (int)$args[1], (int)$args[2]))
		$valid_triangle_count++;
}

echo "Part 1 Count: $valid_triangle_count\n";

$valid_triangle_count = 0;
for($i = 0; $i < count($input); $i += 3) {
	$args1 = array_values(array_filter(explode(' ', $input[$i+0])));
	$args2 = array_values(array_filter(explode(' ', $input[$i+1])));
	$args3 = array_values(array_filter(explode(' ', $input[$i+2])));

	if(isValidTriangle((int)$args1[0], (int)$args2[0], (int)$args3[0]))
		$valid_triangle_count++;

	if(isValidTriangle((int)$args1[1], (int)$args2[1], (int)$args3[1]))
		$valid_triangle_count++;

	if(isValidTriangle((int)$args1[2], (int)$args2[2], (int)$args3[2]))
		$valid_triangle_count++;
}

echo "Part 2 Count: $valid_triangle_count\n";