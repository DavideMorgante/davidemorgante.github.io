---
layout: archive
title: "Publications"
permalink: /publications/
author_profile: true
---

<html>
  <head>
    <title>Dr. Nate's Page of accomplishments</title>
    <script type="text/javascript">
    <!--
    var arxiv_authorid = "morgante_d_1";
    //--></script>
    <style type="text/css">
    div.arxivfeed {margin-bottom: 5px; width:700px;}
    </style>
    <script type="text/javascript" src="https://arxiv.org/js/myarticles.js">
    </script>
  </head>
  <body>
    <h1>Nate Rules!</h1>
    <p>Stuff goes here</p>
    <div id="arxivfeed"></div>
  </body>
</html>

#{% if author.googlescholar %}
#  You can also find my articles on <u><a href="{{author.googlescholar}}">my Google Scholar profile</a>.</u>
#{% endif %}

#{% include base_path %}

#{% for post in site.publications reversed %}
#  {% include archive-single.html %}
#{% endfor %}
