#include "progressbars_init.h"

/*########################################################################*/
/////            P R O G R E S S B A R S     T H E M E S               /////
/*########################################################################*/

////////////////////////////////////////////////////////////////////////////

/*           C I R C L E - PROGRESS BAR */

/*------------------------------------------------------------------------*/
//     C P U
/*------------------------------------------------------------------------*/
circle_bar_t circle_bar_cpu = {
    .radius = 30,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_line_width = 3.0,
    .show_frame = 1,             // frame on/off
    .frame_radius = 34,          // poloměr frame
    .frame_width = 2,          // frame width
    .frame_color = {0.2, 1.0, 0.2, 0.8}
};

/*------------------------------------------------------------------------*/
//     GP U
/*------------------------------------------------------------------------*/
circle_bar_t circle_bar_gpu = {
    .radius = 30,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_line_width = 3.0,
    .show_frame = 1,             // frame on/off
    .frame_radius = 34,          // poloměr frame
    .frame_width = 2,          // frame width
    .frame_color = {0.2, 1.0, 0.2, 0.8}
};

/*------------------------------------------------------------------------*/
//     R A M
/*------------------------------------------------------------------------*/
circle_bar_t circle_bar_ram = {
    .radius = 30,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_line_width = 3.0,
    .show_frame = 1,             // frame on/off
    .frame_radius = 34,          // poloměr frame
    .frame_width = 2,          // frame width
    .frame_color = {0.2, 1.0, 0.2, 0.8}
};

/*------------------------------------------------------------------------*/
//     D I S K
/*------------------------------------------------------------------------*/
circle_bar_t circle_bar_disk = {
    .radius = 30,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_line_width = 3.0,
    .show_frame = 1,             // frame on/off
    .frame_radius = 34,          // poloměr frame
    .frame_width = 2,          // frame width
    .frame_color = {0.2, 1.0, 0.2, 0.8}
};

/*------------------------------------------------------------------------*/
//     N E T W O R K
/*------------------------------------------------------------------------*/
circle_bar_t circle_bar_network = {
    .radius = 30,
    .bg = {0.0, 0.5, 0.5, 0.5},
    .fg = {0.0, 1.0, 1.0},
    .frame_line_width = 3.0,
    .show_frame = 1,             // frame on/off
    .frame_radius = 36,          // poloměr frame
    .frame_width = 1,          // frame width
    .frame_color = {0.5, 1.0, 1.0, 0.5}
};

////////////////////////////////////////////////////////////////////////////

/*           L E D   C I R C L E - PROGRESS BAR */

/*------------------------------------------------------------------------*/
//     C P U
/*------------------------------------------------------------------------*/
led_circle_bar_t led_circle_bar_cpu = {
    .radius = 30,                // poloměr
    .line_width = 3.5,           // tlouštka segmentů
    .segments = 30,              // počet segmentů
    .segment_fill = 0.4,         // poměr 0.4 segment 0.6 mezera
    .show_frame = 1,             // frame on/off
    .frame_radius = 34,          // poloměr frame
    .frame_width = 2,          // frame width
    .frame_color = {0.2, 1.0, 0.2, 0.8},
    .glow = 1,                   // glow efect on/off
    .glow_line1 = 3,             // Glow 1 – širší, slabší
    .glow_line2 = 1.8,           // Glow 2 – užší, silnější
    .show_label = 1,             // text uprostřed on/off
    .off = {0.3, 0.3, 0.3, 0.5}, // neaktivní segmenty barva
    .on = {0.2, 1.0, 0.2},       // aktivní segmenty barva
};


/*------------------------------------------------------------------------*/
//     G P U
/*------------------------------------------------------------------------*/
led_circle_bar_t led_circle_bar_gpu = {
    .radius = 30,                // poloměr
    .line_width = 3.5,           // tlouštka segmentů
    .segments = 30,              // počet segmentů
    .segment_fill = 0.3,         // poměr 0.4 segment 0.6 mezera
    .show_frame = 1,             // frame on/off
    .frame_radius = 36,          // poloměr frame
    .frame_width = 1.0,          // frame width
    .frame_color = {0.2, 0.6, 1.0, 0.8},
    .glow = 0,                   // glow efect on/off
    .glow_line1 = 3,             // Glow 1 – širší, slabší
    .glow_line2 = 1.8,           // Glow 2 – užší, silnější
    .show_label = 1,             // text uprostřed on/off
    .off = {0.3, 0.3, 0.3, 0.5}, // neaktivní segmenty barva
    .on = {0.2, 0.6, 1.0},       // aktivní segmenty barva
};


/*------------------------------------------------------------------------*/
//     R A M
/*------------------------------------------------------------------------*/
led_circle_bar_t led_circle_bar_ram = {
    .radius = 30,                // poloměr
    .line_width = 3.5,           // tlouštka segmentů
    .segments = 20,              // počet segmentů
    .segment_fill = 0.4,         // poměr 0.4 segment 0.6 mezera
    .show_frame = 1,             // frame on/off
    .frame_radius = 34,          // poloměr frame
    .frame_width = 1.5,          // frame width
    .frame_color = {0.2, 0.2, 0.2, 0.8},
    .glow = 1,                   // glow efect on/off
    .glow_line1 = 3,             // Glow 1 – širší, slabší
    .glow_line2 = 1.8,           // Glow 2 – užší, silnější
    .show_label = 1,             // text uprostřed on/off
    .off = {0.3, 0.3, 0.3, 0.5}, // neaktivní segmenty barva
    .on = {0.2, 0.6, 1.0},       // aktivní segmenty barva
};


/*------------------------------------------------------------------------*/
//     D I S K
/*------------------------------------------------------------------------*/
led_circle_bar_t led_circle_bar_disk = {
    .radius = 30,                // poloměr
    .line_width = 3.5,           // tlouštka segmentů
    .segments = 20,              // počet segmentů
    .segment_fill = 0.4,         // poměr 0.4 segment 0.6 mezera
    .show_frame = 1,             // frame on/off
    .frame_radius = 32,          // poloměr frame
    .frame_width = 1.5,          // frame width
    .frame_color = {0.2, 0.2, 0.2, 0.8},
    .glow = 1,                   // glow efect on/off
    .glow_line1 = 3,             // Glow 1 – širší, slabší
    .glow_line2 = 1.8,           // Glow 2 – užší, silnější
    .show_label = 1,             // text uprostřed on/off
    .off = {0.3, 0.3, 0.3, 0.5}, // neaktivní segmenty barva
    .on = {0.2, 0.6, 1.0},       // aktivní segmenty barva
};


/*------------------------------------------------------------------------*/
//     N E T W O R K
/*------------------------------------------------------------------------*/
led_circle_bar_t led_circle_bar_network = {
    .radius = 30,                // poloměr
    .line_width = 3.5,           // tlouštka segmentů
    .segments = 20,              // počet segmentů
    .segment_fill = 0.4,         // poměr 0.4 segment 0.6 mezera
    .show_frame = 1,             // frame on/off
    .frame_radius = 32,          // poloměr frame
    .frame_width = 1.5,          // frame width
    .frame_color = {0.2, 0.2, 0.2, 0.8},
    .glow = 1,                   // glow efect on/off
    .glow_line1 = 3,             // Glow 1 – širší, slabší
    .glow_line2 = 1.8,           // Glow 2 – užší, silnější
    .show_label = 1,             // text uprostřed on/off
    .off = {0.3, 0.3, 0.3, 0.5}, // neaktivní segmenty barva
    .on = {0.2, 0.6, 1.0},       // aktivní segmenty barva
};


////////////////////////////////////////////////////////////////////////////

/*           G A U G E - PROGRESS BAR */

/*------------------------------------------------------------------------*/
//     C P U
/*------------------------------------------------------------------------*/
gauge_bar_t gauge_bar_cpu = {
    .radius = 30,
    .line_width = 2.0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.2, 1.0, 0.2},
    .show_needle = 1,
    .needle_width = 1.5,            // tloušťka ručičky
    .needle_length = 30,           // délka ručičky (0 = auto)
    .needle_center_size = 2.0     // velikost středového kolečka
};


/*------------------------------------------------------------------------*/
//     G P U
/*------------------------------------------------------------------------*/
gauge_bar_t gauge_bar_gpu = {
    .radius = 30,
    .line_width = 2.0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.2, 0.6, 1.0},
    .show_needle = 0,
    .needle_width = 1.5,            // tloušťka ručičky
    .needle_length = 0,           // délka ručičky (0 = auto)
    .needle_center_size = 2.0     // velikost středového kolečka
};


/*------------------------------------------------------------------------*/
//     R A M
/*------------------------------------------------------------------------*/
gauge_bar_t gauge_bar_ram = {
    .radius = 30,
    .line_width = 2.0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .show_needle = 1,
    .needle_width = 1.5,            // tloušťka ručičky
    .needle_length = 0,           // délka ručičky (0 = auto)
    .needle_center_size = 2.0     // velikost středového kolečka
};


/*------------------------------------------------------------------------*/
//     D I S K
/*------------------------------------------------------------------------*/
gauge_bar_t gauge_bar_disk= {
    .radius = 30,
    .line_width = 2.0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .show_needle = 1,
    .needle_width = 1.5,            // tloušťka ručičky
    .needle_length = 0,           // délka ručičky (0 = auto)
    .needle_center_size = 2.0     // velikost středového kolečka
};


/*------------------------------------------------------------------------*/
//     N E T W O R K
/*------------------------------------------------------------------------*/
gauge_bar_t gauge_bar_network = {
    .radius = 30,
    .line_width = 2.0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .show_needle = 1,
    .needle_width = 1.5,            // tloušťka ručičky
    .needle_length = 0,           // délka ručičky (0 = auto)
    .needle_center_size = 2.0     // velikost středového kolečka
};

////////////////////////////////////////////////////////////////////////////

/*          H E X A G O N - PROGRESS BAR */

/*------------------------------------------------------------------------*/
//     C P U
/*------------------------------------------------------------------------*/
hexagon_bar_t hexagon_bar_cpu = {
    .size = 25,
    .line_width = 3,
    .bg = {0.2, 0.2, 0.2},
    .fg = {0.0, 1.0, 1.0}
};
static const char *cpu_labels[] = {"0%", "20%", "40%", "60%", "80%", "100%"};
labels_t labels_cpu = {
    .size = 25,
    .line_width = 3,
    .count = 6,
    .text = cpu_labels
};


/*------------------------------------------------------------------------*/
//     G P U
/*------------------------------------------------------------------------*/
hexagon_bar_t hexagon_bar_gpu = {
    .size = 25,
    .line_width = 3,
    .bg = {0.2, 0.2, 0.2},
    .fg = {0.0, 1.0, 1.0}
};
static const char *gpu_labels[] = {"0%", "20%", "40%", "60%", "80%", "100%"};
labels_t labels_gpu = {
    .size = 25,
    .line_width = 3,
    .count = 6,
    .text = gpu_labels
};

/*------------------------------------------------------------------------*/
//     R A M
/*------------------------------------------------------------------------*/
hexagon_bar_t hexagon_bar_ram = {
    .size = 25,
    .line_width = 3,
    .bg = {0.2, 0.2, 0.2},
    .fg = {0.0, 1.0, 1.0}
};
static const char *ram_labels[] = {"0%", "20%", "40%", "60%", "80%", "100%"};
labels_t labels_ram = {
    .size = 25,
    .line_width = 3,
    .count = 6,
    .text = ram_labels
};

/*------------------------------------------------------------------------*/
//     D I S K
/*------------------------------------------------------------------------*/
hexagon_bar_t hexagon_bar_disk = {
    .size = 25,
    .line_width = 3,
    .bg = {0.2, 0.2, 0.2},
    .fg = {0.0, 1.0, 1.0}
};
static const char *disk_labels[] = {"0%", "20%", "40%", "60%", "80%", "100%"};
labels_t labels_disk = {
    .size = 25,
    .line_width = 3,
    .count = 6,
    .text = disk_labels
};

/*------------------------------------------------------------------------*/
//     N E T W O R K
/*------------------------------------------------------------------------*/
hexagon_bar_t hexagon_bar_network = {
    .size = 25,
    .line_width = 3,
    .bg = {0.2, 0.2, 0.2},
    .fg = {0.0, 1.0, 1.0}
};
static const char *net_labels[] = {"0%", "20%", "40%", "60%", "80%", "100%"};
labels_t labels_network = {
    .size = 25,
    .line_width = 3,
    .count = 6,
    .text = net_labels
};


////////////////////////////////////////////////////////////////////////////

/*          H O R I Z O N T A L  - PROGRESS BAR */

/*------------------------------------------------------------------------*/
//     C P U
/*------------------------------------------------------------------------*/
horizontal_bar_t horizontal_bar_cpu = {
    .segments = 10,
    .gap = 2.5,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0

};

/*------------------------------------------------------------------------*/
//     G P U
/*------------------------------------------------------------------------*/
horizontal_bar_t horizontal_bar_gpu = {
    .segments = 10,
    .gap = 2.5,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0

};

/*------------------------------------------------------------------------*/
//     R A M
/*------------------------------------------------------------------------*/
horizontal_bar_t horizontal_bar_ram = {
    .segments = 1,
    .gap = 0,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.2, 1.0, 0.8},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0

};

/*------------------------------------------------------------------------*/
//     D I S K
/*------------------------------------------------------------------------*/
horizontal_bar_t horizontal_bar_disk = {
    .segments = 10,
    .gap = 3,
    .show_frame = 0,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {1.0, 0.8, 0.2},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0

};

/*------------------------------------------------------------------------*/
//     N E T W O R K
/*------------------------------------------------------------------------*/
horizontal_bar_t horizontal_bar_network = {
    .segments = 10,
    .gap = 2.5,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0

};


/////////////////////////////////////////////////////////////////////////////

/*           V E R T I C A L  - PROGRESS BAR */

/*------------------------------------------------------------------------*/
//     C P U
/*------------------------------------------------------------------------*/
vertical_bar_t vertical_bar_cpu = {
    .segments = 10,
    .gap = 2.5,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0
};

/*------------------------------------------------------------------------*/
//     G P U
/*------------------------------------------------------------------------*/
vertical_bar_t vertical_bar_gpu = {
    .segments = 10,
    .gap = 1,
    .show_frame = 0,
    .show_label = 1,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.2, 0.6, 1.0},            //progress
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0
};

/*------------------------------------------------------------------------*/
//     R A M
/*------------------------------------------------------------------------*/
vertical_bar_t vertical_bar_ram = {
    .segments = 10,
    .gap = 2.5,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0
};

/*------------------------------------------------------------------------*/
//     D I S K
/*------------------------------------------------------------------------*/
vertical_bar_t vertical_bar_disk = {
    .segments = 10,
    .gap = 2.5,
    .show_frame = 1,
    .show_label = 0,
    .bg = {0.2, 0.2, 0.2, 0.5},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0
};

/*------------------------------------------------------------------------*/
//     N E T W O R K
/*------------------------------------------------------------------------*/
vertical_bar_t vertical_bar_network = {
    .segments = 10,
    .gap = 2.7,
    .show_frame = 0,
    .show_label = 0,
    .bg = {0.1, 0.1, 0.1, 0.7},
    .fg = {0.0, 1.0, 0.0},
    .frame_color = {0.5, 0.5, 0.5, 1.0},
    .frame_line_width = 1.0
};
