/**
 * if supports vml
 */
function supportsVml() {
    if (typeof supportsVml.supported == "undefined") {
        var a = document.body.appendChild(document.createElement('div'));
        a.innerHTML = '<v:shape id="vml_flag1" adj="1" />';
        var b = a.firstChild;
        b.style.behavior = "url(#default#VML)";
        supportsVml.supported = b ? typeof b.adj == "object": true;
        a.parentNode.removeChild(a);
    }
    return supportsVml.supported
}


var drawPie = function(dataset, element) {
    /**
     * if supports vml then is IE
     * set some things for it
     */
    var vertical_text_offset = supportsVml() ? 4:0;
    var circle_stroke_thickness = supportsVml() ? 1.5:1;

    var width = 132,
        radius = width / 2;

    var height = 18 * dataset.values.length + 2 * radius + 20;

    var colorfn = function(i) {

        var vals =
            [
            '#79c9bc'
            , '#5b1e62'
            , '#44697c'
            , '#412c5d'
            , '#e99a84'
            , '#bbe4de'
            , '#ad8eb0'
            , '#a1b4bd'
            , '#9f95ad'
            , '#f3c6ba'
            , '#ddf1ee'
            , '#d5c6d7'
            ]

            return vals[i];
    }

    var pie = d3.layout.pie()
        .sort(null);

    var arc = d3.svg.arc()
        .innerRadius(radius - 15.5)
        .outerRadius(radius - 4.5);

    var svg = d3.select(element).append("svg")
        .attr("width", 227)
        .attr("height", height)
        .append("g");

    svg.append('circle')
        .style('stroke', '#d8d8d8')
        .style('fill', 'white')
        .style('stroke-width', circle_stroke_thickness)
        .attr('r', radius - 1)
        .attr("transform", "translate(" + width / 2 + "," + width / 2 + ")");

    svg.append('circle')
        .style('stroke', '#d8d8d8')
        .style('fill', 'white')
        .style('stroke-width', circle_stroke_thickness)
        .attr('r', radius - 19)
        .attr("transform", "translate(" + width / 2 + "," + width / 2 + ")");

    var path = svg.selectAll("path")
        .data(pie(dataset.values))
        .enter().append("path")
        .attr("fill", function(d, i) { return colorfn(i); })
        .attr("d", arc)
        .attr('class', 'noborder')
        .attr("transform", "translate(" + width / 2 + "," + width / 2 + ")");

    for (i in dataset.legend) {
        // Draw legend boxes
        svg.append('rect')
            .attr('fill', colorfn(i))
            .attr('width', 8)
            .attr('height', 8)
            .attr('x', 0)
            .attr('y', 18*i)
            .attr('class', 'noborder')
            .attr("transform", "translate(10," + (width + 15) + ")");
        // Draw legend text
        svg.append('text')
            .text(dataset.legend[i])
            .attr('font-family', 'helvetica')
            .attr('font-size', '12px')
            .attr('text-anchor', 'start')
            .attr('y', 18*i - vertical_text_offset)
            .attr("transform", "translate(23," + (width + 23) + ")");
    }

};

var piedata = {
    values:[200, 200, 200, 200, 200],
    legend:['legend 1', 'legend 2', 'legend 3', 'legend 4', 'legend 5']
};

