<?php

class Parse {

    private $currentRowData;
    private $state;

    // States
    private static $states = array(
        'start'     ,
        'table'     ,
        'graph'     ,
        'narrative' ,
        'none'      ,
    );

    // Inputs
    private static $inputs = array(
        'isTitle'       ,
        'isRow'         ,
        'isEmpty'       ,
        'isGraphData'   ,
    );

    // Outputs
    private static $outputs = array(
        'setTitle'     ,
        'startTable'   ,
        'appendTable'  ,
        'startGraph'   ,
        'appendGraph'  ,
        'setNarrative' ,
        'nop'          ,
    );

    // Transition function
    // state, input => array(new state, output function)

    private static $tf = array(
    //  isTitle                            isRow                              isEmpty                  isGraphData                          States

        array('none'  ,  'setTitle')   ,   array('none', 'nop')           ,   array('none', 'nop')   , null                            , // start
        array('table' ,  'startTable') ,   array('table', 'appendTable')  ,   array('table', 'nop')  , array('graph', 'startGraph')    , // table
        array('table' ,  'setTitle')   ,   array('graph', 'nop')          ,   array('none', 'nop')   , null                            , // graph
        array('table' ,  'setTitle')   ,   array('none', 'nop')           ,   array('none', 'nop')   , null                            , // narrative
        array('table' ,  'startTable') ,   array('table','appendTable')   ,   array('none', 'nop')   , null                            , // none
    );

    // Fields
    public $property_name;
    public $centre_narrative;
    public $tables = array();
    public $graph = array();

    function __construct() {
        // initial state is start
        $this->state = self::$states[0];
    }

    function processRow($rowData) {
    }

    function getEvent() {
    }

    // Return property data after parsing
    public function propertyData() {
    }
}
