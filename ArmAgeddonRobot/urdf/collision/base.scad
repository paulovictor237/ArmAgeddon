% scale(1000) import("base.stl");

// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
rotate([0, 0, 0]) {
    translate([0, 0, 0]) {
        cylinder(r=100, h=30, center=false);
    }
}