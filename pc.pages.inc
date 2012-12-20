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
    $charts = array();
    foreach(pc_pgd_data() as $title => $chartdata) {

        $piedata = array();
        $piedata['legend'] = array();
        $piedata['values'] = array();

        foreach($chartdata as $pair) {
            $piedata['legend'][] = pc_fullstate($pair[0]);
            $piedata['values'][] = $pair[1];
        }

            //array('#prefix' =>,'<div class="col3">'),
            //array('#suffix' => '</div>'),

        $charts[] = array(
            '#prefix' => '<div class="col3">',
            '#suffix' => '</div>',
            array(
                '#type' => 'markup',
                '#prefix' => '<div class="charttitle">',
                '#suffix' => '</div>',
                '#markup' => 'By '.$title
            ),
            array(
                '#theme' => 'pie',
                '#piedata' => $piedata
            )
        );
    }

    return $charts;
}

function pc_overview_summary() {
    $summary_data = pc_summary_data();
    $render_array = pc_render_array_from_summary_data($summary_data);
    return $render_array;
}

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent:
