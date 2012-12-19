<?php

function pc_overview_page() {
    $file = file_load(variable_get('compendium', false));

    if ($file == false) {
        return '<h1>You need to upload a compendium file</h1>'.l('Upload', 'admin/property-compendium/upload');
    }

    $filepath = drupal_realpath($file->uri);

    $objPHPExcel = PHPExcel_IOFactory::load($filepath);

    $sheets = $objPHPExcel->getSheetCount();


    $header = array('Property', 'Centre Narrative', 'Chart');
    $rows = array();
    for ($i = 2; $i < $sheets; $i ++) {
        $sheet = $objPHPExcel->getSheet($i);
        $title = $sheet->getTitle();
        $property = pc_process_sheet($sheet);
        $rows[] = array(
            $title,
            $property['centre_narrative'],
            theme('pie', array('piedata' => pc_piedata_from_graphdata($property['graphdata'])))
        );
    }

    return array(
        'sheets' => array(
            '#theme' => 'table',
            '#rows' => $rows,
            '#header' => $header
        )
    );
}

function pc_upload_form($form, &$form_state) {

    $form = array();

    $fid = variable_get('compendium', false);

    if ($fid == false) {
            $instruction = '<h1>Upload property compendium file. xlsx or xlsm</h1>';
    } else {
            $instruction = "<h1>You already have a compendium file.</h1><h1>Only upload a new file if you want to replace the current compendium file. </h1>";
    }

    $form['instruction'] = array(
        '#markup' => $instruction
    );

    $form['compendium'] = array(
        '#title' => t('Choose property compendium file'),
        '#type' => 'file'
    );

    $form['submit'] = array(
        '#value' => t('Upload'),
        '#type' => 'submit'
    );

    return $form;
}

function pc_upload_form_validate($form, &$form_state) {
    $validators = array(
        'file_validate_extensions' => array('xlsx xlsm')
    );
    $mFile = file_save_upload('compendium', $validators, 'public://');

    if ($mFile == false) {
        form_set_error('compendium', 'Need to select a file');
    }
}

function pc_upload_form_submit($form, &$form_state) {
    $mFile = file_save_upload('compendium');
    variable_set('compendium', $mFile->fid);
    pc_delete_cache();
    drupal_set_message("Great success. $mFile->filename uploaded.");
}

// vim: set expandtab tabstop=4 shiftwidth=4 autoindent:
