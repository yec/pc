<?php
/**
 * property template
 * $title = Property title
 * $chart = pie chart
 */
?>
        <!-- Col 2 -->
        <div id="content-col2" >

<div class="centretitle"><?php print $title ?></div>
<img src="http://lorempixel.com/442/240/city" alt="" width="442px" height="240px">
<div class="overview">
<strong>Overview</strong>
<p>
<?php print $centre_narrative; ?>
</p>

</div>
<div class="propertytables">
<?php print_r($tables); ?>
</div>
        </div>
        <!-- // Col 2 -->
        
        <!-- Col 3 -->
        <div id="content-col3" >
<div class="chartitle"> Centre Composition by GLA </div>
<?php print $chart ?>
        </div>
        <!-- // Col 3 -->
