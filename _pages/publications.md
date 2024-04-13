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


<div class="container">
  <div class="main_wrapper">
    <div class="canvas_wrapper"> <canvas class="canvas chart-area" id="citationHistogram"></canvas> </div>
    <p></p>
    <div class="canvas_wrapper" style="margin-left:3%"> <canvas class="canvas chart-area" id="papersPerYear"></canvas> </div>
  </div>
</div>

{% include bibere/byyear.html mainAuthor='morgante' %}

<script>
    const mainTextColor = getComputedStyle(document.documentElement).getPropertyValue('--main-text-color');

const papers = [
    { title: "Paper 1", citations: 3, published: true, year: 2022 },
    { title: "Paper 2", citations: 59, published: true, year: 2022 },
    { title: "Paper 3", citations: 12, published: true, year: 2023 },
    { title: "Paper 4", citations: 2, published: false, year: 2023 },
    { title: "Paper 5", citations: 6, published: false, year: 2023 },
    { title: "Paper 6", citations: 0, published: false, year: 2024 },
];

const citableCounts = [0, 0, 0, 0, 0]; 
const publishedCounts = [0, 0, 0, 0, 0]; 
const papersPerYear = {};

papers.forEach(paper => {
    const citations = paper.citations;
    const year = paper.year;
    papersPerYear[year] = (papersPerYear[year] || { total: 0, published: 0, citable: 0 });
    papersPerYear[year].total++;
    if (paper.published) {
        papersPerYear[year].published++;
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
        papersPerYear[year].citable++;
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

const years = Object.keys(papersPerYear).sort((a, b) => a - b);
const totalData = years.map(year => papersPerYear[year].total);
const publishedData = years.map(year => papersPerYear[year].published);
const citableData = years.map(year => papersPerYear[year].citable);


var ctx = document.getElementById('citationHistogram').getContext('2d');
var myChart = new Chart(ctx, {
    type: 'bar',
    data: {
        labels: ["0", "1-9", "10-19", "20-49", "50-99"],
        datasets: [{
            label: 'Unpublished Papers',
            backgroundColor: 'rgb(54, 162, 235)',
            data: citableCounts // You can fill this with actual data if needed
        }, {
            label: 'Published Papers',
            backgroundColor: 'rgb(255, 99, 132)',
            data: publishedCounts // You can fill this with actual data if needed
        }]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true,
                    fontColor: mainTextColor
                },
                gridLines: {
                    color: mainTextColor
                }
            }],
            xAxes: [{
                ticks: {
                    fontColor: mainTextColor
                },
                gridLines: {
                    color: mainTextColor
                },
                scaleLabel: {
                    display: true,
                    labelString: 'Citations',
                    fontColor: mainTextColor
                }
            }]
        },
        legend: {
            labels: {
                fontColor: mainTextColor 
            }
        }
    }
});

var ctx2 = document.getElementById('papersPerYear').getContext('2d');
var myChart2 = new Chart(ctx2, {
    type: 'line',
    data: {
        labels: years,
        datasets: [{
            label: 'Published Papers Per Year',
            borderColor: 'rgb(75, 192, 192)',
            data: publishedData
        }, {
            label: 'Unpublished Papers Per Year',
            borderColor: 'rgb(54, 162, 235)',
            data: citableData
        }, {
            label: 'Total Papers Per Year',
            borderColor: 'rgb(255, 206, 86)',
            data: totalData
        }]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero: true,
                    fontColor: mainTextColor
                },
                gridLines: {
                    color: mainTextColor
                }
            }],
            xAxes: [{
                ticks: {
                    fontColor: mainTextColor
                },
                gridLines: {
                    color: mainTextColor
                }
            }]
        },
        legend: {
            labels: {
                fontColor: mainTextColor 
            }
        }
    }
});

</script>

<style>
  .container {
      width: 90%;
      margin: auto;
      margin-left: 3%;
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
      width: 50%;
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

