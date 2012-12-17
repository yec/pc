<?php
$files = glob('*.php');

function anchor($file) {
    return "<a href='$file'>$file</a>";
}

print implode('<br>',array_map('anchor', $files));
