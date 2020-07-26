escala=1000;
% scale(escala) import("../visual/link2.stl");

// Append pure shapes (cube, cylinder and sphere), e.g:
// cube([10, 10, 10], center=true);
// cylinder(r=10, h=10, center=true);
// sphere(10);
// coordenadas

x= 5.48191e-16;
y= 0.086;
z= 0.128;

translate([x*escala, y*escala+90, z*escala-75]) {
    rotate([0, 0, 0]) {
        cylinder(r=60, h=745, center=false);
    }
}