---
layout: archive
title: "Publications"
permalink: /publications/
author_profile: true
---

<!--
{% if author.googlescholar %}
  You can also find my articles on <u><a href="{{author.googlescholar}}">my Google Scholar profile</a>.</u>
{% endif %}

{% include base_path %}

{% for post in site.publications reversed %}
  {% include archive-single.html %}
{% endfor %}
 -->

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>


<div class="container">
  <div class="main_wrapper">
    <div class="canvas_wrapper"> <canvas class="canvas chart-area" id="citationHistogram"></canvas> </div>
    <div class="canvas_wrapper"> <canvas class="canvas chart-area" id="paperCountDoughnut"></canvas> </div>
  </div>
</div>

{% include bibere/byyear.html mainAuthor='morgante' %}

<script>
  // Sample data (replace with your actual data)
  const mainTextColor = getComputedStyle(document.documentElement).getPropertyValue('--main-text-color');
  const papers = [
      { title: "Paper 1", citations: 3, published: true },
      { title: "Paper 2", citations: 59, published: true },
      { title: "Paper 3", citations: 12, published: true },
      { title: "Paper 4", citations: 2, published: false },
      { title: "Paper 5", citations: 6, published: false },
      { title: "Paper 6", citations: 0, published: false },
      // Add more papers here...
  ];

  // Initialize arrays to hold citation counts for citable and published papers
  const citableCounts = [0, 0, 0, 0, 0]; // Initialize with zeros for each citation range
  const publishedCounts = [0, 0, 0, 0, 0]; // Initialize with zeros for each citation range

  // Count the number of papers falling into each citation range for citable and published papers
  papers.forEach(paper => {
      const citations = paper.citations;
      if (paper.published) {
          if (citations == 0) {
              publishedCounts[0]++;
          } else if (citations < 10) {
              publishedCounts[1]++;
          } else if (citations < 20) {
              publishedCounts[2]++;
          } else if (citations < 50) {
              publishedCounts[3]++;
          } else {
              publishedCounts[4]++;
          }
      } else {
          if (citations == 0) {
              citableCounts[0]++;
          } else if (citations < 10) {
              citableCounts[1]++;
          } else if (citations < 20) {
              citableCounts[2]++;
          } else if (citations < 50) {
              citableCounts[3]++;
          } else {
              citableCounts[4]++;
          }
      }
  });

  // Draw the histogram
  var ctx = document.getElementById('citationHistogram').getContext('2d');
  var myChart = new Chart(ctx, {
  type: 'bar',
  data: {
  labels: ["0", "1-9", "10-19", "20-49", "50-99"],
  datasets: [{
      label: 'Citable Papers',
      backgroundColor: 'rgb(54, 162, 235)',
      data: citableCounts // Sample data for citable papers
  }, {
      label: 'Published Papers',
      backgroundColor: 'rgb(255, 99, 132)',
      data: publishedCounts // Sample data for published papers
  }]
  },
  options: {
    scales: {
      yAxes: [{
        ticks: {
            beginAtZero: true,
            fontColor: mainTextColor // Set the color of the ticks on the y-axis to the value of --main-text-color
        },
        gridLines: {
            color: mainTextColor // Set the color of the grid lines on the y-axis to the value of --main-text-color
        }
    }],
    xAxes: [{
        ticks: {
            fontColor: mainTextColor // Set the color of the ticks on the x-axis to the value of --main-text-color
        },
        gridLines: {
            color: mainTextColor // Set the color of the grid lines on the x-axis to the value of --main-text-color
        }
      }]
    },
    legend: {
            labels: {
                fontColor: mainTextColor // Set the color of the legend labels to the value of --main-text-color
            }
    }
  }
  });
   // Draw the doughnut chart for paper count
        var ctxDoughnut = document.getElementById('paperCountDoughnut').getContext('2d');
        var myChartDoughnut = new Chart(ctxDoughnut, {
            type: 'doughnut',
            data: {
                labels: ['Citable','Published'],
                datasets: [{
                    data: [publishedCounts.reduce((a, b) => a + b), citableCounts.reduce((a, b) => a + b)],
                    backgroundColor: ['rgb(54, 162, 235)','rgb(255, 99, 132)']
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false
            }
        });

</script>

<style>
  .container {
      width: 90%;
      margin: auto;
      margin-left: 10%;
      align-items: center;
  }

  .main_wrapper{
      display: flex;
      flex-wrap: row;
      justify-content: center;
      align-items: center;
      height: auto;
      width: 100%;
  }
  .canvas_wrapper{
      display: flex;
      justify-content: center;
      align-items: center;
      flex-direction: column;
      width: 60%;
  }
  .canvas{
      width: 100%;
      height: auto;
  }
</style>




<!--
<style type="text/css">
  div.arxivfeed {margin-bottom: 5px; width:700px;}
</style>

<div id="arxivfeed"></div>
-->

