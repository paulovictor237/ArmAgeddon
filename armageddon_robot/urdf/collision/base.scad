escala=1000;
% scale(escala) import("../visual/base.stl");

// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x=0;
y=0;
z=0;

translate([x*escala, y*escala, z*escala]) {
    rotate([0, 0, 0]) {
        cylinder(r=100, h=35,center=false);
    }
}