---
layout: gallery
title: Photography
permalink: /photography/
support: [jquery, gallery]
---

<p>Here is a page where I collect some of the pictures that I've taken over the years and liked enough to publish them here!</p>

{% assign count = 0 %}
{% assign align = "left" %}
{% for gallery in site.data.galleries.overview %}
{% if count == 0 %}<div class="row">{% endif %}
  <div class="half-width gallery-preview {{ align }}">
    <h2>{{ gallery.title }}</h2>
    <a href="{{ gallery.directory }}">
      <img alt="{{ gallery.title }}" src="/assets/photography/{% if gallery.picture_path %}{{ gallery.picture_path }}{% else %}{{ gallery.directory }}{% endif %}/{{ gallery.preview.thumbnail }}" />
    </a>
  </div>
{% if count == 1 %}</div>{% endif %}
{% assign count = count | plus: 1 %}
{% assign align = "right" %}
{% if count >= 2 %}
{% assign align = "left" %}
{% assign count = 0 %}
{% endif %}
{% endfor %}

{% if count != 1 %}
{% endif %}