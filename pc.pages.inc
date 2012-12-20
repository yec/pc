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

function pc_nz() {
    // todo
}

function pc_australia() {
    // todo
}

function pc_lep() {
    // todo
}

function pc_jvp() {
    // todo
}

function pc_pgd() {
    // todo
}

function pc_overview_summary() {
    $summary_data = pc_summary_data();
    $render_array = pc_render_array_from_summary_data($summary_data);
    return $render_array;
}

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent:
