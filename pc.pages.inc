<?php

function pc_property_page($pc_property) {

    foreach($pc_property['tables'] as $table => $rows) {
        $rtables[] = theme('table', array('header' => array(array('data' => $table, 'colspan' => 3)),'rows' => $rows));
    }

    return array(
        '#theme' => 'profile',
        '#tables' => implode('<br>',$rtables),
        '#title' => $pc_property['title'],
        '#centre_narrative' => $pc_property['centre_narrative'],
        '#chart' => theme('pie', array('piedata' => pc_piedata_from_graphdata($pc_property['graphdata'])))
    );
}

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent:
