/* All units are mm */

eps = 0.01;

raster = 9.87;
led_win_h = 6.0;
led_win_w = 5.0;
led_tape_w = 10.0;
led_tape_thickness = 0.5;

mod_d = 3.0;
wall_w = 2.0;
wall_d = 3.0;
breakoff_slot_w = 1.0;
breakoff_slot_d = 4.0;
breakoff_slot_bottom = 1.5;

do_holder_clips = false;
holder_clip_w = 5.0;
holder_clip_d = 1.0;

do_holder_wires = true;
holder_wire_d = 1.0;
holder_wire_pitch = 5.0;

n_modules = 12;

difference(){
    cube([n_modules*raster, led_tape_w+2*wall_w, mod_d+wall_d]);
    translate([-eps, wall_w, mod_d]) cube([n_modules*raster+2*eps, led_tape_w, wall_d+eps]);
    for (n = [0:n_modules-1]) {
        translate([
            n*raster + (raster-led_win_w)/2,
            wall_w + (led_tape_w-led_win_h)/2,
            -eps])
            cube([led_win_w, led_win_h, mod_d+wall_d+eps]);
    }
    for (n = [1:n_modules-1]) {
        translate([
            n*raster - breakoff_slot_w/2,
            -eps,
            breakoff_slot_bottom 
            ])
            cube([breakoff_slot_w, led_tape_w+2*wall_w+2*eps, breakoff_slot_d+eps]);
    }
    if (do_holder_wires) {
        for (n = [0:n_modules-1]) {
            translate([n*raster + raster/2 - holder_wire_pitch/2,
                -eps,
                mod_d + led_tape_thickness + holder_wire_d/2])
            rotate([-90, 0, 0])
            cylinder(d=holder_wire_d, h=wall_w*2+led_tape_w+2*eps, $fn=16);
            translate([n*raster + raster/2 + holder_wire_pitch/2,
                -eps,
                mod_d + led_tape_thickness + holder_wire_d/2])
            rotate([-90, 0, 0])
            cylinder(d=holder_wire_d, h=wall_w*2+led_tape_w+2*eps, $fn=16);
        }
    }
}

// tape holder clips
if (do_holder_clips) {
    for (n = [0:n_modules-1]) {
        translate([
            n*raster + (raster - holder_clip_w)/2,
            0,
            mod_d + led_tape_thickness
        ]) union () {
            translate([0,wall_w-eps,0])
            cube ([holder_clip_w,
                holder_clip_d + eps,
                wall_w - led_tape_thickness]);
            translate([0,wall_w+led_tape_w-holder_clip_d,0])
            cube ([holder_clip_w,
                holder_clip_d + eps,
                wall_w - led_tape_thickness]);
        };
    }
};