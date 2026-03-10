# wayland_movable — Version 05

## Overview

Version **05** is a major step forward compared to version **04**.

While v04 was mainly a functional Wayland SHM + Cairo demo application with double buffering and a tick loop, **v05 evolves into a modular framework** combining:

    - Wayland SHM rendering

    - Cairo graphics and text

    - system monitoring modules

    - widgets

    - a configuration system

    - drag-to-move window support

This version represents the first real foundation for Wayland widgets, dashboards, and lightweight system monitors.

---

## Major Changes in Version 05

Modular Architecture

The project is now divided into independent modules with clear responsibilities.

.
├── cairo_graphics
├── cairo_text
├── config
├── orchestrator
├── system_info
├── ui
├── utils
├── widgets
├── wayland_movable.c
├── xdg_move.c/.h
└── Makefile

Each module focuses on a single responsibility, simplifying maintenance and future development.

---

## Core Architecture

### System Layer

**system_info**

Provides dynamic system metrics:

    - CPU

    - RAM

    - GPU (nVidia)

    - network

    - storage

    - uptime

---
    
### Rendering Layer

**cairo_graphics**

Responsible for graphical elements:

    - shapes

    - progress bars

    - graphs

    - LED bars

    - gauges

    - hexagon progress indicators

---
    
### cairo_text

**Handles textual output:**

    - time and date

    - CPU / RAM usage

    - network information

    - storage statistics

---
    
### Widget Layer

**widgets**

Widgets combine:

    - system data

    - graphics

    - text

Each widget is implemented as an independent module.

---

## Orchestration Layer

### orchestrator

Controls execution flow:

init → update → draw

---

## Widget Lifecycle

Version 05 introduces a unified widget pipeline.

   1. init_all
      Initializes widgets, graphs, and text modules.

   2. update_all
      Updates system data and widget states on every tick.

   3. draw_all
      Renders widgets in the correct order.

   4. widget_registry
      Registers widgets and allows enabling/disabling them through the config system.

This is the first version where widgets behave as real modular components.

---

## Configuration System

The config/ directory introduces the first full configuration system.

Components:

   * config_loader – custom config.ini parser

   * graphs_init – graph theme initialization

   * progressbars_init – progress bar theme initialization

config.ini allows configuration of:

   * window size and position

   * widget enable/disable

   * widget positions

   * theme parameters (colors, radius, thickness, fonts)

   * network interface (auto / manual)
   
---

## Available Widgets (v05)

Widgets combine text + progress bars + history graphs.

    - Clock – circular clock

    - CPU widget
      usage %, temperature °C, frequency MHz

    - RAM widget
      usage %, used / max MB

    - GPU widget (nVidia only)
      usage %, temperature, VRAM %, core/mem MHz, power W

    - Network widget
      RX/TX speed, interface, WiFi signal strength, IP address

    - Storage widget
      usage %, total / used / free GB, disk I/O

    - SysInfo widget
      time, date, uptime, hostname, kernel, Plasma version

---

## Drag-to-Move Support

Version 05 introduces window dragging support.

xdg_move

    - captures mouse button events

    - sends move request to Wayland

    - compositor performs the window movement

This allows the window to behave like a movable widget/dashboard panel.

---

## Build (in terminal)

make

Run:

./wayland_movable

---

## Summary

Version 05 transitions the project from a demo application into a modular Wayland widget framework by introducing:

    - modular architecture

    - widget pipeline

    - system monitoring modules

    - graphical widgets

    - configuration system

    - drag-to-move window support

This version forms the technical foundation for the later **KwiWi project**.
