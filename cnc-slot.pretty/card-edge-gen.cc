#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static constexpr float kSlotDeep = 9;
static constexpr char kHeader[] = R"(
(module cnc-card-edge-%d (layer F.Cu) (tedit %X)
  (fp_text reference REF** (at 8.5 0 270) (layer F.SilkS)
    (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value cnc-card-edge-25 (at -13.5 0 90) (layer F.Fab)
    (effects (font (size 1 1) (thickness 0.15)))
  )
)";

struct { const char *txt; bool recessed = false; } properties[] = {
    { "EStop_1", true }, { "GND" },
    { "5V" },            { "n/c" },
    { "PWM_1" },         { "PWM_1" },
    { "PWM_1" },         { "PWM_1" },
    { "PWM_2" },         { "PWM_2" },
    { "PWM_2" },         { "PWM_2" },
    { "PWM_3" },         { "PWM_4" },
    { "M1_A+" },         { "M1_A-" },
    { "M1_B+" },         { "M1_B-" },
    { "M2_A+" },         { "M2_A-" },
    { "M2_B+" },         { "M2_B-" },
    { "M3_A+" },         { "M3_A-" },
    { "M3_B+" },         { "M3_B-" },
    { "M4_A+" },         { "M4_A-" },
    { "M4_B+" },         { "M4_B-" },
    { "GND" },           { "GND" },
    { "SW_1" },          { "SW_2" },
    { "SW_3" },          { "SW_4" },
    { "SW_5" },          { "SW_6" },
    { "RS422_TX+" },     { "RS422_TX-" },
    { "RS485_RXTX+" },   { "RS485_RXTX-" },
    { "GND" },           { "GND" },
    { "n/c" },           { "n/c" },
    { "Ain_1" },         { "Ain_2" },
    { "GND" },           { "EStop_2", true },

    { "SW-7"},           { "SW-8" },
    { "n/c"},            { "n/c" },
    { "M5_A+" },         { "M5_A-" },
    { "M5_B+" },         { "M5_B-" },
    { "M6_A+" },         { "M6_A-" },
    { "M6_B+" },         { "M6_B-" },

    { "M7_A+" },         { "M7_A-" },
    { "M7_B+" },         { "M7_B-" },
    { "n/c"},            { "n/c" },
    { "n/c"},            { "n/c" },
    { "GND" },           { "GND" },
};

void text(float x, float y, bool front, const char *txt) {
    if (!txt) return;
    if (front) {
        printf("  (fp_text user \"%s\" (at %.2f %.2f) (layer F.SilkS) (effects (font (size 1 1) (thickness 0.15)) (justify left)))\n",
               x, y, txt);
    } else {
        printf("  (fp_text user \"%s\" (at %.2f %.2f) (layer B.SilkS) (effects (font (size 1 1) (thickness 0.15)) (justify right mirror)))\n",
               x, y, txt);
    }
}

float xpos = 0;
float ypos = 0;
static void moveto(float x, float y) {
    xpos = x;
    ypos = y;
}
static void lineto(float x, float y) {
    printf("  (fp_line (start %.2f %2f) (end %.2f %.2f) (layer Edge.Cuts) (width 0.05))\n",
           xpos, ypos, x, y);
    moveto(x, y);
}

static void pad(int n, float pos_y, bool recessed, const char *layer) {
    const float trace_origin = 1.27;
    const float solder_margin = 2.5;
    float pad_len = kSlotDeep + trace_origin;
    const float origin_x = pad_len/2 - trace_origin;
    float pos_x = 0;

    const float kDefaultRecess = 0.8;
    const float kShortPadRecess = kDefaultRecess + 1.5;
    float recess_shorter = recessed ? kShortPadRecess : kDefaultRecess;
    pad_len -= recess_shorter;
    pos_x += recess_shorter/2;

    printf("  (pad %d smd roundrect (at %.2f %.2f) (size %.2f 1.27) "
           "(drill (offset %.2f 0)) (layers %s)(roundrect_rratio 0.25) (solder_mask_margin %.2f))\n",
           n, pos_x, pos_y, pad_len, -origin_x, layer, solder_margin);
}

static int usage(const char *progname) {
    fprintf(stderr, "Usage: %s [25|31|36]\n", progname);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return usage(argv[0]);

    const int positions = atoi(argv[1]);
    if (positions != 25 && positions != 31 && positions != 36) {
        return usage(argv[0]);
    }

    const float txt_x = 1.5;
    const float distance = 2.54;
    const float len = distance * positions;
    const float start_component = (distance * (positions+2))/2;
    const float extra_wide = 1.3;
    const float slot_thick = kSlotDeep;
    const float corner = 0.7;
    const float top_radius = 0.635;

    printf(kHeader, positions, time(nullptr));

    fprintf(stderr, "Pos: %d Contacts wide: %.2f Edge-width: %.2f\n",
            positions, len, len + 2*extra_wide);

    moveto(0, -start_component);
    lineto(0, -len/2 - extra_wide - top_radius);
    printf("  (fp_arc (start %f %f) (end %f %f) (angle -90) (layer Edge.Cuts) (width 0.05))\n", -top_radius, ypos, -top_radius, -len/2 - extra_wide);
    moveto(-top_radius, -len/2 - extra_wide);

    lineto(-slot_thick + corner, -len/2 - extra_wide);
    lineto(-slot_thick,          -len/2 - extra_wide + corner);

    lineto(-slot_thick,          len/2 + extra_wide - corner);
    lineto(-slot_thick+ corner,  len/2 + extra_wide);

    lineto(-top_radius,  len/2 + extra_wide);
    printf("  (fp_arc (start %f %f) (end %f %f) (angle 90) (layer Edge.Cuts) (width 0.05))\n", -top_radius, len/2 + extra_wide + top_radius,
           -top_radius, len/2 + extra_wide);
    moveto(0, len/2 + extra_wide + top_radius);
    lineto(0, start_component);

    for (int i = 0; i < positions; ++i) {
        pad(2*i+1, -len/2 + distance/2 + i*distance,
            properties[2*i].recessed, "F.Cu F.Mask");
        pad(2*i+2, -len/2 + distance/2 + i*distance,
            properties[2*i+1].recessed, "B.Cu B.Mask");
    }

    for (int i = 0; i < positions; ++i) {
        float txt_y = -len/2 + distance/2 + i*distance;
        text(txt_x, txt_y, true, properties[2*i].txt);
        text(txt_x, txt_y, false, properties[2*i+1].txt);
    }
    printf(")\n");
}
