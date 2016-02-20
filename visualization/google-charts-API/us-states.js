      google.charts.load('current', {'packages':['geochart']});
      google.charts.setOnLoadCallback(drawRegionsMap);

      function drawRegionsMap() {

        var data = google.visualization.arrayToDataTable([
          ['State', 'Value'],
          ['CA', 600],
          ['MI', 450],
          ['CO', 400],
          ['IL', 500],
          ['IN', 600],
          ['NY', 700]
        ]);

        var options = {region: 'US', resolution: 'provinces'};

        var chart = new google.visualization.GeoChart(document.getElementById('regions_div'));

        chart.draw(data, options);
      }
