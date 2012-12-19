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
<div class="charttitle"> Centre Composition by GLA </div>
<?php print $chart ?>
        </div>
        <!-- // Col 3 -->
<style>
.propertytables table {
    width: 100%;
}
.propertytables table th {
    background-color: black;
    color: white;
    padding: 13px 3px 1px 3px;
}
.propertytables table td {
    background-color: white;
}

.centretitle {
    background-color: black;
    color: white;
    padding: 13px 3px 1px 3px;
}

.charttitle {
    border-top: 1px solid black;
    padding-top:5px;
    padding-bottom:5px;
    border-bottom: 1px solid #808084;
}

.piechart {
    margin-top:10px;
}
</style>

