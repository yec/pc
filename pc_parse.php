<?php

class Parse {

    private $currentRowData;
    private $state;
    private $currentTable;

    // States
    const State_Title       = 'title';
    const State_Table       = 'table';
    const State_TableNew    = 'tablenew';
    const State_None        = 'none';
    const State_GraphNew    = 'graphnew';
    const State_Graph       = 'graph';
    const State_CentreNew   = 'centrenew';
    const State_Centre      = 'centre';

    // Events
    const Event_IsRow          = 0x1;
    const Event_IsEmptyRow     = 0x2;
    const Event_IsGraphData    = 0x4;
    const Event_IsTitle        = 0x8;
    const Event_IsTableHeading = 0x10;
    const Event_IsCentreNew    = 0x20;

    // Actions
    function action_title() {
        $this->property_name = $this->currentRowData[0];
    }
    function action_none() {
        // todo
    }
    function action_table() {
        if (implode('', $this->currentRowData) != ''
            && $this->currentRowData[1] != '0'
            && $this->currentRowData[2] != '0'
        ) {
            $this->tables[$this->currentTable][] = $this->currentRowData;
        }
    }
    function action_tablenew() {
        $this->currentTable = $this->currentRowData[0];
    }
    function action_graph() {
        if ($this->currentRowData[1] > 0) {
            $this->graph[$this->currentRowData[0]] = $this->currentRowData[1];
        }
    }
    function action_graphnew() {
        // todo
    }

    function action_centre() {
        $this->centre_narrative = $this->currentRowData[0];
    }

    function action_centrenew() {

    }

    // State transition table
    // current state: events => new state
    public static $transition_table = array(
        self::State_Title       => array(self::Event_IsEmptyRow        => self::State_None,
                                         self::Event_IsTableHeading    => self::State_TableNew),

        self::State_TableNew    => array(self::Event_IsRow        => self::State_Table,
                                         self::Event_IsEmptyRow   => self::State_Table),

        self::State_Table       => array(self::Event_IsRow             => self::State_Table,
                                         self::Event_IsTableHeading    => self::State_TableNew,
                                         self::Event_IsGraphData       => self::State_GraphNew,
                                         self::Event_IsEmptyRow        => self::State_Table),

        self::State_None        => array(self::Event_IsRow             => self::State_TableNew,
                                         self::Event_IsTableHeading    => self::State_TableNew,
                                         self::Event_IsGraphData       => self::State_GraphNew,
                                         self::Event_IsTitle           => self::State_Title,
                                         self::Event_IsCentreNew       => self::State_CentreNew,
                                         self::Event_IsEmptyRow        => self::State_None),

        self::State_GraphNew    => array(self::Event_IsRow        => self::State_Graph),

        self::State_Graph       => array(self::Event_IsRow             => self::State_Graph,
                                         self::Event_IsEmptyRow        => self::State_None),

        self::State_CentreNew    => array(self::Event_IsRow           => self::State_Centre),

        self::State_Centre       => array(self::Event_IsRow           => self::State_Centre,
                                          self::Event_IsEmptyRow      => self::State_None),
    );

    // Fields
    public $property_name;
    public $centre_narrative;
    public $tables = array();
    public $graph = array();


    function __construct() {
        $this->state = self::State_None;
    }

    function processRow($rowData) {
        $this->currentRowData = $rowData;

        // transition the state
        $event = $this->getEvent();
        $this->state = self::$transition_table[$this->state][$event];

        // perform the action of this state
        $this->{'action_'.$this->state}();
    }

    function getEvent() {

        if ($this->property_name == null) {
            $this->property_name = 'hello';
            return self::Event_IsTitle;
        }

        if ($this->currentRowData[0] !== NULL && $this->currentRowData[1] === NULL && $this->currentRowData[2] === NULL) {
            switch ($this->currentRowData[0]) {
            case 'Data for Graph':
                return self::Event_IsGraphData;
                break;
            case 'Centre Narrative':
                return self::Event_IsCentreNew;
                break;
            default:
                return self::Event_IsTableHeading;
                break;
            }
        }

        if ($this->currentRowData[0] == NULL && $this->currentRowData[1] === NULL && $this->currentRowData[2] === NULL) {
            return self::Event_IsEmptyRow;
        }

        return self::Event_IsRow;
    }

    // Return property data after parsing
    public function propertyData() {
        return array(
            'centre_narrative' => $this->centre_narrative,
            'graphdata' => $this->graph,
            'tables' => $this->tables
        );
    }
}
