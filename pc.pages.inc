<?php

function pc_centre_profiles() {
	// Redirect to the first Centre Profile (ACT)
	drupal_goto('property-portfolio/centre-profiles/act');
}

function pc_generate_profile_link($profile) {
	return '<a href="../profiles/' . str_replace( ' ', '-', $profile ) . '">' . $profile . '</a>';
}

function pc_centre_profiles_act() {
	$properties = pc_get_properties_from_region('act');
	for( $i=0; $i<count($properties); $i++) {
		$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_centre_profiles_nsw() {
	$properties = pc_get_properties_from_region('nsw');
	for( $i=0; $i<count($properties); $i++) {
		$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_centre_profiles_qld() {
	$properties = pc_get_properties_from_region('qld');
	for( $i=0; $i<count($properties); $i++) {
		$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_centre_profiles_sa() {
	$properties = pc_get_properties_from_region('sa');
	for( $i=0; $i<count($properties); $i++) {
		$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_centre_profiles_vic() {
	$properties = pc_get_properties_from_region('vic');
	for( $i=0; $i<count($properties); $i++) {
		$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_centre_profiles_wa() {
	$properties = pc_get_properties_from_region('wa');
	for( $i=0; $i<count($properties); $i++) {
	$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_centre_profiles_nz() {
	$properties = pc_get_properties_from_region('nz');
	for( $i=0; $i<count($properties); $i++) {
		$link = pc_generate_profile_link($properties[$i]);
		$properties[$i] = $link;
	}
	$theme_args = array( 'items' => $properties, 'type' => 'ul', 'attributes' => array( 'class' => 'briefcase_links' ) );
	return theme('item_list', $theme_args );
}

function pc_property_page($pc_property) {
	$menu = menu_tree('navigation');
	
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
    return pc_region_overview(PC_EXCEL_NZ, 'New Zealand');
}

function pc_australia() {
    return pc_region_overview(PC_EXCEL_AUS, 'Australia');
}

// This function render Australia and New Zealand Overview
function pc_region_overview($range, $title) {
    $render = array();
    $format = true;
    $rows = pc_excel_range($range, $format);
    $render[] = array(
        '#prefix' => '<div class="portfolio">',
        '#suffix' => '</div>',
        array(
            '#type' => 'markup',
            '#markup' => "<div>Portfolio Overview – $title</div>"
        ),
        array(
            '#theme' => 'table',
            '#header' => array_shift($rows),
            '#rows' => $rows
        )
    );
    return $render;
}

function pc_lep() {
    // todo
}

function pc_jvp() {
    $render = array();

    $render[] = array(
        '#type' => 'markup',
        '#markup' => '<div class="portfolioheading">Joint Venture Partners</div>'
    );

    $charts = array(
        'WRT/WDC Joint Ventures'          => pc_excel_range(PC_EXCEL_JV),
        'WRT/WDC Multiple Joint Ventures' => pc_excel_range(PC_EXCEL_JVM)
    );

    foreach ($charts as $title => $rows) {
        $piedata = pc_piedata_from_rows($rows);
        $render[] = array(
            '#prefix' => '<div class="col3">',
            '#suffix' => '</div>',
            array(
                '#type' => 'markup',
                '#prefix' => '<div class="charttitle">',
                '#suffix' => '</div>',
                '#markup' => $title
            ),
            array(
                '#theme' => 'pie',
                '#piedata' => $piedata
            )
        );
    }

    return $render;
}

function pc_pgd() {
    $render = array();

    $render[] = array(
        '#type' => 'markup',
        '#markup' => '<div class="portfolioheading">Portfolio Geographical Diversification</div>'
    );
    foreach(pc_pgd_data() as $title => $chartdata) {

        $piedata = array();
        $piedata['legend'] = array();
        $piedata['values'] = array();

        foreach($chartdata as $pair) {
            $piedata['legend'][] = pc_fullstate_from_short($pair[0]);
            $piedata['values'][] = $pair[1];
        }

            //array('#prefix' =>,'<div class="col3">'),
            //array('#suffix' => '</div>'),

        $render[] = array(
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

    return $render;
}

function pc_overview_summary() {
    $summary_data = pc_summary_data();
    $render_array = pc_render_array_from_summary_data($summary_data);
    return $render_array;
}

function pc_overview(){
	drupal_goto( 'property-portfolio/overview/summary' );
	//drupal_not_found();
}

function pc_generate_pdf( $title )
{
	// Load the file.
	$file = file_load(variable_get('compendium', false));
	$filepath = drupal_realpath($file->uri);
	
	// Get xls Data.
	$data = pc_process_sheet_from_title( $title );
	
	// Generate an image of the chart.
	
	
	// Generate a PDF.
	$html =
	  '<html><body>'.
	  '<h1>' . $title . '</h1>'.
	  '<img src="http://localhost/' . base_path() .'sites/default/files/chatswood_chart.png' . '" />'.
	  '</body></html>';

	$dompdf = new DOMPDF();
	$dompdf->load_html($html);
	$dompdf->render();
	$dompdf->stream( $title . ".pdf");
}
