<?php

define('pc_state_nsw', 'nsw')
define('pc_state_act', 'act')
define('pc_state_qld', 'qld')
define('pc_state_nt' , 'nt')
define('pc_state_tas', 'tas')

define('pc_key_name', 'name')
define('pc_key_state', 'state')

function pc_get_properties() {

    /**
     * Mock properties
     */

    return array(
          array(pc_key_name => 'Belconnen', pc_key_state => pc_state_nsw)
        , array(pc_key_name => 'Airport West', pc_key_state => pc_state_nsw)
        , array(pc_key_name => 'Burwood', pc_key_state => pc_state_nsw)
        , array(pc_key_name => 'Melbourne', pc_key_state => pc_state_qld)
    );
}
