var drawPie = function(dataset, element) {
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
        .append("g")
        .attr("transform", "translate(" + width / 2 + "," + width / 2 + ")");

    svg.append('circle')
        .style('stroke', '#d8d8d8')
        .style('fill', 'transparent')
        .style('stroke-width','1px')
        .attr('r', radius - 1);

    svg.append('circle')
        .style('stroke', '#d8d8d8')
        .style('fill', 'transparent')
        //.style('stroke-width','1px')
        .attr('r', radius - 19);

    for (i in dataset.legend) {

        svg.append('rect')
            .attr('fill', colorfn(i))
            .attr('width', 8)
            .attr('height', 8)
            .attr('x', -radius + 6)
            .attr('y', 18*i + radius + 20);

        svg.append('text')
            .text(dataset.legend[i])
            .attr('font-family', 'helvetica')
            .attr('font-size', '12px')
            .attr('x', -radius + 20)
            .attr('y', 18*i + radius + 28);

    }

    var path = svg.selectAll("path")
        .data(pie(dataset.values))
        .enter().append("path")
        .attr("fill", function(d, i) { return colorfn(i); })
        .attr("d", arc);
};

var piedata = {
    values:[200, 200, 200, 200, 200],
    legend:['legend 1', 'legend 2', 'legend 3', 'legend 4', 'legend 5'],
};

